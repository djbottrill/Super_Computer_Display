// "Super Computer" display inspired by bigclivedotcom https://www.youtube.com/watch?v=H1k7mxhWQ5Q
// uses 4 FC16 type MAX7219 8x32 dot matrix display modules
// flashes each pixel at a randomw speed between dly_min and dly_max
// LED initially flash in phase but slowly the display become more random
// Pinout is for an ESP8266 but this should work faster Arduino compatible boards such as:
// ESP8266, ESP32, STM32 BluePill, Adafruit Feather SAMD21 / SAMD51 etc,
// Uses Majic Designs MD_MAX72xx library https://github.com/MajicDesigns/MD_MAX72XX

#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  16

//SPI definitions for ESP8266
#define CLK_PIN   D5  // or SCK
#define DATA_PIN  D7  // or MOSI
#define CS_PIN    D8  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int dly_min = 300;                            //Minimum time period for on and off
const int dly_max = 390;                            //Maximum timer period for on and off

int r , c;                                          //Row and Column variables
uint32_t p[8][256];                                 //Pixel timer buffer 
uint32_t m;                                         //Current snapshot time

void setup() {
  mx.begin();                                       //Start display, all pixels will be off
  mx.control(MD_MAX72XX::INTENSITY, 0);             //Set display intensity 0 - 15

//Set intial randowm time for each pixel 
  m = millis();
  for (r = 0; r < 8; r++) {                         //Loop through all rows and columns
    for (c = 0; c < 256; c++) {
      p[r][c] = m + random(dly_min, dly_max);       //Generate a randow time for first change
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);  //Turn off automatic display updates
}

void loop() {

  m = millis();                                     //Get current timr
  for (r = 0; r < 8; r++) {                         //Loop through all rows and columns
    for (c = 0; c < 256; c++) {
      if (m > p[r][c]) {                            //is it time to toggle pixel ?
        p[r][c] = m + random(dly_min, dly_max);     //Calculate a new randow time for next change
        mx.setPoint(r, c, !mx.getPoint(r,c));       //Toggle Pixel
      }
    }
  }
  mx.update();                                      //Update the entire display

}
