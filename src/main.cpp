#include <Arduino.h>
#include <FastLED.h>

#include "global_defs.h"
#include "led_config.h"
#include "program_options.h"
#include "utility_functions.h"
#include "color_palettes.h"

//----------------------------------------------------------------------------------
// LED definitions
CRGB leds[NUM_LEDS];            // leds array
CRGBSet ledSet(leds, NUM_LEDS); // leds set

// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
const TProgmemRGBPalette16 *ActivePaletteList[] = {
    &RetroC9_p,
    &BlueWhite_p,
    &RainbowColors_p,
    &FairyLight_p,
    &RedGreenWhite_p,
    &PartyColors_p,
    &RedWhite_p,
    &Snow_p,
    &Holly_p,
    &Ice_p};

const uint8_t NUM_PALETTES = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);

CRGBPalette16 gTargetPalette;
CRGBPalette16 gCurrentPalette;
CRGB gBackgroundColor = CRGB::Black;

//----------------------------------------------------------------------------------
// Function Declarations
void chooseNextColorPalette(CRGBPalette16 &pal);
void drawTwinkles(CRGBSet &L);
uint8_t attackDecayWave8(uint8_t i);
void coolLikeIncandescent(CRGB &c, uint8_t phase);
CRGB computeOneTwinkle(uint32_t ms, uint8_t salt);

//----------------------------------------------------------------------------------
void setup()
{
  delay(3000);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS); // .setCorrection(TypicalLEDStrip);
  chooseNextColorPalette(gTargetPalette);
}

//----------------------------------------------------------------------------------
void loop()
{
  EVERY_N_SECONDS(SECONDS_PER_PALETTE)
  {
    chooseNextColorPalette(gTargetPalette);
  }

  EVERY_N_MILLISECONDS(10)
  {
    nblendPaletteTowardPalette(gCurrentPalette, gTargetPalette, 12);
  }

  drawTwinkles(ledSet);

  FastLED.show();
}
