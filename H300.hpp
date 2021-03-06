/**
 * Original authors: http://team18-19.studenti.fiit.stuba.sk/
 */

#pragma once

#include <ModbusMaster.h>  // source: https://www.arduino.cc/reference/en/libraries/modbusmaster/
#include <stdint.h>

#include <string>

#include "config/config.hpp"
#include "device.hpp"

class H300 : public Device {
 private:
  String name;
  String category = "MOTOR";
  int status = DEVICE_WAITING;

  mutable ModbusMaster node;

  static constexpr HardwareSerial& serial_bus = Serial2;

  static void pre_transmission();
  static void post_transmission();

  uint32_t iteration_counter;

 public:
  const uint8_t slave_id;

  static constexpr uint16_t speed_register = 0x1000;  // writable
  static constexpr uint16_t state_register = 0x8000;
  static constexpr uint16_t get_freq_register = 0x1001;
  static constexpr uint16_t set_freq_register = 0xF00C;  // writable
  static constexpr uint16_t get_motion_register = 0x3000;
  static constexpr uint16_t set_motion_register = 0x2000;  // writable
  static constexpr uint16_t accel_time_register = 0xF011;  // writable
  static constexpr uint16_t decel_time_register = 0xF012;  // writable
  static constexpr uint16_t get_timer_register = 0x1015;
  static constexpr uint16_t set_timer_register = 0xF82C;  // writable

  H300(const uint8_t slave_id, String name);
  uint8_t write_value(const uint16_t register_addr, const uint16_t value) const;
  uint8_t read_value(const uint16_t register_addr, uint16_t* const response) const;
  void set_motion(String type);

  // interface Device
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);
};
