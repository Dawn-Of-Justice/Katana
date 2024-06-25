#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <FastLED.h>

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

#define NUM_LEDS 106
#define LED_PIN D0

CRGB leds[NUM_LEDS];
bool ledState = false;
int colorIndex = 0;
bool colorChange = false;
CRGB currentColor = CRGB::Red; // Default color
bool rainbowActive = false;    // Flag to indicate if rainbow mode is active
bool prevTouchState0 = false;  // Previous touch state for electrode 0
bool prevTouchState4 = false;  // Previous touch state for electrode 4

void setup() {
  Serial.begin(9600);
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  uint16_t currtouched = cap.touched();

  // Handle touch on electrode 0
  bool currTouchState0 = currtouched & _BV(0);
  if (currTouchState0 && !prevTouchState0) {  // Detect rising edge
    if (!ledState) {
      fadeIn(currentColor);
      ledState = true;
    } else {
      fadeOut(currentColor);
      ledState = false;
      rainbowActive = false;  // Turn off rainbow mode if LEDs are turned off
    }
  }
  prevTouchState0 = currTouchState0;

  // Handle touch on electrode 4
  bool currTouchState4 = currtouched & _BV(4);
  if (currTouchState4 && !prevTouchState4) {  // Detect rising edge
    if (ledState) {  // Only change color if LEDs are on
      colorChange = true;
      colorIndex = (colorIndex + 1) % 5;  // cycle through 5 colors
    }
  }
  prevTouchState4 = currTouchState4;

  // Handle color change
  if (colorChange) {
    switch (colorIndex) {
      case 0:
        currentColor = CRGB::Red;
        rainbowActive = false;
        fill_solid(leds, NUM_LEDS, currentColor);
        FastLED.show();
        break;
      case 1:
        currentColor = CRGB::White;
        rainbowActive = false;
        fill_solid(leds, NUM_LEDS, currentColor);
        FastLED.show();
        break;
      case 2:
        currentColor = CRGB::Blue;
        rainbowActive = false;
        fill_solid(leds, NUM_LEDS, currentColor);
        FastLED.show();
        break;
      case 3:
        currentColor = CRGB::Green;
        rainbowActive = false;
        fill_solid(leds, NUM_LEDS, currentColor);
        FastLED.show();
        break;
      case 4:
        rainbowActive = true;  // Activate rainbow mode
        break;
    }
    colorChange = false;
  }

  if (rainbowActive && ledState) {
    rainbow();
  }

  delay(20);  // Adjust the delay for smoother animation
}

void fadeIn(CRGB color) {
  for (int i = 0; i < 256; i++) {
    CRGB fadedColor = color;
    fadedColor.nscale8_video(i);  // Scale color by i/256
    fill_solid(leds, NUM_LEDS, fadedColor);
    FastLED.show();
    delay(1);
  }
}

void fadeOut(CRGB color) {
  for (int i = 255; i >= 0; i--) {
    CRGB fadedColor = color;
    fadedColor.nscale8_video(i);  // Scale color by i/256
    fill_solid(leds, NUM_LEDS, fadedColor);
    FastLED.show();
    delay(1);
  }
}

void rainbow() {
  uint16_t millisDiv = millis() / 10;  // Adjust speed of the wave by changing divisor
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Wheel(((i * 256 / NUM_LEDS) + millisDiv) & 255);
  }
  FastLED.show();
}

CRGB Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
