# smart-led-firmware

Firmware for controlling smart LED strip via Web GUI or serial port. Initially developed for NodeMCU v3.

## Usage

-   Define your Wi-Fi SSID & password in the secrets.h:
    ```c
    #define WIFI_SSID     "SSID"
    #define WIFI_PASSWORD "PASSWORD"
    ```

## Web GUI

The source code for the Web GUI is stored [here](https://github.com/kd3n1z/smart-led-web-gui). This repository always contains the latest build (automatically updated via [Github Actions](https://github.com/kd3n1z/smart-led-web-gui/blob/main/.github/workflows/bump-firmware.yml))

## Dependencies

-   [ESP8266 boards](http://arduino.esp8266.com/stable/package_esp8266com_index.json)
-   [FastLED](https://github.com/FastLED/FastLED)
