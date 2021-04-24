/***********************************

webserver_demo

running on a
LOLIN(WEMOS)D1 mini Lite

24 April 2021 - gswann

***********************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "secrets.h"

// start instance of web server
ESP8266WebServer server(80);

// blue LED on many ESP8266 board
const int led = 2;

const char* progname = "webserverdemo.ino";
const char* myVersion = "v1.0";

// some versions of the IDE may require these prototypes
// comment out if you don't want them
void handleRoot(void);
void handleGPIO(void);
void handleControl(void);
void handleNotFound(void);

//************************************
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(WiFi_hostname);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(WiFi_hostname)) {
    Serial.println("MDNS responder started");
  }

// these statements make the connection between a path 
// in the URL and the function to handle it

// first one shows the main (root) page
  server.on("/", handleRoot);

// for manual GPIO control as from a HTML file on your PC
  server.on("/GPIO", handleGPIO);

// generates an HTML page with clickable links  
  server.on("/control", handleControl);

// doesn't require a separate handler section
  server.on("/inline", [](){
    String message = "this works as well \n";
    message += "line 2 is here";
    server.send(200, "text/plain", message); 
  });

  server.onNotFound(handleNotFound);

// start the webserver
  server.begin();
  Serial.println("HTTP server started");
}

//************************************
void loop(void){
  server.handleClient();
}
