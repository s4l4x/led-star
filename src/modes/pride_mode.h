#ifndef PRIDE_MODE_H
#define PRIDE_MODE_H

#include <FastLED.h>

void initPrideMode(CRGBSet &L, const CRGBPalette16 &palette);
void updatePrideMode(CRGBSet &L); // Even if currently empty, good to have for consistency

#endif // PRIDE_MODE_H