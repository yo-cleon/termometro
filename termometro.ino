/**************************************************************************
 Ejemplo de apliación para construir un termómetro atmosférico.
 Material requerido:
 1 Esp8266
 1 OLED I2C 168x32
 1 DHT22
 **************************************************************************/

#include <ESP8266WiFi.h>
// https://github.com/arduino-libraries/NTPClient
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
// https://github.com/adafruit/Adafruit_SSD1306
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Configuración de la conexión Wifi
const char* ssid       = "The Burrow";   //Replace with your own SSID
const char* password   = "Ch1m1ch4ng4s?";  //Replace with your own password

// Definición del cliente ntp
WiFiUDP ntpUDP;
// NTPClient timeClient(servidor UDP, servidor ntp, offset (en s), tiempo de actualizacion (en ms);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);


void setup() {
  Serial.begin(115200);

  //Display Text
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Welcome!!");
  display.display();

  // Conexión a la red WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED to WIFI");
  display.setCursor(0, 30);
  display.println("Wi-Fi OK!");
  display.display();
  
  // Inicialización del cliente ntp
  timeClient.begin();
  if (timeClient.isTimeSet() == 0){
    display.setCursor(0, 50);  
    display.println("Time set!");
    display.display();
  }
  delay(2000);
}

void loop() {
  delay(1000);
  timeClient.update();
  printLocalTime();
}

void printLocalTime() {
//  Serial.println(timeClient.getFormattedTime());
  display.clearDisplay();
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(30, 50);
  display.println(timeClient.getFormattedTime());
  display.display();
}
