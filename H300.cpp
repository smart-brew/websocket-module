/**
 * Original authors: http://team18-19.studenti.fiit.stuba.sk/
 */

#include "H300.hpp"

H300::H300(const uint8_t slave_id, String _name) : slave_id(slave_id) {
  name = _name;
}

void H300::init() {
  // Modbus communication through hardware bus
  node.begin(slave_id, serial_bus);

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

/**
 * @brief Writes value to register
 *
 * @param register_addr Register to write
 * @param value Value to write
 * @return Code of modbus request (0x00 for success)
 */
uint8_t H300::write_value(const uint16_t register_addr, const uint16_t value) const {
  return node.writeSingleRegister(register_addr, value);
}

/**
 * @brief Reads value from register and saves it to response
 *
 * @param register_addr Register to read
 * @param response Return value
 * @return Code of modbus request (0x00 for success)
 */
uint8_t H300::read_value(const uint16_t register_addr, uint16_t* const response) const {
  const uint8_t code = node.readHoldingRegisters(register_addr, 1);

  Serial.print("H300::read_value (response_code): ");
  Serial.println(code);

  if (code == node.ku8MBSuccess)
    *response = node.getResponseBuffer(0);

  return code;
}

float H300::get() {
  uint16_t speed = 0;
  if (!read_value(speed_register, &speed)) {
    float speed_res = float(speed) / 10;
    return speed_res;
  }
  return speed;
};

void H300::appendJsonValues(JsonObject& obj) {
  uint16_t speed = 0;
  if (!read_value(speed_register, &speed)) {
    float speed_res = float(speed) / 10;

    obj["speed"] = speed_res;
    Serial.println(String("\tSPEED:\t") + speed_res);
  }

  uint16_t state = 0;
  if (!read_value(state_register, &state)) {
    String state_res;

    if (state == 0)
      state_res = "OK";
    else
      state_res = "ERROR " + state;

    obj["state"] = state_res;
    Serial.println(String("\tSTATE:\t") + state_res);
  }

  uint16_t get_freq = 0;
  if (!read_value(get_freq_register, &get_freq)) {
    float get_freq_res = float(get_freq) / 100;

    obj["get_freq"] = get_freq_res;
    Serial.println(String("\tGET_FREQ:\t") + get_freq_res);

    float rpm_res = (get_freq_res * 60 * 2) / 4;
    obj["rpm"] = rpm_res;
    Serial.println(String("\tRPM:\t") + rpm_res);
  }

  uint16_t set_freq = 0;
  if (!read_value(set_freq_register, &set_freq)) {
    float set_freq_res = float(set_freq) / 100;

    obj["set_freq"] = set_freq_res;
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

    obj["get_motion"] = get_motion_res;
    Serial.println(String("\tGET_MOTION:\t") + get_motion_res);
  }

  uint16_t accel_time = 0;
  if (!read_value(accel_time_register, &accel_time)) {
    obj["accel_time"] = accel_time;
    Serial.println(String("\tACCEL_TIME:\t") + accel_time);
  }

  uint16_t decel_time = 0;
  if (!read_value(decel_time_register, &decel_time)) {
    obj["decel_time"] = decel_time;
    Serial.println(String("\tDECEL_TIME:\t") + decel_time);
  }

  uint16_t get_timer = 0;
  if (!read_value(get_timer_register, &get_timer)) {
    float get_timer_res = float(get_timer) / 10;

    obj["get_timer"] = get_timer_res;
    Serial.println(String("\tGET_TIMER:\t") + get_timer_res);
  }

  uint16_t set_timer = 0;
  if (!read_value(set_timer_register, &set_timer)) {
    float set_timer_res = float(set_timer) / 10;

    obj["set_timer"] = set_timer_res;
    Serial.println(String("\tSET_TIMER:\t") + set_timer_res);
  }
};

String H300::getName() {
  return name;
};

String H300::getCategory() {
  return category;
}

void H300::set_motion(String type) {
  if (type == "FWD") write_value(H300::set_motion_register, 1);
  if (type == "REV") write_value(H300::set_motion_register, 2);
  if (type == "FWD_JOG") write_value(H300::set_motion_register, 3);
  if (type == "REV_JOG") write_value(H300::set_motion_register, 4);
  if (type == "STOP") write_value(H300::set_motion_register, 5);
  if (type == "BREAK") write_value(H300::set_motion_register, 6);
}

void H300::executeFunction(JsonDocument& obj) {
  if (obj["param"].isNull()) return;

  String instruction = obj["instruction"];
  const char* value = obj["param"];

  if (instruction.equals("SET_MOTOR_SPEED")) {
    set_motion("FWD");
    write_value(H300::speed_register, (uint16_t)(atof(value) * 10));
  } else if (instruction.equals("SET_FREQ")) {
    write_value(H300::set_freq_register, (uint16_t)(atof(value) * 100));
  } else if (instruction.equals("ACCEL_TIME")) {
    write_value(H300::accel_time_register, (uint16_t)atoi(value));
  } else if (instruction.equals("DECEL_TIME")) {
    write_value(H300::decel_time_register, (uint16_t)atoi(value));
  } else if (instruction.equals("SET_TIMER")) {
    write_value(H300::set_timer_register, (uint16_t)(atof(value) * 10));
  }
}

String H300::getStatus() {
  return DEVICE_STATUS[status];
}

void H300::abort() {
  set_motion("STOP");
  status = DEVICE_WAITING;
}