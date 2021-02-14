#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>

char wifi_ssid[] = "";
char wifi_pass[] = "";

extern WiFiClient wifi_client;

void wifi_start() {
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(wifi_ssid);
    status = WiFi.begin(wifi_ssid, wifi_pass);
    delay(5000);
  }
  Serial.println("Connected to WiFi");
}

void wifi_status() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
