#include "timer.hpp"

Timer::Timer(String timerName) {
  name = timerName;
}

void Timer::init() {
  gettimeofday(&start, NULL);
  gettimeofday(&now, NULL);
  length = 0;

  Serial.println("[timer] ready");
}

String Timer::getName() {
  return name;
}

String Timer::getCategory() {
  return category;
}

int32_t Timer::getRemaining() {
  int32_t diff = length - ((int32_t)now.tv_sec - (int32_t)start.tv_sec);

  if (diff < 0)
    return 0;
  else
    return diff;
}

void Timer::updateStatus() {
  gettimeofday(&now, NULL);

  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  if (status == DEVICE_IN_PROGRESS && getRemaining() == 0) {
    status = DEVICE_DONE;
  }
}

String Timer::getStatus() {
  return DEVICE_STATUS[status];
}

void Timer::appendJsonValues(JsonObject& obj) {
  updateStatus();

  obj["remaining"] = getRemaining();
}

void Timer::executeFunction(JsonDocument& obj) {
  String instruction = obj["instruction"];

  // WAIT
  if (instruction.equals("WAIT") && !obj["params"].isNull()) {
    length = obj["params"].as<int32_t>();
    gettimeofday(&start, NULL);  // get current time
  }
}

void Timer::abort() {
  length = 0;
  status = DEVICE_WAITING;
}