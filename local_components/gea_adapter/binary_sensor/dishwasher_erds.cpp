#include "../gea_adapter.h"
#include "GEAA_binary_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.binary_sensor.dishwasher_erds";



void GEAA_Component::dishwasher_binary_sensor_D003() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0xD003, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0xD003, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD D003 value %X", rx_buf[9]);
                }
}

void GEAA_Component::dishwasher_binary_sensor_3038() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x3038, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x3038, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 3038 value %X", rx_buf[9]);
                }
}

void GEAA_Component::dishwasher_binary_sensor_3085() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x3085, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x3085, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 3085 value %X", rx_buf[9]);
                }
}


}  // namespace gea_adapter
}  // namespace esphome