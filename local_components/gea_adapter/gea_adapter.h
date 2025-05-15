#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/gpio.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/preferences.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include <stdint.h>
#include <list>
#include <vector>

namespace esphome {
namespace gea_adapter {

  class GEAA_Component;
  typedef Parented<GEAA_Component> GEAA_Child;  

  class GEAA_Component :public Component, public uart::UARTDevice {

  public:
    void setup() override;
    void loop() override;
    // float get_loop_priority() const override {return 2.0f; }  // increse default priority
    void dump_config() override;
    float get_setup_priority() const override { return esphome::setup_priority::LATE; }
    
    void register_sensor(sensor::Sensor *obj) { this->sensors_.push_back(obj); }
    void register_sensor(binary_sensor::BinarySensor *obj) { this->binary_sensors_.push_back(obj); }
    void register_sensor(text_sensor::TextSensor *obj) { this->text_sensors_.push_back(obj); }

    void set_destination_address(uint8_t address) { this->destination_address_ = address; }
    void set_source_address(uint8_t address) { this->source_address_ = address; }

    void add_read_erd_packet(uint16_t erd);

  protected:
    std::vector<sensor::Sensor *> sensors_;
    std::vector<binary_sensor::BinarySensor *> binary_sensors_;
    std::vector<text_sensor::TextSensor *> text_sensors_;
    
    uint8_t destination_address_;
    uint8_t source_address_;

    bool processing_packet_ = false;

    static constexpr size_t ERD_PACKET_SIZE = 32;
    static constexpr size_t RX_BUFFER_SIZE = 128;
    static constexpr size_t CRC_SEED = 0xE300;
    
    static constexpr uint8_t GEA_ESC = 0xE0;
    static constexpr uint8_t GEA_ACK = 0xE1;
    static constexpr uint8_t GEA_STX = 0xE2;
    static constexpr uint8_t GEA_ETX = 0xE3;

    std::list<std::vector<uint8_t>> read_erd_packet_list_; 
    std::list<std::vector<uint8_t>>::iterator read_erd_packet_list_it_;

    std::vector<uint8_t> rx_buf = std::vector<uint8_t>(RX_BUFFER_SIZE);
    

    //MIT License https://github.com/geappliances/tiny-gea-api/
    uint16_t tiny_crc16_byte(uint16_t seed, uint8_t byte)
    {
      uint16_t crc = seed;
      byte = (uint8_t)(crc >> 8 ^ byte);
      byte ^= byte >> 4;
      return (uint16_t)((crc << 8) ^ ((uint16_t)(byte << 12)) ^ ((uint16_t)(byte << 5)) ^ ((uint16_t)byte));
    }
    //MIT License https://github.com/geappliances/tiny-gea-api/
    uint16_t tiny_crc16_block(const uint8_t* bytes, size_t byte_count)
    {
      uint16_t crc = CRC_SEED;
      for(size_t i = 0; i < byte_count; i++) {
        crc = tiny_crc16_byte(crc, bytes[i]);
      }
      return crc;
    }

    //MIT License https://github.com/geappliances/tiny-gea-api/
    bool needs_escape_(uint8_t b) {return (b & 0xFC) == GEA_ESC;}

    void send_next_packet_();
    void process_packet_();

    void laundry_binary_sensor_send(uint16_t erd, bool value);
    void laundry_binary_sensor_2002();  // complete
    void laundry_binary_sensor_2012();  // door
    void laundry_binary_sensor_2013();  // door_locked
    void laundry_binary_sensor_20A6();  // unbalanced

    void laundry_sensor_send(uint16_t erd, float value);
    void laundry_sensor_2003();  // total_cycles
    void laundry_sensor_2007();  // remaining_cycle_time

    void laundry_text_sensor_send(uint16_t erd, const char* value);
    void laundry_text_sensor_2000();  // state
    void laundry_text_sensor_2001();  // sub_state
    void laundry_text_sensor_200A();  // cycle
    void laundry_text_sensor_2015();  // soil_setting 
    void laundry_text_sensor_2016();  // temp_setting
    void laundry_text_sensor_2017();  // spin_setting
    void laundry_text_sensor_2018();  // rinse_setting
    void laundry_text_sensor_204D();  // dryness_setting
    void laundry_text_sensor_2050();  // heat_setting

  };

}  // namespace gea_adapter
}  // namespace esphome
