#pragma once

#include "mqtt_entity.h"
#include <Arduino.h>

class mqtt_light : public mqtt_entity {
public:
  mqtt_light(const String &_name, mqtt_helper &_mqtt, const int pin);
};
