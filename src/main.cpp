
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/plain", "hello from esp8266!");
}

void setup(){
  IPAddress ip(192, 168, 11, 23);
  IPAddress gateway(192, 168, 11, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  Serial.begin(9600);
  Serial.println();
  Serial.println(WiFi.localIP());

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPSKAR", "password");
  if (result == true){
    Serial.println("Ready");
  }
  else{
    Serial.println("Failed!");
  }

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
  MDNS.update();
}