#pragma once

#include "../gea_adapter.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace gea_adapter {

    enum GEAASensorType {
        GEAA_REMAINING_CYCLE_TIME,
        GEAA_TOTOAL_CYCLES
   };

    class GEAASensor : public sensor::Sensor, public gea_adapter::GEAA_Child, public Component {
    public:
        void setup() override;
        void set_sensor_type(GEAASensorType sensor_type) { this->sensor_type_ = sensor_type; }
        GEAASensorType get_sensor_type() { return this->sensor_type_; }

    protected:
        GEAASensorType sensor_type_;
    };

} // namespace gea_adapter
} // namespace esphome
