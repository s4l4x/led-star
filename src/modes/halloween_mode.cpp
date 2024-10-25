#include "halloween_mode.h"
#include "../global_defs.h"
#include "../led_config.h"
#include "../utility_functions.h" // Add this include

void initHalloweenMode(CRGBSet &L)
{
  for (int row = 0; row < NUM_ROWS; row++)
  {
    for (int section = 0; section < SECTIONS_PER_ROW; section++)
    {
      uint16_t startIndex = getLedIndexForSection(row, section);
      for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
      {
        if (startIndex + j < NUM_LEDS)
        {
          L[startIndex + j] = CRGB(0, 32, 0); // Dark green base
        }
      }
    }
  }
}

void updateHalloweenMode(CRGBSet &L)
{
  static const uint16_t SPARKLE_INTERVAL = 50;

  EVERY_N_MILLISECONDS(SPARKLE_INTERVAL)
  {
    // Add sparkles section by section
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        if (random8() < 64)
        { // 25% chance to sparkle in this section
          uint16_t startIndex = getLedIndexForSection(row, section);
          uint8_t sectionLength = SECTION_LENGTHS[row][section];

          uint8_t numSparkles = random8(1, 4);
          for (int i = 0; i < numSparkles; i++)
          {
            uint16_t pos = startIndex + random8(sectionLength);
            if (pos < NUM_LEDS)
            {
              L[pos] = CRGB(0, random8(180, 255), 0);
            }
          }
        }
      }
    }

    fadeToBlackBy(L, NUM_LEDS, 40);

    // Restore base color
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        uint16_t startIndex = getLedIndexForSection(row, section);
        for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
        {
          if (startIndex + j < NUM_LEDS && L[startIndex + j].g < 32)
          {
            L[startIndex + j] = CRGB(0, 32, 0);
          }
        }
      }
    }
  }
}
