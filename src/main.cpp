
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "ComposerImpl.h"
#include "EndpointDispatcher.h"
#include "DatabaseRepository.h"
#include "ArduinoJson.h"

ESP8266WebServer server(80);
DatabaseRepository *db = new DatabaseRepository();
ComposerImpl *composer = new ComposerImpl();
EndpointDispatcher *dispatcher = new EndpointDispatcher(db, composer);

using namespace std;

void handleRoot() {
  server.send(200, "text/html", dispatcher->getMsgs());
}

void handleDelete() {
  int id = server.arg("messageId").toInt();
  dispatcher->deleteMsg(id);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/html", "");
}

void handlePost() {
  String message = server.arg("note");
  Serial.println(message);
  std::string str = message.c_str();
  dispatcher->postMsg(str);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/html", "");
}

void sendCss() {
  File file = SPIFFS.open("/materialize.min.css", "r"); // Open it
  server.streamFile(file, "text/css");    // And send it to the client
  file.close();
}

void adminHandler() {
  File file = SPIFFS.open("/Manager.html", "r"); // Open it
  server.streamFile(file, "text/html");    // And send it to the client
  file.close();
}

void settingsHandler() {
  StaticJsonDocument<200> doc;
  File file = SPIFFS.open("/config.json", "w");
  deserializeJson(doc, file);
  for (int i = 0; i < server.args(); i++) {
    String name = server.argName(i);
    String value = server.arg(i);
    Serial.println(name + value);
    doc[name] = value;
  } 
  serializeJson(doc, file);
  file.close();
  server.sendHeader("Location", String("/Manager.html"), true);
  server.send(302, "text/html", "");
}

void handleSwif(){
    StaticJsonDocument<200> doc;
    File file = SPIFFS.open("/config.json", "r");
    deserializeJson(doc, file);
    const char* ssid = doc["ssid"];
    const char* pass = doc["pass"];
    IPAddress ip(192, 168, 11, 23);
    IPAddress gateway(192, 168, 11, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);
    Serial.begin(9600);
    Serial.println();
    Serial.println(WiFi.localIP());

    Serial.print("Setting soft-AP ... ");
    boolean result = WiFi.softAP(ssid, pass);
    if (result == true)
    {
      Serial.println("Ready");
    }
    else
    {
      Serial.println("Failed!");
    }
}

void setup() {

  SPIFFS.begin();

  handleSwif();

  server.on("/materialize.min.css", HTTP_GET, sendCss);
  server.on("/", handleRoot);
  server.on("/messages", HTTP_POST, handlePost);
  server.on("/messages/delete", HTTP_POST, handleDelete);
  server.on("/admin.html", HTTP_GET, adminHandler);
  server.on("/admin/settings", HTTP_POST, settingsHandler);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
