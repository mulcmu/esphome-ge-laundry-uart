#include "../gea_adapter.h"
#include "GEAA_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.sensor.dishwasher_erds";


void GEAA_Component::dishwasher_sensor_D004() {
                uint16_t minutes = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                sensor_send(0xD004, minutes);
}

void GEAA_Component::dishwasher_sensor_321A() {
                uint16_t minutes = (uint16_t)(rx_buf[9]) << 8 | (uint16_t)rx_buf[10];
                sensor_send(0x321A, minutes);
}
 

 


}  // namespace gea_adapter
}  // namespace esphome