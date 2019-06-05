
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "ComposerImpl.h"
#include "EndpointDispatcher.h"
#include "DatabaseRepository.h"

ESP8266WebServer server(80);
DatabaseRepository *db = new DatabaseRepository();
ComposerImpl *composer = new ComposerImpl();
EndpointDispatcher *dispatcher = new EndpointDispatcher(db, composer);

void handleRoot()
{
  server.send(200, "text/html", dispatcher->getMsgs());
}

void handleDelete()
{
  int id = server.arg("messageId").toInt();
  dispatcher->deleteMsg(id);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/html", "");
}

void handlePost()
{
  String message = server.arg("note");
  char _message[sizeof(message)];
  message.toCharArray(_message, sizeof(_message));
  dispatcher->postMsg(_message);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/html", "");
}

void sendCss()
{
  File file = SPIFFS.open("/materialize.min.css", "r"); // Open it
  server.streamFile(file, "text/css");    // And send it to the client
  file.close();
}

void setup()
{

  SPIFFS.begin();
  IPAddress ip(192, 168, 11, 23);
  IPAddress gateway(192, 168, 11, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
  Serial.begin(115200);
  Serial.println();
  Serial.println(WiFi.localIP());

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("ESPSKAR", "password");
  if (result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }

  server.on("/materialize.min.css", HTTP_GET, sendCss);
  server.on("/", handleRoot);
  server.on("/messages", HTTP_POST, handlePost);
  server.on("/messages/delete", HTTP_POST, handleDelete);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
