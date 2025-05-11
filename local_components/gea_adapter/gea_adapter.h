#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/gpio.h"
#include "esphome/core/log.h"
#include "esphome/core/preferences.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <stdint.h>

namespace esphome {
namespace gea_adapter {

  class GEAA_Component;
  typedef Parented<GEAA_Component> GEAA_Child;  

  class GEAA_Component : public Component {

  public:
    void setup() override;
    void loop() override;
    void dump_config() override;
    float get_setup_priority() const override { return esphome::setup_priority::LATE; }
    
    void register_sensor(sensor::Sensor *obj) { this->sensors_.push_back(obj); }
    void register_sensor(binary_sensor::BinarySensor *obj) { this->binary_sensors_.push_back(obj); }
    void register_sensor(text_sensor::TextSensor *obj) { this->text_sensors_.push_back(obj); }

  protected:
    std::vector<sensor::Sensor *> sensors_;
    std::vector<binary_sensor::BinarySensor *> binary_sensors_;
    std::vector<text_sensor::TextSensor *> text_sensors_;
    std::vector<uint32_t> erd_list__;

    uint8_t b=0;
    unsigned long millisProgress=0;
    uint8_t erd=0;
    
    std::vector<uint8_t> rx_buf;     

  };

}  // namespace gea_adapter
}  // namespace esphome
