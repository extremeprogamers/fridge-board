
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
  vector<string> messages = db->getAll();
  string message;
  for(auto & element : messages) {
    message += element;
  }
  Serial.println(message.c_str());
}

void handlePost()
{
  String message = server.arg("note");
  char _message[sizeof(message)];
  message.toCharArray(_message, sizeof(_message));
  dispatcher->postMsg(_message);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void handleSSID(){
  String ssid = server.arg("ssid");
  char _ssid[sizeof(ssid)];
  ssid.toCharArray(_ssid, sizeof(_ssid));
  dispatcher->postSsid(_ssid);
  server.sendHeader("Location", String("/manager"), true);
  server.send(302, "text/plain", "");
}

void handlePassword(){
  String password = server.arg("password");
  char _password[sizeof(password)];
  password.toCharArray(_password, sizeof(_password));
  dispatcher->postPassword(_password);
  server.sendHeader("Location", String("/manager"), true);
  server.send(302, "text/plain", "");
}

void handleManager(){
  server.send(200, "text/html", dispatcher->getManager());
}

void sendCss()
{
  File file = SPIFFS.open("/materialize.min.css", "r"); // Open it
  size_t sent = server.streamFile(file, "text/css");    // And send it to the client
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
  boolean result = WiFi.softAP( "ESPSKAR", "password");
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
  server.on("/changessid", HTTP_POST, handleSSID);
  server.on("/changepassword", HTTP_POST, handlePassword);
  server.on("/manager", HTTP_GET, handleManager);

  server.begin();
  Serial.println("HTTP server started");

}

void loop()
{
  server.handleClient();
}
