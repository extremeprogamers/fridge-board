
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "ComposerImpl.h"
#include "EndpointDispatcher.h"
#include "DatabaseRepository.h"
#include "ArduinoJson.h"

ESP8266WebServer *server = new ESP8266WebServer(80);
DatabaseRepository *db = new DatabaseRepository();
ComposerImpl *composer = new ComposerImpl();
EndpointDispatcher *dispatcher = new EndpointDispatcher(db, composer);

using namespace std;

void handleRoot() {
  server->send(200, "text/html", dispatcher->getMsgs());
}

void handleDelete() {
  int id = server->arg("messageId").toInt();
  dispatcher->deleteMsg(id);
  server->sendHeader("Location", String("/"), true);
  server->send(302, "text/html", "");
}

void handlePost() {
  String message = server->arg("note");
  Serial.println(message);
  std::string str = message.c_str();
  dispatcher->postMsg(str);
  server->sendHeader("Location", String("/"), true);
  server->send(302, "text/html", "");
}

void sendCss() {
  File file = SPIFFS.open("/materialize.min.css", "r"); // Open it
  server->streamFile(file, "text/css");    // And send it to the client
  file.close();
}

void adminHandler() {
  File file = SPIFFS.open("/Manager.html", "r"); // Open it
  server->streamFile(file, "text/html");    // And send it to the client
  file.close();
}

void settingsHandler() {
  StaticJsonDocument<200> doc;
  File file = SPIFFS.open("/config.json", "w");
  deserializeJson(doc, file);
  for (int i = 0; i < server->args(); i++) {
    String name = server->argName(i);
    String value = server->arg(i);
    Serial.println(name + value);
    doc[name] = value;
  } 
  serializeJson(doc, file);
  file.close();
  server->sendHeader("Location", String("/admin.html"), true);
  server->send(302, "text/html");
}

void handleSwif(){
    StaticJsonDocument<200> doc;
    File file = SPIFFS.open("/config.json", "r");
    deserializeJson(doc, file);
    const char* ssid = doc["ssid"];
    const char* pass = doc["pass"];
    int ip1 = doc["ip1"];
    int ip2 = doc["ip2"];
    int ip3 = doc["ip3"];
    int ip4 = doc["ip4"];

    IPAddress ip(ip1, ip2, ip3, ip4);
    IPAddress gateway(ip1, ip2, ip3, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);
    Serial.begin(9600);
    Serial.println();
    Serial.println(WiFi.localIP());

    Serial.print("Setting soft-AP ... ");
    boolean result = WiFi.softAP(ssid, pass);
}

void setHandler() {
  String ssid = server->arg("ssid");
  String pass = server->arg("pass");
  int ip1 = server->arg("ip1").toInt();
  int ip2 = server->arg("ip2").toInt();
  int ip3 = server->arg("ip3").toInt();
  int ip4 = server->arg("ip4").toInt();   
  IPAddress ip(ip1, ip2, ip3, ip4);
  IPAddress gateway(ip1, ip2, ip3, ip4);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  WiFi.softAP(ssid, pass);
  server->close();
  server = new ESP8266WebServer(80);

  server->on("/materialize.min.css", HTTP_GET, sendCss);
  server->on("/", HTTP_GET, handleRoot);
  server->on("/messages", HTTP_POST, handlePost);
  server->on("/messages/delete", HTTP_POST, handleDelete);
  server->on("/admin.html", HTTP_GET, adminHandler);
  server->on("/admin/settings", HTTP_POST, settingsHandler);
  server->begin();
}

void handleSetup() {
  server->on("/", HTTP_GET, adminHandler);   
  server->on("/admin/settings", HTTP_POST, setHandler);
  server->on("/materialize.min.css", HTTP_GET, sendCss);   
 
  IPAddress ip(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  Serial.begin(9600);
  Serial.println();
  Serial.println(WiFi.localIP());

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESP_INIT_MODE");
}

void setup() {
  SPIFFS.begin();
  handleSetup();
  server->begin();
  Serial.println("HTTP server started");
}

void loop() {
  server->handleClient();
}
