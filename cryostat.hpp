#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "device.hpp"

// for cryostat Julabo CF41
class Cryostat : public Device {
 private:
  String name;
  String category = "TEMPERATURE";
  int status = DEVICE_WAITING;

  static constexpr unsigned long baud_rate = 19200;
  static constexpr HardwareSerial& serial_bus = Serial2;

  // list of important commands supported by CF41
  // because we use RS485 we need to send "A032_" register address before each command
  String set_temp_command = "A032_OUT_SP_00 ";

  String use_temp_command = "A032_OUT_MODE_01 0";
  String stop_unit_command = "A032_OUT_MODE_05 0";
  String start_unit_command = "A032_OUT_MODE_05 1";
  String cooling_power_high_command = "A032_OUT_HIL_00 -100";
  String cooling_power_low_command = "A032_OUT_HIL_00 -10";
  String heating_power_high_command = "A032_OUT_HIL_01 100";
  String heating_power_low_command = "A032_OUT_HIL_00 10";

  String bath_temp_command = "A032_IN_PV_00";
  String working_temp_command = "A032_IN_SP_00";
  String selected_temp_command = "A032_IN_MODE_01";
  String cooling_power_command = "A032_IN_HIL_00";
  String heating_power_command = "A032_IN_HIL_01";

  String status_command = "A032_STATUS";

 public:
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  Cryostat(String sensorName);
  void updateStatus();

  void setTemperature(int param);
  String sendCommand(String command);
};
