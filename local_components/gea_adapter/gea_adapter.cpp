#include "gea_adapter.h"
#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include "./sensor/GEAA_sensor.h"
#include "./binary_sensor/GEAA_binary_sensor.h"
#include "./text_sensor/GEAA_text_sensor.h"
#include <stdint.h>
#include <string>
#include <list>
#include <thread>
#include <vector>
#include "esphome/components/uart/uart_debugger.h"

#include "driver/uart.h"


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.component";

void GEAA_Component::setup(){
    rx_buf.reserve(128);

    //esp-idf call, default value was too slow for the GEA_ACK to get sent
    uart_set_rx_timeout((uart_port_t)0,1);

    set_interval("send_packet", 500, [this]() {
        if (read_erd_packet_list_.size() > 0) {
            send_next_packet_();
        }
    });
    
}

void GEAA_Component::loop(){
    
    uint8_t b;

    // ESP_LOGD(TAG, "loop %d", millis());

    if (available() == 0 || processing_packet_) {
        return;
    }

    while ( available() ) {
        
        read_byte(&b);

        if (b == GEA_ESC) {
            //read escaped data byte
            read_byte(&b);
            rx_buf.push_back(b);
        }
        else {  //unescaped control bytes
            if (b == GEA_STX) {
                rx_buf.clear();            
            }
            
            rx_buf.push_back(b);

            if (b == GEA_ETX && rx_buf.size() > 3)  {
                if (rx_buf[1]==this->source_address_ ) { 
                    write(GEA_ACK);
                    processing_packet_ = true;
                    defer([this]() {process_packet_();} ); 
                    return;
                } 
            }

        }
    }
            
    if(rx_buf.size() == rx_buf.capacity() )  {
        ESP_LOGE(TAG, "rx_buf was filled!");
        rx_buf.clear();            
    }
}


void GEAA_Component::dump_config(){

    ESP_LOGCONFIG(TAG, "GEAA Component");
    ESP_LOGCONFIG(TAG, "  Destination address: 0x%02X", this->destination_address_);
    ESP_LOGCONFIG(TAG, "  Source address: 0x%02X", this->source_address_);
    
    for (auto *text_sensor : this->text_sensors_) {
        LOG_TEXT_SENSOR("  ", "GEAA Text sensor", text_sensor);
        auto *gea_text_sensor = static_cast<gea_adapter::GEAATextSensor *>(text_sensor);
        if (gea_text_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_text_sensor->get_text_sensor_type());
            ESP_LOGCONFIG(TAG, "    ERD: %x", gea_text_sensor->get_erd());
        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast text sensor to GEAATextSensor");
        }
    }

    for (auto *binary_sensor : this->binary_sensors_) {
        LOG_BINARY_SENSOR("  ", "GEAA Binary sensor", binary_sensor);
        auto *gea_binary_sensor = static_cast<gea_adapter::GEAABinarySensor *>(binary_sensor);
        if (gea_binary_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_binary_sensor->get_binary_sensor_type());
            ESP_LOGCONFIG(TAG, "    ERD: %x", gea_binary_sensor->get_erd());
        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast binary sensor to GEAABinarySensor");
        }
    }
    for (auto *sensor : this->sensors_) {
        LOG_SENSOR("  ", "GEAA Sensor", sensor);
        auto *gea_sensor = static_cast<gea_adapter::GEAASensor *>(sensor);
        if (gea_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_sensor->get_sensor_type());
            ESP_LOGCONFIG(TAG, "    ERD: %x", gea_sensor->get_erd());

        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast sensor to GEAASensor");
        }
    }

    int i = 0;
    for (const auto &packet : this->read_erd_packet_list_) {

        std::string res;
        size_t len = packet.size();
        char buf[6];
        for (size_t i = 0; i < len; i++) {
            sprintf(buf, " %02X ", packet[i]);
            res += buf;
        }
        
        ESP_LOGCONFIG(TAG, "  Read ERD packet %d:  %s ",i, res.c_str());
        i++;
        delay(10);
    }
    
    ESP_LOGCONFIG(TAG, "  ------");
}

void GEAA_Component::add_read_erd_packet(uint16_t erd) {


    read_erd_packet_list_.insert(read_erd_packet_list_.end(), std::vector<uint8_t>(ERD_PACKET_SIZE, 0));
    auto &packet = read_erd_packet_list_.back();
    
    packet.clear();
    packet.push_back(GEA_STX); // Start byte
    packet.push_back(this->destination_address_);
    packet.push_back(0x0B); // Length before escape characters added
    packet.push_back(this->source_address_);
    packet.push_back(0xF0); // Read ERD command  TODO: F0 is for gea2, gea3 is A0.  is F0 backward compatible or deprecated or gea2 but full duplex?
    packet.push_back(0x01); // Number of ERDs
    packet.push_back((erd >> 8) & 0xFF); // High byte of ERD
    packet.push_back(erd & 0xFF); // Low byte of ERD

    uint16_t crc = tiny_crc16_block(packet.data(), 8);
    packet.push_back((crc >> 8) & 0xFF); // High byte of CRC
    packet.push_back(crc & 0xFF); // Low byte of CRC

    // Escape bytes if necessary
    for(size_t i = 1; i < packet.size(); ++i) {
        if (needs_escape_(packet[i])) {
            packet.insert(packet.begin() + i, GEA_ESC);
            ++i;
        }
    }

    packet.push_back(GEA_ETX); // End byte

    read_erd_packet_list_it_=read_erd_packet_list_.begin();
}

