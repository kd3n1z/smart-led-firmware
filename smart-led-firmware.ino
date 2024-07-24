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

CRGB solidLeds[NUM_LEDS];
CRGB* leds = nullptr;

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
  server.on("/api", handle_api_request);
  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("done");

  // FastLED Setup

  leds = solidLeds;

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  Serial.println("Setup finished");

  for (int i = 0; i < NUM_LEDS; i++) {
    solidLeds[i].setRGB(255, 0, 0);
  }
}

void loop() {
  server.handleClient();

  FastLED.show();
}

String* splitString(String data, char delimiter, int& numSubstrings) {
  numSubstrings = 1;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == delimiter) {
      numSubstrings++;
    }
  }

  String* substrings = new String[numSubstrings];
  int currentIndex = 0;
  int startIndex = 0;
  int endIndex = data.indexOf(delimiter);

  while (endIndex > 0) {
    substrings[currentIndex] = data.substring(startIndex, endIndex);
    currentIndex++;
    startIndex = endIndex + 1;
    endIndex = data.indexOf(delimiter, startIndex);
  }

  substrings[currentIndex] = data.substring(startIndex);

  return substrings;
}

void handle_api_request() {
  String commands = server.arg("commands");

  Serial.println(commands);

  int numSubstrings = 0;
  String* substrings = splitString(commands, ';', numSubstrings);

  for (int i = 0; i < numSubstrings; i++) {
    executeCommand(substrings[i]);
  }

  delete[] substrings;

  server.send(200, "text/plain", "ok");
}


void executeCommand(String command) {
  int numSubstrings = 0;
  String* substrings = splitString(command, ' ', numSubstrings);

  if (substrings[0] == "set-solid-color") {
    int r = substrings[1].toInt();
    int g = substrings[2].toInt();
    int b = substrings[3].toInt();

    for (int i = 0; i < NUM_LEDS; i++) {
      solidLeds[i].setRGB(r, g, b);
    }
  }

  delete[] substrings;
}