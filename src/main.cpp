#include <ArduinoOTA.h>
#include <WiFiManager.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "secret.h"

WiFiManager wm;
int timeout_hotspot = 120;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 3600000);

const int sleepStartHour = 180;   // 18:00 (6:00 PM)
const int sleepStartMinute = 0;  // 00 minutes
const int sleepEndHour = 610;      // 06:00 (6:00 AM)
const int sleepEndMinute = 10;    // 00 minutes

#define RESTART_PIN 12
#define LED_PIN_A 13
#define LED_PIN_B 14

int buttonState = 0;

unsigned long ledBOnDuration = 1000;
unsigned long lastButtonPressTime = 0;
bool ledBState = LOW;

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000;

unsigned long lastCheckTime = 0; 
const unsigned long checkInterval = 60000; //3600000 

void setupCompleteCallback() {
  digitalWrite(LED_PIN_A, HIGH);
  delay(100);
  digitalWrite(LED_PIN_A, LOW);
  delay(100);
}

void IRAM_ATTR handleButtonPress() {
  ledBState = HIGH; 
  lastButtonPressTime = millis();
  digitalWrite(LED_PIN_B, ledBState);
  ESP.restart();  // Restart
}

void setup() {
  Serial.begin(115200);
  bool res = wm.autoConnect(ssid, password); 
  if (res) {
    Serial.println("Terhubung... :)");
    delay(100);
    timeClient.begin();
    Serial.println("Mendapatkan waktu... ");
    delay(2000);
    timeClient.update();
    Serial.print("Waktu sekarang: ");
    Serial.println(timeClient.getFormattedTime());
  } else {
    Serial.println("Gagal mengkoneksikan Wi-Fi");
    delay(100);

    wm.setConfigPortalTimeout(timeout_hotspot);
    if (!wm.startConfigPortal(hotspot_ssid, hotspot_password)) {
      Serial.println("Gagal mengkoneksikan Wi-Fi dan waktu habis");
      delay(100);
      ESP.restart();
      delay(100);
      Serial.println("Restarting");
    } else {
      Serial.println("Terhubung ke Wi-Fi setelah dikonfigurasi!");
      delay(100);
    }
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
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Wi-Fi status: ");
    Serial.println(WiFi.status());
    Serial.println("Wi-Fi terputus, memulai config portal...");
    wm.startConfigPortal(hotspot_ssid, hotspot_password);
  }

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
