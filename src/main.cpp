#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  if (SPIFFS.begin()){
    Serial.println("SPIFFS mount OK");
  };

  WiFi.softAP("sneu", NULL);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void loop()
{
}
