#include <ArduinoOTA.h>
#include <WiFi.h>
#include "secret.h"

#define RESTART_PIN 12
#define LED_PIN_A 13
#define LED_PIN_B 14

int buttonState = 0;

unsigned long ledBOnDuration = 1000;
unsigned long lastButtonPressTime = 0;
bool ledBState = LOW;

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 500;

void setupCompleteCallback() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

void IRAM_ATTR handleButtonPress() {
  ledBState = HIGH; 
  lastButtonPressTime = millis();
  digitalWrite(LED_PIN_B, ledBState);
  ESP.restart();  // Restart
}

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  ArduinoOTA.setPassword(auth);
  ArduinoOTA.begin();
  pinMode(LED_PIN_A, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  pinMode(RESTART_PIN, INPUT_PULLUP);
  Serial.println("Setup complete");
  for(int i = 0; i < 6; i++) {
    setupCompleteCallback();
  }
  attachInterrupt(digitalPinToInterrupt(RESTART_PIN), handleButtonPress, FALLING);
  digitalWrite(LED_PIN_B, LOW);
  }

void loop() {
  ArduinoOTA.handle();

  if (millis() - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = millis();

    // Toggle LED A
    digitalWrite(LED_PIN_A, !digitalRead(LED_PIN_A)); 
  }

  if (ledBState == HIGH && millis() - lastButtonPressTime >= ledBOnDuration) {
  digitalWrite(LED_PIN_B, LOW);  // Matikan LED 2
  ledBState = LOW;  // Status Matikan LED 2
  }
}
