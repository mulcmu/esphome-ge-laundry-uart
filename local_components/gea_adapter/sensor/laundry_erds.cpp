#include "..\gea_adapter.h"
#include "GEAA_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.sensor.laundry_erds";


void GEAA_Component::laundry_sensor_2003() {
                uint16_t cycles = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                sensor_send(0x2003, cycles);
}

void GEAA_Component::laundry_sensor_2007() {
                uint16_t seconds = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                float minutes = seconds / 60.0;
                sensor_send(0x2007, minutes);
}
 

 


}  // namespace gea_adapter
}  // namespace esphome