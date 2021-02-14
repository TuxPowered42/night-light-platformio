#include <ArduinoJson.h>

#include "mqtt_entity.h"
#include "mqtt_helper.h"

mqtt_entity::mqtt_entity(const String &_component, const String &_device_class,
                         const String &_name, const int &_pin,
                         mqtt_helper &_mqtt)
    : component(_component), device_class(_device_class), name(_name),
      mqtt(_mqtt), pin(_pin) {

  id = name;
  id.toLowerCase();
  id.replace(' ', '_');
  topic_base = "homeassistant/" + component + "/" + id;
}

void mqtt_entity::hass_register(const String &topic, const String &action) {
  DynamicJsonDocument json(1024);
  json["name"] = name;
  json["unique_id"] = id;
  if (device_class != "") {
    json["device_class"] = device_class;
  }
  json[topic + "_topic"] = topic_base + "/" + action;

  String topic_config = topic_base + "/config";

  String mqtt_msg;
  serializeJson(json, mqtt_msg);

  Serial.println("Registering MQTT entity: " + topic_config + " " + mqtt_msg);

  mqtt.publish(topic_config, mqtt_msg);
}
