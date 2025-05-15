#include "..\gea_adapter.h"
#include "GEAA_text_sensor.h"
#include <stdint.h>


namespace esphome {
namespace gea_adapter {

static const char *TAG = "gea_adapter.text_sensor.dishwasher_erds";

void GEAA_Component::dishwasher_text_sensor_3001() {

    switch (rx_buf[9])  {

        case 0x00: //Low Power
            text_sensor_send(0x3001, "Off");
            break;
        case 0x01: //Power Up
            text_sensor_send(0x3001, "Power Up");
            break;
        case 0x02: //Standby
            text_sensor_send(0x3001, "Standby");
            break;
        case 0x03: //Delay Start
            text_sensor_send(0x3001, "Delay Start");
            break;
        case 0x04: //Pause
            text_sensor_send(0x3001, "Pause");
            break;
        case 0x05: //Run
            text_sensor_send(0x3001, "Running");
            break;
        case 0x06: //EOC
            text_sensor_send(0x3001, "Done");
            break;
        case 0x07: //Download Mode
            text_sensor_send(0x3001, "Download Mode");
            break;
        case 0x08: //Sensor Check Mode
            text_sensor_send(0x3001, "Sensor Check Mode");
            break;
        case 0x09: //Load Activation Mode
            text_sensor_send(0x3001, "Load Activation Mode");
            break;
        case 0x0B: //MC Only Mode
            text_sensor_send(0x3001, "MC Only Mode");
            break;
        case 0x0C: //User Alert Mode
            text_sensor_send(0x3001, "User Alert Mode");
            break;
        case 0x0D: //Lock
            text_sensor_send(0x3001, "Locked");
            break;
        case 0x0E: //CSM
            text_sensor_send(0x3001, "CSM");
            break;
        case 0x0F: //Wifi Binding
            text_sensor_send(0x3001, "Wifi Binding");
            break;
        case 0x10: //Rinse Aid Level Selection
            text_sensor_send(0x3001, "Rinse Aid Level Selection");
            break;
        case 0x11: //Sabbath Mode
            text_sensor_send(0x3001, "Sabbath Mode");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2000 value %X", rx_buf[9]);
    }
}

void GEAA_Component::dishwasher_text_sensor_300E() {
    switch (rx_buf[9]) {
        
        case 0x00:
            text_sensor_send(0x300E, "No Change");
            break;
        case 0x01:
            text_sensor_send(0x300E, "PreWash");
            break;
        case 0x02:
            text_sensor_send(0x300E, "Sensing");
            break;
        case 0x03:  
            text_sensor_send(0x300E, "Main Wash");
            break;
        case 0x04:
            text_sensor_send(0x300E, "Drying");
            break;
        case 0x05:  
            text_sensor_send(0x300E, "Sanitizing");
            break;
        case 0x06:          
            text_sensor_send(0x300E, "Turbidity Cal");
            break;
        case 0x07:
            text_sensor_send(0x300E, "Diverter Cal");
            break;
        case 0x08:
            text_sensor_send(0x300E, "Pause");
            break;
        case 0x09:
            text_sensor_send(0x300E, "Rinsing");
            break;
        case 0x0A:
            text_sensor_send(0x300E, "PreWash 1");
            break;
        case 0x0B:
            text_sensor_send(0x300E, "Final Rinse");
            break;
        case 0x0C:
            text_sensor_send(0x300E, "End PreWash 1");
            break;
        case 0x0D:
            text_sensor_send(0x300E, "Auto Hot Start 1");
            break;
        case 0x0E:
            text_sensor_send(0x300E, "Auto Hot Start 2");
            break;
        case 0x0F:
            text_sensor_send(0x300E, "Auto Hot Start 3");
            break;
        case 0x10:
            text_sensor_send(0x300E, "Final Rinse Fill");
            break;
        case 0x11:
            text_sensor_send(0x300E, "Cycle Inactive");
            break;
        case 0x12:
            text_sensor_send(0x300E, "End of Cycle");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 300E value %X", rx_buf[9]); 

    }
}

//09  7F  0F  00  getting 4 bytes not just 1

void GEAA_Component::dishwasher_text_sensor_321B() {
    switch (rx_buf[9]) {

        case 0x00:
            text_sensor_send(0x321B, "Cycle0");
            break;
        case 0x01:
            text_sensor_send(0x321B, "Cycle1");
            break;
        case 0x02:
            text_sensor_send(0x321B, "Cycle2");
            break;
        case 0x03:
            text_sensor_send(0x321B, "Cycle3");
            break;
        case 0x04:
            text_sensor_send(0x321B, "Cycle4");
            break;
        case 0x05:
            text_sensor_send(0x321B, "Cycle5");
            break;
        case 0x06:
            text_sensor_send(0x321B, "Cycle6");
            break;
        case 0x07:
            text_sensor_send(0x321B, "Cycle7");
            break;
        case 0x08:
            text_sensor_send(0x321B, "Unused");
            break;
        case 0x09:
            text_sensor_send(0x321B, "AutoSense");
            break;
        case 0x0A:
            text_sensor_send(0x321B, "Auto");
            break;
        case 0x0B:
            text_sensor_send(0x321B, "Auto Wash");
            break;
        case 0x0C:
            text_sensor_send(0x321B, "Smart");
            break;
        case 0x0D:
            text_sensor_send(0x321B, "Heavy");
            break;
        case 0x0E:
            text_sensor_send(0x321B, "Pots");
            break;
        case 0x0F:
            text_sensor_send(0x321B, "Intense");
            break;
        case 0x10:
            text_sensor_send(0x321B, "Heavy Duty");
            break;
        case 0x11:
            text_sensor_send(0x321B, "Normal");
            break;
        case 0x12:
            text_sensor_send(0x321B, "Medium");
            break;
        case 0x13:
            text_sensor_send(0x321B, "Everyday");
            break;
        case 0x14:
            text_sensor_send(0x321B, "Light");
            break;
        case 0x15:
            text_sensor_send(0x321B, "China");
            break;
        case 0x16:
            text_sensor_send(0x321B, "Delicate");
            break;
        case 0x17:
            text_sensor_send(0x321B, "1 Hr Wash");
            break;
        case 0x18:
            text_sensor_send(0x321B, "Express");
            break;
        case 0x19:
            text_sensor_send(0x321B, "30 Minutes");
            break;
        case 0x1A:
            text_sensor_send(0x321B, "Quick");
            break;
        case 0x1B:
            text_sensor_send(0x321B, "Time Saver");
            break;
        case 0x1C:
            text_sensor_send(0x321B, "Eco");
            break;
        case 0x1D:
            text_sensor_send(0x321B, "Rinse");
            break;
        case 0x1E:
            text_sensor_send(0x321B, "Custom");
            break;
        case 0x1F:
            text_sensor_send(0x321B, "Cookware");
            break;
        case 0x20:
            text_sensor_send(0x321B, "Gentle");
            break;
        case 0x21:
            text_sensor_send(0x321B, "Cascade Platinum Plus");
            break;
        case 0x22:
            text_sensor_send(0x321B, "Baby Care");
            break;
        case 0x23:
            text_sensor_send(0x321B, "Glass");
            break;
        case 0x24:
            text_sensor_send(0x321B, "Steam");
            break;
        case 0x25:
            text_sensor_send(0x321B, "Crystal");
            break;
        case 0x26:
            text_sensor_send(0x321B, "1 Hour");
            break;
        case 0x27:
            text_sensor_send(0x321B, "Prep Rinse");
            break;
        case 0x28:
            text_sensor_send(0x321B, "HydroSave");
            break;
        case 0x29:
            text_sensor_send(0x321B, "Quiet");
            break;
        case 0x2A:
            text_sensor_send(0x321B, "Dishwasher Cleaning");
            break;
        case 0x2B:
            text_sensor_send(0x321B, "Quiet2");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 200A value %X", rx_buf[9]);
    }
}

void GEAA_Component::dishwasher_text_sensor_3003() {
    switch (rx_buf[9]) {

    }
}

void GEAA_Component::dishwasher_text_sensor_3037() {
    switch (rx_buf[9]) {
        case 0x00:
            text_sensor_send(0x3037, "Open");
            break;
        case 0x01:
            text_sensor_send(0x3037, "Closed");
            break;
        case 0x02:
            text_sensor_send(0x3037, "Invalid");
            break;
        case 0x03:
            text_sensor_send(0x3037, "Init");
            break;
        case 0x04:
            text_sensor_send(0x3037, "Unknown");
            break;
        default:
            ESP_LOGE(TAG, "Unknown ERD 2016 value %X", rx_buf[9]);
    }
}


}  // namespace gea_adapter
}  // namespace esphome