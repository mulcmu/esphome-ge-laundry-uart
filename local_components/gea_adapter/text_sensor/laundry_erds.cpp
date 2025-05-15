#include "..\gea_adapter.h"
#include "GEAA_text_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.text_sensor.laundry_erds";

void GEAA_Component::laundry_text_sensor_send(uint16_t erd, const char* value) {

    for (auto *text_sensor : this->text_sensors_) {
        auto *gea_text_sensor = static_cast<GEAATextSensor *>(text_sensor);
        if (gea_text_sensor->get_erd() == erd) {
            gea_text_sensor->publish_state(value);
            return;
        }
    }
    ESP_LOGE(TAG, "Failed to find text sensor for ERD %x", erd);
}

void GEAA_Component::laundry_text_sensor_2000() {

    switch (rx_buf[9])  {
        case 0x00: //Idle screen off
        case 0x01: //Standby, display on
            laundry_text_sensor_send(0x2000, "Off");
            break;
        case 0x02: //Run
            laundry_text_sensor_send(0x2000, "Running");
            break;                    
        case 0x03: //Paused
            laundry_text_sensor_send(0x2000, "Paused");
            break;    
        case 0x04: //EOC
            laundry_text_sensor_send(0x2000, "Done");
            break;                    
        default:
            ESP_LOGE(TAG, "Unknown ERD 2000 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2001() {
    switch (rx_buf[9]) {
        case 0x00:
            laundry_text_sensor_send(0x2001, "N/A");
            break;
        case 0x01:
            laundry_text_sensor_send(0x2001, "Fill");
            break;
        case 0x02:
            laundry_text_sensor_send(0x2001, "Soak");
            break;
        case 0x03:
            laundry_text_sensor_send(0x2001, "Wash");
            break;
        case 0x04:
            laundry_text_sensor_send(0x2001, "Rinse");
            break;
        case 0x05:
            laundry_text_sensor_send(0x2001, "Spin");
            break;
        case 0x06: 
            laundry_text_sensor_send(0x2001, "Drain");
            break;   
        case 0x07: 
            laundry_text_sensor_send(0x2001, "Extra Spin");
            break;   
        case 0x08: 
            laundry_text_sensor_send(0x2001, "Extra Rinse");
            break;                  
        case 0x09:
            laundry_text_sensor_send(0x2001, "Tumble");
            break;                    
        case 0x0A: 
            laundry_text_sensor_send(0x2001, "Load Detection");
            break;                    
        case 0x80: 
            laundry_text_sensor_send(0x2001, "Drying");
            break;   
        case 0x81: 
            laundry_text_sensor_send(0x2001, "Steam");
            break;   
        case 0x82: 
            laundry_text_sensor_send(0x2001, "Cool Down");
            break;   
        case 0x83: 
            laundry_text_sensor_send(0x2001, "Extended Tumble");
            break;   
        case 0x84: 
            laundry_text_sensor_send(0x2001, "Damp");
            break;  
        case 0x85: 
            laundry_text_sensor_send(0x2001, "Air Fluff");
            break;                                       
        default:
            ESP_LOGE(TAG, "Unknown ERD 2001 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_200A() {
    switch (rx_buf[9]) {
        case 0x89:
            laundry_text_sensor_send(0x200A, "Mixed Load");
            break;
        case 0x0D:
            laundry_text_sensor_send(0x200A, "Delicates");
            break;
        case 0x80:
            laundry_text_sensor_send(0x200A, "Cottons");
            break;
        case 0x0B:
            laundry_text_sensor_send(0x200A, "Jeans");
            break;
        case 0x8B:
            laundry_text_sensor_send(0x200A, "Casuals");
            break;
        case 0x88:
            laundry_text_sensor_send(0x200A, "Quick Dry");
            break;
        case 0x06:
            laundry_text_sensor_send(0x200A, "Towels");
            break;
        case 0x04:
            laundry_text_sensor_send(0x200A, "Bulky");
            break;
        case 0x05:
            laundry_text_sensor_send(0x200A, "Sanitize");
            break;
        case 0x85:
            laundry_text_sensor_send(0x200A, "Air Fluff");
            break;
        case 0x8C:
            laundry_text_sensor_send(0x200A, "Warm Up");
            break;
        case 0x83:
            laundry_text_sensor_send(0x200A, "Timed Dry");
            break;
        case 0x14:
            laundry_text_sensor_send(0x200A, "Colors");
            break;
        case 0x09:
            laundry_text_sensor_send(0x200A, "Whites");
            break;
        case 0x82:
            laundry_text_sensor_send(0x200A, "Active Wear");
            break;
        case 0x1D:
            laundry_text_sensor_send(0x200A, "Quick Wash");
            break;
        case 0x02:
            laundry_text_sensor_send(0x200A, "Drain & Spin");
            break;
        case 0x1A:
            laundry_text_sensor_send(0x200A, "Deep Clean");
            break;  
        default:
            ESP_LOGE(TAG, "Unknown ERD 200A value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2015() {
    switch (rx_buf[9]) {
        case 0x01:
            laundry_text_sensor_send(0x2015, "Light");
            break;
        case 0x02:
            laundry_text_sensor_send(0x2015, "Normal");
            break;
        case 0x03:
            laundry_text_sensor_send(0x2015, "Heavy");
            break;
        case 0x04:
            laundry_text_sensor_send(0x2015, "Extra Heavy");
            break;
        case 0x05: //occurs for drain & spin cycle
            laundry_text_sensor_send(0x2015, "N/A");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2015 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2016() {
    switch (rx_buf[9]) {
        case 0x06:
            laundry_text_sensor_send(0x2016, "N/A");
            break;
        case 0x10:
            laundry_text_sensor_send(0x2016, "Tap Cold");
            break;
        case 0x11:
            laundry_text_sensor_send(0x2016, "Cold");
            break;
        case 0x12:
            laundry_text_sensor_send(0x2016, "Cool");
            break;
        case 0x13:
            laundry_text_sensor_send(0x2016, "Colors");
            break;
        case 0x14:
            laundry_text_sensor_send(0x2016, "Warm");
            break;
        case 0x15:
            laundry_text_sensor_send(0x2016, "Hot");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2016 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2017() {
    switch (rx_buf[9]) {
        case 0x00:
            laundry_text_sensor_send(0x2017, "No Spin");
            break;
        case 0x02:
            laundry_text_sensor_send(0x2017, "Normal");
            break;
        case 0x03:
            laundry_text_sensor_send(0x2017, "More");
            break;
        case 0x04:
            laundry_text_sensor_send(0x2017, "Max");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2017 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2018() {
    switch (rx_buf[9]) {
        case 0x00:
            laundry_text_sensor_send(0x2018, "Standard Rinse");
            break;
        case 0x01:
            laundry_text_sensor_send(0x2018, "Deep Rinse");
            break;
        case 0x02:
            laundry_text_sensor_send(0x2018, "Extra Rinses");
            break;
        case 0x03:
            laundry_text_sensor_send(0x2018, "Deep + Extra Rinse");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2018 value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_204D() {
    switch (rx_buf[9]) {
        case 0x00:
            laundry_text_sensor_send(0x204D, "N/A");
            break;
        case 0x01:
            laundry_text_sensor_send(0x204D, "Damp");
            break;
        case 0x02:
            laundry_text_sensor_send(0x204D, "Less Dry");
            break;
        case 0x03:
            laundry_text_sensor_send(0x204D,"Dry");
            break;
        case 0x04:
            laundry_text_sensor_send(0x204D, "More Dry");
            break; 
        default:
            ESP_LOGE(TAG, "Unknown ERD 204D value %X", rx_buf[9]);
    }
}

void GEAA_Component::laundry_text_sensor_2050() {
    switch (rx_buf[9]) {
        case 0x01:
            laundry_text_sensor_send(0x2050, "Air Fluff");
            break;
        case 0x03:
            laundry_text_sensor_send(0x2050, "Low");
            break;
        case 0x04:
            laundry_text_sensor_send(0x2050, "Medium");
            break;
        case 0x05:
            laundry_text_sensor_send(0x2050, "High");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2050 value %X", rx_buf[9]);
    }
}


}  // namespace gea_adapter
}  // namespace esphome