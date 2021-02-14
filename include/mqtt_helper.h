#pragma once

#include <Arduino.h>
#include <MQTT.h>
#include <WiFi.h>
#include <map>

#include "mqtt_entity.h"

typedef void (*callback_func)(mqtt_entity *_mqtt_entity);

class mqtt_helper {
private:
  MQTTClient &mqtt_client;
  WiFiClient &wifi_client;
  String server;
  String client_id;
  String user;
  String pass;
  static std::map<String, callback_func> mqtt_callbacks;
  static std::map<String, mqtt_entity *> mqtt_entities;

public:
  mqtt_helper(MQTTClient &_mqtt_client, WiFiClient &_wifi_client,
              const String &_server, const String &_client_id,
              const String &_user, const String &_pass);
  // bool publish(String &topic, String &payload);
  bool publish(String topic, String payload);
  void loop(void);
  void subscribe(const String &topic, callback_func, mqtt_entity *_mqtt_entity);

  static void callback(String &topic, String &payload);
};
