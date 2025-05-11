#include "./GEAA_text_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace gea_adapter {

    static const char* const TAG = "GEAA.text_sensor";

    void GEAATextSensor::setup() {
        if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_STATE) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_CYCLE) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_DRYNESS_SETTING) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_SUB_STATE) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_HEAT_SETTING) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_RINSE_SETTING) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_SOIL_SETTING) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_SPIN_SETTING) {
            this->publish_state("Unknown");
        } else if (this->text_sensor_type_ == TextSensorType::GEAA_SENSOR_TEMP_SETTING) {
            this->publish_state("Unknown");
        } else {
            ESP_LOGE(TAG, "Unknown text sensor type: %d", this->text_sensor_type_);
        }
    }

} // namespace gea_adapter
} // namespace esphome