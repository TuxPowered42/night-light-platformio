#pragma once

#include "mqtt_helper.h"
#include <Arduino.h>

class mqtt_entity {
private:
  String component, device_class, name, id;

protected:
  String topic_base;
  mqtt_helper &mqtt;
  int pin;
  void hass_register(const String &topic, const String &action);

public:
  mqtt_entity(const String &_component, const String &_device_class,
              const String &_name, const int &pin, mqtt_helper &_mqtt);
};
