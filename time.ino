#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "APTO 26";
const char* password = "pjcandez25";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600, 60000); // -3h = GMT-3 (Brasil), atualiza a cada 60s

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();

  lcd.clear();
}

void loop() {
  timeClient.update();

  lcd.setCursor(0, 0);
  lcd.print("Hora:");
  
  lcd.setCursor(0, 1);
  lcd.print(timeClient.getFormattedTime());

  delay(1000);
}
