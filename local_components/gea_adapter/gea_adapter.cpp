#include "gea_adapter.h"
#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include ".\sensor\GEAA_sensor.h"
#include ".\binary_sensor\GEAA_binary_sensor.h"
#include ".\text_sensor\GEAA_text_sensor.h"


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.component";

void GEAA_Component::setup(){

    rx_buf.reserve(128);

}

void GEAA_Component::loop(){
    
   
}


void GEAA_Component::dump_config(){

    ESP_LOGCONFIG(TAG, "GEAA Component");

    for (auto *text_sensor : this->text_sensors_) {
        LOG_TEXT_SENSOR("  ", "GEAA Text sensor", text_sensor);
        auto *gea_text_sensor = static_cast<gea_adapter::GEAATextSensor *>(text_sensor);
        if (gea_text_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_text_sensor->get_text_sensor_type());
        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast text sensor to GEAATextSensor");
        }
    }

    for (auto *binary_sensor : this->binary_sensors_) {
        LOG_BINARY_SENSOR("  ", "GEAA Binary sensor", binary_sensor);
        auto *gea_binary_sensor = static_cast<gea_adapter::GEAABinarySensor *>(binary_sensor);
        if (gea_binary_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_binary_sensor->get_binary_sensor_type());
        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast binary sensor to GEAABinarySensor");
        }
    }
    for (auto *sensor : this->sensors_) {
        LOG_SENSOR("  ", "GEAA Sensor", sensor);
        auto *gea_sensor = static_cast<gea_adapter::GEAASensor *>(sensor);
        if (gea_sensor != nullptr) {
            ESP_LOGCONFIG(TAG, "    GEAA type: %d", gea_sensor->get_sensor_type());
        } else {
            ESP_LOGCONFIG(TAG, "  Failed to cast sensor to GEAASensor");
        }
    }
}

} //namespace gea_adapter
} //namespace esphome