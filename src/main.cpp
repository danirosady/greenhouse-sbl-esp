#include <ArduinoOTA.h>
#include <WiFi.h>
#include "secret.h"

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  ArduinoOTA.setPassword(auth);
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
}
