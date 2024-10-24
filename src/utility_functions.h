#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <FastLED.h>

void setPrideMode(CRGBSet &L, const CRGBPalette16 &palette);
void setHalloweenMode(CRGBSet &L);
void updateHalloweenSparkles(CRGBSet &L);
uint16_t getLedIndexForSection(uint8_t row, uint8_t section);

#endif // UTILITY_FUNCTIONS_H