#pragma once

#include "../gea_adapter.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/component.h"
#include <stdint.h>

namespace esphome {
namespace gea_adapter {

    enum SensorType {
        GEAA_SENSOR_DOOR,
        GEAA_SENSOR_DOORLOCK,
        GEAA_SENSOR_CYCLE_COMPLETE,
        GEAA_SENSOR_UNBALANCED,
        GEAA_SENSOR_RINSE_AID,
        GEAA_SENSOR_FLOOD

    };

    class GEAABinarySensor : public binary_sensor::BinarySensor, public gea_adapter::GEAA_Child, public Component {
    public:
        void setup() override;
        
        void set_binary_sensor_type(SensorType binary_sensor_type) { this->binary_sensor_type_ = binary_sensor_type; }
        void set_erd(uint16_t erd) { this->erd_ = erd; }
        
        SensorType get_binary_sensor_type() { return this->binary_sensor_type_; }
        uint16_t get_erd() { return this->erd_; }

    protected:
        SensorType binary_sensor_type_;
        uint16_t erd_;
    };

} // namespace gea_adapter
} // namespace esphome
