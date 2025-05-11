#include "GEAA_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace gea_adapter {

    static const char* const TAG = "GEAA.sensor";

    void GEAASensor::setup()
    {
        // this->parent_->subscribe_openings([=](uint16_t value) {
        //     this->publish_state(value);
        // });
    }

} // namespace gea_adapter
} // namespace esphome
