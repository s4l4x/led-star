#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

#include <FastLED.h>

extern const TProgmemRGBPalette16 *ActivePaletteList[];
extern const uint8_t NUM_PALETTES;
extern CRGBPalette16 gCurrentPalette;
extern CRGBPalette16 gTargetPalette;

// Background color for 'unlit' pixels
// Can be set to CRGB::Black if desired.
// Example of dim incandescent fairy light background color
// CRGB gBackgroundColor = CRGB(CRGB::FairyLight).nscale8_video(16);
extern CRGB gBackgroundColor;

#endif // GLOBAL_DEFS_H
