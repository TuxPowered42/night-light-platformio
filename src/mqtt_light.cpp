#include <Arduino.h>
#include <ArduinoJson.h>

#include "mqtt_entity.h"
#include "mqtt_helper.h"
#include "mqtt_light.h"

mqtt_light::mqtt_light(const String &_name, mqtt_helper &_mqtt, const int _pin)
    : mqtt_entity("light", "", _name, _pin, _mqtt) {
  pinMode(pin, OUTPUT);
  hass_register("command", "switch");
  mqtt.subscribe(topic_base);
};
