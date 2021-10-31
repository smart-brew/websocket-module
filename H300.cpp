/**
 * Original authors: http://team18-19.studenti.fiit.stuba.sk/
 */

#include "H300.hpp"

H300::H300(const std::string device_id, const uint8_t unit_id, const uint32_t poll_rate, uint8_t RX, uint8_t TX, String _name)
    : device_id(device_id), unit_id(unit_id), poll_rate(poll_rate) {
  iteration_counter = poll_rate;
  name = _name;
}

void H300::init() {
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);

  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication through hardware bus
  serial_bus.begin(baud_rate, SERIAL_8N1, RX, TX);
  node.begin(unit_id, serial_bus);

  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(pre_transmission);
  node.postTransmission(post_transmission);
}

void H300::pre_transmission() {
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void H300::post_transmission() {
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

// Write value to holding register
uint8_t H300::write_value(const uint16_t register_addr, const uint16_t value) const {
  return node.writeSingleRegister(register_addr, value);
}

// Read value from holding register
uint8_t H300::read_value(const uint16_t register_addr, uint16_t* const response) const {
  const uint8_t result = node.readHoldingRegisters(register_addr, 1);

  if (result == node.ku8MBSuccess)
    *response = node.getResponseBuffer(0);

  return result;
}

bool H300::decrease_counter() {
  iteration_counter--;

  if (iteration_counter == 0) {
    iteration_counter = poll_rate;
    return true;
  }

  return false;
}

float H300::get() {
  uint16_t speed = 0;
  if (!read_value(speed_register, &speed)) {
    float speed_res = float(speed) / 10;
    return speed_res;
  }
  return speed;
};

void H300::getJsonValues(JsonObject& obj) {
  uint16_t speed = 0;
  if (!read_value(speed_register, &speed)) {
    float speed_res = float(speed) / 10;

    obj["SPEED"] = speed_res;
    Serial.println(String("\tSPEED:\t") + speed_res);
  }

  uint16_t state = 0;
  if (!read_value(state_register, &state)) {
    String state_res;

    if (state == 0)
      state_res = "OK";
    else
      state_res = "ERROR " + state;

    obj["STATE"] = state_res;
    Serial.println(String("\tSTATE:\t") + state_res);
  }

  uint16_t get_freq = 0;
  if (!read_value(get_freq_register, &get_freq)) {
    float get_freq_res = float(get_freq) / 100;

    obj["GET_FREQ"] = get_freq_res;
    Serial.println(String("\tGET_FREQ:\t") + get_freq_res);

    float rpm_res = (get_freq_res * 60 * 2) / 4;
    obj["RPM"] = rpm_res;
    Serial.println(String("\tRPM:\t") + rpm_res);
  }

  uint16_t set_freq = 0;
  if (!read_value(set_freq_register, &set_freq)) {
    float set_freq_res = float(set_freq) / 100;

    obj["SET_FREQ"] = set_freq_res;
    Serial.println(String("\tSET_FREQ:\t") + set_freq_res);
  }

  uint16_t get_motion = 0;
  if (!read_value(get_motion_register, &get_motion)) {
    String get_motion_res;

    if (get_motion == 1)
      get_motion_res = "FWD";
    else if (get_motion == 2)
      get_motion_res = "REV";
    else if (get_motion == 3)
      get_motion_res = "STOP";

    obj["GET_MOTION"] = get_motion_res;
    Serial.println(String("\tGET_MOTION:\t") + get_motion_res);
  }

  uint16_t accel_time = 0;
  if (!read_value(accel_time_register, &accel_time)) {
    obj["ACCEL_TIME"] = accel_time;
    Serial.println(String("\tACCEL_TIME:\t") + accel_time);
  }

  uint16_t decel_time = 0;
  if (!read_value(decel_time_register, &decel_time)) {
    obj["DECEL_TIME"] = decel_time;
    Serial.println(String("\tDECEL_TIME:\t") + decel_time);
  }

  uint16_t get_timer = 0;
  if (!read_value(get_timer_register, &get_timer)) {
    float get_timer_res = float(get_timer) / 10;

    obj["GET_TIMER"] = get_timer_res;
    Serial.println(String("\tGET_TIMER:\t") + get_timer_res);
  }

  uint16_t set_timer = 0;
  if (!read_value(set_timer_register, &set_timer)) {
    float set_timer_res = float(set_timer) / 10;

    obj["SET_TIMER"] = set_timer_res;
    Serial.println(String("\tSET_TIMER:\t") + set_timer_res);
  }
};

String H300::getName() {
  return name;
};

String H300::getCategory() {
  return category;
}