#include <Arduino.h>
#include <WiFi.h>

#include "m_wifi.h"
#include "mqtt_helper.h"
#include "mqtt_light.h"
#include "mqtt_motion_sensor.h"

String mqtt_server = "192.168.178.130";
String mqtt_clientid = "client_id";
String mqtt_user = "homeassistant";
String mqtt_pass = "szqRLCxC!Aqu2GMax";

#define MOTION_SENSOR 21
#define NIGHT_LIGHT 22

WiFiClient wifi_client;
MQTTClient mqtt_client(256);

mqtt_helper *mqtt;

mqtt_light *left_light;
mqtt_motion_sensor *left_sensor;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  wifi_start();
  wifi_status();

  mqtt = new mqtt_helper(mqtt_client, wifi_client, mqtt_server, mqtt_clientid,
                         mqtt_user, mqtt_pass);
  left_light = new mqtt_light("Bedroom left light", *mqtt, NIGHT_LIGHT);
  left_sensor =
      new mqtt_motion_sensor("Bedroom left sensor", *mqtt, MOTION_SENSOR);
}

void loop() {
  mqtt->loop();
  left_sensor->check_input();
}
