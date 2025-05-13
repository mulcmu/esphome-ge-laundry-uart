#include "./GEAA_text_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace gea_adapter {

    static const char* const TAG = "GEAA.text_sensor";

    void GEAATextSensor::setup() {
        this->parent_->add_read_erd_packet(this->erd_);
    }

} // namespace gea_adapter
} // namespace esphome