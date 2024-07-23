#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include "secrets.h"
#include "frontend.h"

// WI-FI
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

IPAddress local_ip(192, 168, 0, 110);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// FastLED
#define NUM_LEDS 120
#define DATA_PIN D1

CRGB leds[NUM_LEDS];

// Server
ESP8266WebServer server(80);

void setup() {
  // General Setup
  Serial.begin(115200);

  // Wi-Fi Setup

  Serial.print("Connecting to " + String(ssid) + "... ");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(local_ip, gateway, subnet);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.print("done! IP: ");
  Serial.println(WiFi.localIP());

  // Server Setup

  Serial.print("Starting HTTP server... ");

  SETUP_FRONTEND_SERVER();  // defined in frontend.h
  server.on("/", []() {
    server.sendHeader("Location", String("/gui/"), true);
    server.send(302, "text/plain", "");
  });
  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("done");

  // FastLED Setup

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  Serial.println("Setup finished");
}

void loop() {
  server.handleClient();

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(255, 162, 57);
  }

  FastLED.show();
}