void GEAA_Component::send_next_packet_() {

    auto &packet = *read_erd_packet_list_it_;
    write_array(packet);

    read_erd_packet_list_it_++;

    if ( read_erd_packet_list_it_ == read_erd_packet_list_.end()) {
        read_erd_packet_list_it_ = read_erd_packet_list_.begin();
    } 
}

void GEAA_Component::sensor_send(uint16_t erd, float value) {

    for (auto *sensor : this->sensors_) {
        auto *gea_sensor = static_cast<GEAASensor *>(sensor);
        if (gea_sensor->get_erd() == erd) {
            gea_sensor->publish_state(value);
            return;
        }
    }
    ESP_LOGE(TAG, "Failed to find sensor for ERD %04X", erd);
}

void GEAA_Component::text_sensor_send(uint16_t erd, const char* value) {

    for (auto *text_sensor : this->text_sensors_) {
        auto *gea_text_sensor = static_cast<GEAATextSensor *>(text_sensor);
        if (gea_text_sensor->get_erd() == erd) {
            gea_text_sensor->publish_state(value);
            return;
        }
    }
    ESP_LOGE(TAG, "Failed to find text sensor for ERD %x", erd);
}

void GEAA_Component::binary_sensor_send(uint16_t erd, bool value) {

    for (auto *binary_sensor : this->binary_sensors_) {
        auto *gea_binary_sensor = static_cast<GEAABinarySensor *>(binary_sensor);
        if (gea_binary_sensor->get_erd() == erd) {
            gea_binary_sensor->publish_state(value);
            return;
        }
    }
    ESP_LOGE(TAG, "Failed to find binary sensor for ERD %04X", erd);
}

void GEAA_Component::process_packet_() {

    if (rx_buf.size() < 3) {
        ESP_LOGE(TAG, "Packet too short");
        processing_packet_ = false;
        return;
    }

    if (rx_buf[2] != rx_buf.size()) {
        ESP_LOGE(TAG, "Invalid packet length: expected %d, got %d", rx_buf[2], rx_buf.size());
        processing_packet_ = false;
        return;
    }

    uint16_t crc = tiny_crc16_block(rx_buf.data(), rx_buf.size() - 3);
    uint16_t crc_received = (rx_buf[rx_buf.size() - 3] << 8) | rx_buf[rx_buf.size() - 2];

    if (crc != crc_received) {
        ESP_LOGE(TAG, "CRC mismatch: calculated %04X, received %04X", crc, crc_received);
        processing_packet_ = false;
        return;
    }

    //send ack if crc is ok
    //write(GEA_ACK); too slow here???


    std::string res;
    size_t len = rx_buf.size();
    char buf[6];
    for (size_t i = 0; i < len; i++) {
        sprintf(buf, " %02X ", rx_buf[i]);
        res += buf;
    }
    
    ESP_LOGD(TAG, "Packet:  %s ", res.c_str());



    uint16_t erd = (rx_buf[6] << 8) | rx_buf[7];
    switch (erd) {
        case 0x2002: // State
            laundry_binary_sensor_2002();  // complete
            break;
        case 0x2012: // Door
            laundry_binary_sensor_2012();  // door
            break;
        case 0x2013: // Door Locked
            laundry_binary_sensor_2013();  // door_locked
            break;
        case 0x20A6: // Unbalanced
            laundry_binary_sensor_20A6();  // unbalanced
            break;
        case 0xD003: //  complete
            dishwasher_binary_sensor_D003();  // complete
            break;
        case 0x3038: //  rinse aid
            dishwasher_binary_sensor_3038();  // rinse aid
            break;
        case 0x3085: // flood
            dishwasher_binary_sensor_3085();  // flood
            break;

        case 0x2003: // Total Cycles
            laundry_sensor_2003();  // total_cycles
            break;
        case 0x2007: // Remaining Cycle Time
            laundry_sensor_2007();  // remaining_cycle_time
            break;
        case 0xD004:
            dishwasher_sensor_D004();  // remaining_cycle_time
            break;
        case 0x321A:
            dishwasher_sensor_321A();  // delay start time
            break;

        case 0x2000: // State
            laundry_text_sensor_2000();  // state
            break;
        case 0x2001: // Sub State
            laundry_text_sensor_2001();  // sub_state
            break;
        case 0x200A: // Cycle
            laundry_text_sensor_200A();  // cycle
            break;
        case 0x2015: // Soil Setting
            laundry_text_sensor_2015();  // soil_setting
            break;
        case 0x2016: // Temp Setting
            laundry_text_sensor_2016();  // temp_setting
            break;
        case 0x2017: // Spin Setting
            laundry_text_sensor_2017();  // spin_setting
            break;
        case 0x2018: // Rinse Setting
            laundry_text_sensor_2018();  // rinse_setting
            break;
        case 0x204D: // Dryness Setting
            laundry_text_sensor_204D();  // dryness_setting
            break;
        case 0x2050: // Heat Setting
            laundry_text_sensor_2050();  // heat_setting
            break;
        case 0x3001: // State
            dishwasher_text_sensor_3001();  // state
            break;
        case 0x300E: // Sub State
            dishwasher_text_sensor_300E();  // sub_state
            break;
        case 0x321B: // Cycle
            dishwasher_text_sensor_321B();  // cycle
            break;
        case 0x3003: // Reminder
            dishwasher_text_sensor_3003();  // reminder
            break;
        case 0x3037: 
            dishwasher_text_sensor_3037();  // door
            break;

        default:
            ESP_LOGE(TAG, "Unknown ERD: %04X", erd);
            break;
    }

    processing_packet_ = false;
}

} //namespace gea_adapter
} //namespace esphome
