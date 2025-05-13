#include "gea_adapter.h"
#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include ".\sensor\GEAA_sensor.h"
#include ".\binary_sensor\GEAA_binary_sensor.h"
#include ".\text_sensor\GEAA_text_sensor.h"
#include <stdint.h>
#include <string>
#include <list>
#include <vector>
#include "esphome/components/uart/uart_debugger.h"


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.component";

void GEAA_Component::setup(){

    rx_buf.reserve(128);

    this->set_update_interval(1000); // Set the update interval to 1 second

}

void GEAA_Component::loop(){
    
   
}

void GEAA_Component::update() {
    if (this->read_erd_packet_list_.empty()) {
        return;
    }
    send_next_packet_();

}


void GEAA_Component::dump_config(){

    ESP_LOGCONFIG(TAG, "GEAA Component");
    ESP_LOGCONFIG(TAG, "  Destination address: %02X", this->destination_address_);
    ESP_LOGCONFIG(TAG, "  Source address: %02X", this->source_address_);
    
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
            ++i; // Skip the next byte
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


} //namespace gea_adapter
} //namespace esphome