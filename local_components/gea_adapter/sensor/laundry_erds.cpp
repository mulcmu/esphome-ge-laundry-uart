#include "..\gea_adapter.h"
#include "GEAA_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.sensor.laundry_erds";

void GEAA_Component::laundry_sensor_send(uint16_t erd, float value) {

    for (auto *sensor : this->sensors_) {
        auto *gea_sensor = static_cast<GEAASensor *>(sensor);
        if (gea_sensor->get_erd() == erd) {
            gea_sensor->publish_state(value);
            return;
        }
    }
    ESP_LOGE(TAG, "Failed to find sensor for ERD %04X", erd);
}


void GEAA_Component::laundry_sensor_2003() {
                uint16_t cycles = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                laundry_sensor_send(0x2003, cycles);
}

void GEAA_Component::laundry_sensor_2007() {
                uint16_t seconds = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                float minutes = seconds / 60.0;
                laundry_sensor_send(0x2007, minutes);
}
 

 


}  // namespace gea_adapter
}  // namespace esphome