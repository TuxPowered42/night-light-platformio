#include <Arduino.h>
#include <ArduinoJson.h>

#include "mqtt_entity.h"
#include "mqtt_helper.h"
#include "mqtt_motion_sensor.h"

mqtt_motion_sensor::mqtt_motion_sensor(const String &_name, mqtt_helper &_mqtt,
                                       const int _pin)
    : mqtt_entity("binary_sensor", "motion", _name, _pin, _mqtt) {
  pinMode(pin, INPUT);
  hass_register("state", "state");
};

void mqtt_motion_sensor::check_input(void) {
  state_last = digitalRead(pin);

  if (state_last != state_prev) {
    state_prev = state_last;

    if (state_last == LOW) {
      Serial.println("Motion has stopped");
      mqtt.publish(topic_base + "/state", "OFF");
    }

    if (state_last == HIGH) {
      Serial.println("Motion has started");
      mqtt.publish(topic_base + "/state", "ON");
    }
  }
};
