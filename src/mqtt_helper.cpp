#include <Arduino.h>
#include <MQTT.h>
#include <WiFI.h>
#include <unordered_map>

#include "mqtt_helper.h"

std::map<String, void *> mqtt_helper::mqtt_callbacks;

mqtt_helper::mqtt_helper(MQTTClient &_mqtt_client, WiFiClient &_wifi_client,
                         const String &_server, const String &_client_id,
                         const String &_user, const String &_pass)
    : mqtt_client(_mqtt_client), wifi_client(_wifi_client), server(_server),
      client_id(_client_id), user(_user), pass(_pass) {

  Serial.println("Starting MQTT  " + server);
  mqtt_client.begin(server.c_str(), wifi_client);
  mqtt_client.onMessage(callback);

  Serial.println("Connecting MQTT " + client_id + " " + user);
  while (!mqtt_client.connect(client_id.c_str(), user.c_str(), pass.c_str())) {

    delay(1000);
  }
  Serial.println("MQTT Connected");
}

bool mqtt_helper::publish(String topic, String payload) {
  bool ret = mqtt_client.publish(topic, payload);
  Serial.println("Sending topic: '" + topic + "' payload: '" + payload + "'");
  return ret;
}

void mqtt_helper::loop(void) { mqtt_client.loop(); }

void mqtt_helper::subscribe(const String &topic, callback_func _callback_func) {
  Serial.println("Subsctibing to '" + topic + "/#'");
  mqtt_client.subscribe(topic + "/#");
  mqtt_callbacks[topic] = callback;
}

void mqtt_helper::callback(String &topic, String &payload) {
  Serial.println("Received opic: '" + topic + "' payload: '" + payload + "'");
}
