#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <FastLED.h>
#include "led_config.h"
#include "program_options.h"

void chooseNextColorPalette(CRGBPalette16 &pal);
void drawTwinkles(CRGBSet &L);
uint8_t attackDecayWave8(uint8_t i);
void coolLikeIncandescent(CRGB &c, uint8_t phase);
CRGB computeOneTwinkle(uint32_t ms, uint8_t salt);

#endif // UTILITY_FUNCTIONS_H
