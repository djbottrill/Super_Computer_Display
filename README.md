# Super_Computer_Display
Flashing LED Matrix "Super Computer" display inspired by bigclivedotcom

"Super Computer" display inspired by bigclivedotcom https://www.youtube.com/watch?v=H1k7mxhWQ5Q
uses 4 FC16 type MAX7219 8x32 dot matrix display modules
flashes each pixel at a random speed between dly_min and dly_max
LEDs initially flash in phase but slowly the display become more random
Pinout is for an ESP8266 but this should work faster Arduino compatible boards such as:
ESP8266, ESP32, STM32 BluePill, Adafruit Feather SAMD21 / SAMD51 etc,
Uses Majic Designs MD_MAX72xx library https://github.com/MajicDesigns/MD_MAX72XX
