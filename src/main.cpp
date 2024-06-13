#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

AsyncWebServer webserver(80);

String processor(const String &var)
{
  if (var == "TIME")
  {
    return String(millis());
  }

  if (var == "LED"){
    if(digitalRead(LED_BUILTIN)){
      return "AN";
    } else {
      return "OFF";
    }
  }

  return var;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  if (SPIFFS.begin())
  {
    Serial.println("SPIFFS mount OK");
  };

  WiFi.softAP("sneu", NULL);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/index.html", "text/html", false, processor); });

  webserver.serveStatic("/", SPIFFS, "/");

  webserver.on("/on", HTTP_GET, [](AsyncWebServerRequest *request)
               {
      digitalWrite(LED_BUILTIN, HIGH);
      request->send(SPIFFS, "/index.html", "text/html", false, processor); });

  webserver.on("/off", HTTP_GET, [](AsyncWebServerRequest *request)
               {
      digitalWrite(LED_BUILTIN, LOW);
      request->send(SPIFFS, "/index.html", "text/html", false, processor); });
  webserver.begin();
}

void loop()
{
}
