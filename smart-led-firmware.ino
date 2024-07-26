#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>
#include <EEPROM.h>
#include "secrets.h"
#include "frontend.h"

// WI-FI
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

IPAddress local_ip(192, 168, 0, 110);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

// FastLED
#define NUM_LEDS 119
#define DATA_PIN D1

CRGB zoneLeds[NUM_LEDS];
CRGB solidLeds[NUM_LEDS];
CRGB* leds = nullptr;

// Server
ESP8266WebServer server(80);

// General
#define SAVE_DELAY 10000
#define TEST_NUMBER 1
#define SWITCH_PIN D2
#define OFF_TIME 200

struct {
  int testNumber;
  int solidRed;
  int solidGreen;
  int solidBlue;
} settings;

void setup() {
  // Serial setup
  Serial.begin(115200);

  // Pins setup

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Wi-Fi setup

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

  // Server setup

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

  // FastLED setup

  Serial.print("Setting up LEDs... ");

  leds = solidLeds;

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  Serial.println("done");

  // Read settings

  Serial.print("Reading settings from EEPROM... ");

  EEPROM.begin(512);

  EEPROM.get(0, settings);

  if (settings.testNumber == TEST_NUMBER) {
    Serial.println("done");
  } else {
    Serial.println("invalid test number (got " + String(settings.testNumber) + ", expected " + String(TEST_NUMBER) + "), setting defaults");

    settings.testNumber = TEST_NUMBER;
    settings.solidRed = 255;
    settings.solidGreen = 255;
    settings.solidBlue = 255;

    saveSettings();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    solidLeds[i].setRGB(settings.solidRed, settings.solidGreen, settings.solidBlue);
  }

  Serial.println("Setup finished");
}

bool solidColorSaveScheduled = false;
unsigned long solidColorSaveTime;
uint8_t brightness = 255;

void loop() {
  server.handleClient();

  if (solidColorSaveScheduled && millis() >= solidColorSaveTime) {
    settings.solidRed = solidLeds[0].red;
    settings.solidGreen = solidLeds[0].green;
    settings.solidBlue = solidLeds[0].blue;

    saveSettings();

    solidColorSaveScheduled = false;
  }

  FastLED.show();
  FastLED.setBrightness(getBrightness());
}

uint8_t getBrightness() {
  static unsigned long changeOnTime = 0;

  static bool wasOn = false;

  bool isOn = !digitalRead(SWITCH_PIN);

  if (isOn != wasOn) {
    wasOn = isOn;

    changeOnTime = millis();
  }

  unsigned long timeDiff = (millis() - changeOnTime) * brightness / OFF_TIME;

  if (timeDiff > brightness) {
    timeDiff = brightness;
  }

  if (isOn) {
    return timeDiff;
  } else {
    return brightness - timeDiff;
  }
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
  server.sendHeader("Access-Control-Allow-Origin", "*", true);
  server.send(200, "text/plain", executeCommands(server.arg("commands")));
}

String executeCommands(String commands) {
  unsigned long startTime = millis();

  String result = "";

  int numSubstrings = 0;
  String* substrings = splitString(commands, ';', numSubstrings);
  for (int i = 0; i < numSubstrings; i++) {
    result += executeCommand(substrings[i]) + ";";
  }

  delete[] substrings;

  return result + String(millis() - startTime);
}

struct RGB {
  int r;
  int g;
  int b;
};

struct RGB hexToRGB(const String& hex) {
  struct RGB rgb;

  rgb.r = strtol(hex.substring(0, 2).c_str(), nullptr, 16);
  rgb.g = strtol(hex.substring(2, 4).c_str(), nullptr, 16);
  rgb.b = strtol(hex.substring(4, 6).c_str(), nullptr, 16);

  return rgb;
}

String executeCommand(String command) {
  String result = "unknown";

  if (command == "get-solid-color") {
    result = String(solidLeds[0].red) + " " + String(solidLeds[0].green) + " " + String(solidLeds[0].blue);
  } else if (command == "get-leds-count") {
    result = String(NUM_LEDS);
  } else if (command == "get-brightness") {
    result = String(brightness);
  } else {
    int numSubstrings = 0;
    String* substrings = splitString(command, ' ', numSubstrings);

    if (substrings[0] == "set-solid-color") {
      int r = substrings[1].toInt();
      int g = substrings[2].toInt();
      int b = substrings[3].toInt();

      for (int i = 0; i < NUM_LEDS; i++) {
        solidLeds[i].setRGB(r, g, b);
      }

      solidColorSaveScheduled = true;
      solidColorSaveTime = millis() + SAVE_DELAY;

      result = "ok";
    } else if (substrings[0] == "set-zones") {
      for (int i = 0; i < NUM_LEDS; i++) {
        int startIndex = i * 6;

        struct RGB rgb = hexToRGB(substrings[1].substring(startIndex, startIndex + 6));

        zoneLeds[i].setRGB(rgb.r, rgb.g, rgb.b);
      }

      result = "ok";
    } else if (substrings[0] == "set-brightness") {
      brightness = substrings[1].toInt();

      result = "ok";
    }

    delete[] substrings;
  }

  return result;
}

void saveSettings() {
  Serial.print("Writing to EEPROM... ");
  EEPROM.put(0, settings);
  EEPROM.commit();
  Serial.println("done");
}