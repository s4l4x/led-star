#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

#include <FastLED.h>

#define NUM_ROWS 3
#define SECTIONS_PER_ROW 7
#define NUM_MODES 2

enum LightMode
{
  PRIDE = 0,
  HALLOWEEN = 1
};

extern const uint8_t SECTION_LENGTHS[NUM_ROWS][SECTIONS_PER_ROW];
extern CRGBPalette16 gCurrentPalette;
extern uint8_t gCurrentMode;

// Helper struct to track sections
struct SectionInfo
{
  uint16_t startIndex;
  uint16_t length;
};

#endif // GLOBAL_DEFS_H