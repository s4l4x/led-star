#include <Arduino.h>
#include <FastLED.h>

#include "global_defs.h"
#include "led_config.h"
#include "modes/pride_mode.h"
#include "modes/halloween_mode.h"
#include "modes/witchy_mode.h"
#include "color_palettes.h"

CRGB leds[NUM_LEDS];
CRGBSet ledSet(leds, NUM_LEDS);
uint8_t gCurrentMode = WITCHY;

const uint8_t SECTION_LENGTHS[NUM_ROWS][SECTIONS_PER_ROW] = {
    {7, 9, 9, 10, 9, 8, 8},
    {10, 11, 10, 9, 9, 11, 8},
    {7, 11, 9, 12, 11, 12, 10}};

void setup()
{
  delay(3000);
  FastLED.addLeds<WS2812, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  switch (gCurrentMode)
  {
  case PRIDE:
    initPrideMode(ledSet, CustomRainbowColors_p);
    break;
  case HALLOWEEN:
    initHalloweenMode(ledSet);
    break;
  case WITCHY:
    initWitchyMode(ledSet);
    break;
  }
}

void loop()
{
  switch (gCurrentMode)
  {
  case PRIDE:
    updatePrideMode(ledSet);
    break;
  case HALLOWEEN:
    updateHalloweenMode(ledSet);
    break;
  case WITCHY:
    updateWitchyMode(ledSet);
    break;
  }

  FastLED.show();
  FastLED.delay(10);
}