#pragma once

#include "../gea_adapter.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace gea_adapter {

    enum TextSensorType {
        GEAA_SENSOR_STATE,
        GEAA_SENSOR_SUB_STATE,
        GEAA_SENSOR_CYCLE,
        GEAA_SENSOR_DRYNESS_SETTING,
        GEAA_SENSOR_HEAT_SETTING,
        GEAA_SENSOR_RINSE_SETTING,
        GEAA_SENSOR_SOIL_SETTING,
        GEAA_SENSOR_SPIN_SETTING,
        GEAA_SENSOR_TEMP_SETTING
    };
    class GEAATextSensor : public text_sensor::TextSensor, public gea_adapter::GEAA_Child, public Component {

    public:
        void setup() override;
        void set_text_sensor_type(TextSensorType text_sensor_type) { this->text_sensor_type_ = text_sensor_type; }
        TextSensorType get_text_sensor_type() { return this->text_sensor_type_; }

    protected:
        TextSensorType text_sensor_type_;
    };

} // namespace gea_adapter
} // namespace esphome