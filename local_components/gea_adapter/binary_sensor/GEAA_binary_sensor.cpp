#include "./GEAA_binary_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace gea_adapter {

    static const char* const TAG = "GEAA.binary_sensor";

    void GEAABinarySensor::setup()
    {
        if (this->binary_sensor_type_ == SensorType::GEAA_SENSOR_DOORLOCK) {
            this->publish_initial_state(true);
            // this->parent_->subscribe_motion_state([=](MotionState state) {
            //     this->publish_state(state == MotionState::DETECTED);
            // });
        } else if (this->binary_sensor_type_ == SensorType::GEAA_SENSOR_CYCLE_COMPLETE) {
            this->publish_initial_state(false);
            // this->parent_->subscribe_obstruction_state([=](ObstructionState state) {
            //     this->publish_state(state == ObstructionState::OBSTRUCTED);
            // });
        } 
    }

} // namespace gea_adapter
} // namespace esphome
