#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

#include <FastLED.h>

#define NUM_ROWS 3
#define SECTIONS_PER_ROW 7

extern const uint8_t SECTION_LENGTHS[NUM_ROWS][SECTIONS_PER_ROW];

extern CRGBPalette16 gCurrentPalette;

#endif // GLOBAL_DEFS_H