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

  class GEAA_Component :public PollingComponent, public uart::UARTDevice {

  public:
    void setup() override;
    void loop() override;
    void update() override;
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

    static constexpr size_t ERD_PACKET_SIZE = 32;
    static constexpr size_t RX_BUFFER_SIZE = 128;
    static constexpr size_t CRC_SEED = 0xE300;
    
    static constexpr uint8_t GEA_ESC = 0xE0;
    static constexpr uint8_t GEA_STX = 0xE1;
    static constexpr uint8_t GEA_ETX = 0xE2;
    static constexpr uint8_t GEA_ACK = 0xE3;

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

  };

}  // namespace gea_adapter
}  // namespace esphome
