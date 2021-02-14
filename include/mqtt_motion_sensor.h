#pragma once

#include "mqtt_entity.h"
#include <Arduino.h>

class mqtt_motion_sensor : public mqtt_entity {
private:
  int state_last = HIGH;
  int state_prev = HIGH;

public:
  mqtt_motion_sensor(const String &_name, mqtt_helper &_mqtt, const int pin);
  void check_input(void);
};
