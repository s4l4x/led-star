#include "halloween_mode.h"
#include "../global_defs.h"
#include "../led_config.h"
#include "../utility_functions.h"

void initHalloweenMode(CRGBSet &L)
{
  // Initialize with much darker base color
  for (int row = 0; row < NUM_ROWS; row++)
  {
    for (int section = 0; section < SECTIONS_PER_ROW; section++)
    {
      uint16_t startIndex = getLedIndexForSection(row, section);
      for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
      {
        if (startIndex + j < NUM_LEDS)
        {
          L[startIndex + j] = CRGB(0, 8, 0); // Much darker green base
        }
      }
    }
  }
}

void updateHalloweenMode(CRGBSet &L)
{
  static const uint16_t SPARKLE_INTERVAL = 100; // Slower interval for more darkness
  static const uint8_t SPARKLE_CHANCE = 32;     // Lower chance (12.5%) for rarer sparkles
  static const uint8_t FADE_RATE = 60;          // Faster fade for more dramatic effect

  EVERY_N_MILLISECONDS(SPARKLE_INTERVAL)
  {
    // Random chance for entire pattern to go very dark
    if (random8() < 5)
    {                                  // 2% chance
      fadeToBlackBy(L, NUM_LEDS, 200); // Quick fade to near-black
    }

    // Add sparkles section by section
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        if (random8() < SPARKLE_CHANCE)
        {
          uint16_t startIndex = getLedIndexForSection(row, section);
          uint8_t sectionLength = SECTION_LENGTHS[row][section];

          // Occasionally add a brighter flash
          if (random8() < 40)
          { // 15% chance for a bright flash
            uint16_t pos = startIndex + random8(sectionLength);
            if (pos < NUM_LEDS)
            {
              // Create a bright flash with a slight color variation
              L[pos] = CRGB(
                  random8(0, 20),    // Slight red tinge
                  random8(200, 255), // Bright green
                  0);

              // Add dim glow to neighboring LEDs
              if (pos > 0 && pos < NUM_LEDS - 1)
              {
                L[pos - 1] = CRGB(0, random8(20, 40), 0);
                L[pos + 1] = CRGB(0, random8(20, 40), 0);
              }
            }
          }
          else
          {
            // Regular, dimmer sparkle
            uint16_t pos = startIndex + random8(sectionLength);
            if (pos < NUM_LEDS)
            {
              L[pos] = CRGB(0, random8(64, 128), 0);
            }
          }
        }
      }
    }

    // Faster fade rate for spookier effect
    fadeToBlackBy(L, NUM_LEDS, FADE_RATE);

    // Restore very dim base color only where completely dark
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        uint16_t startIndex = getLedIndexForSection(row, section);
        for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
        {
          if (startIndex + j < NUM_LEDS && L[startIndex + j].g < 8)
          {
            L[startIndex + j] = CRGB(0, 8, 0); // Very dim base
          }
        }
      }
    }
  }
}