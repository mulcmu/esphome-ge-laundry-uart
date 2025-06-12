#include "../gea_adapter.h"
#include "GEAA_binary_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.binary_sensor.laundry_erds";

void GEAA_Component::laundry_binary_sensor_2002() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x2002, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x2002, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 2002 value %X", rx_buf[9]);
                }
}

void GEAA_Component::laundry_binary_sensor_2012() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x2012, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x2012, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 2012 value %X", rx_buf[9]);
                }
}

void GEAA_Component::laundry_binary_sensor_2013() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x2013, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x2013, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 2013 value %X", rx_buf[9]);
                }
}

void GEAA_Component::laundry_binary_sensor_20A6() {
                switch (rx_buf[9])  {
                    case 0x00: 
                        binary_sensor_send(0x20A6, false);
                        break;   
                    case 0x01: 
                        binary_sensor_send(0x20A6, true);
                        break;                           
                    default:
                        ESP_LOGE(TAG, "Unknown ERD 20A6 value %X", rx_buf[9]);
                }
}


}  // namespace gea_adapter
}  // namespace esphome