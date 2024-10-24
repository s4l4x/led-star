// In main.cpp
#include <Arduino.h>
#include <FastLED.h>

#include "global_defs.h"
#include "led_config.h"
#include "utility_functions.h"
#include "color_palettes.h"

CRGB leds[NUM_LEDS];
CRGBSet ledSet(leds, NUM_LEDS);
uint8_t gCurrentMode = HALLOWEEN; // Set initial mode

// The actual section lengths array
const uint8_t SECTION_LENGTHS[NUM_ROWS][SECTIONS_PER_ROW] = {
    {7, 9, 9, 10, 9, 8, 8},
    {10, 11, 10, 9, 9, 11, 8},
    {7, 11, 9, 12, 11, 12, 10}};

void setup()
{
  delay(3000);
  FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Initialize based on mode
  if (gCurrentMode == PRIDE)
  {
    setPrideMode(ledSet, CustomRainbowColors_p);
  }
  else if (gCurrentMode == HALLOWEEN)
  {
    setHalloweenMode(ledSet);
  }
}

void loop()
{
  if (gCurrentMode == PRIDE)
  {
    // Pride mode is static, no updates needed
    FastLED.show();
  }
  else if (gCurrentMode == HALLOWEEN)
  {
    updateHalloweenSparkles(ledSet);
    FastLED.show();
  }
  FastLED.delay(10);
}