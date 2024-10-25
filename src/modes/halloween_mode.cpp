#include "halloween_mode.h"
#include "../global_defs.h"
#include "../led_config.h"
#include "../utility_functions.h"

using namespace HalloweenConstants;

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
          L[startIndex + j] = CRGB(0, BASE_BRIGHTNESS, 0); // Dark green base
        }
      }
    }
  }
}

void updateHalloweenMode(CRGBSet &L)
{
  EVERY_N_MILLISECONDS(SPARKLE_INTERVAL)
  {
    // Random chance for entire pattern to go very dark
    if (random8() < DRAMATIC_DARK_CHANCE)
    {
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
          if (random8() < BRIGHT_FLASH_CHANCE)
          {
            uint16_t pos = startIndex + random8(sectionLength);
            if (pos < NUM_LEDS)
            {
              // Create a bright flash with a slight color variation
              L[pos] = CRGB(
                  random8(0, 20),                            // Slight red tinge
                  random8(FLASH_GREEN_MIN, FLASH_GREEN_MAX), // Bright green
                  0);

              // Add dim glow to neighboring LEDs
              if (pos > 0 && pos < NUM_LEDS - 1)
              {
                L[pos - 1] = CRGB(0, random8(NEIGHBOR_GLOW_MIN, NEIGHBOR_GLOW_MAX), 0);
                L[pos + 1] = CRGB(0, random8(NEIGHBOR_GLOW_MIN, NEIGHBOR_GLOW_MAX), 0);
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

    // Restore very dim base color where completely dark
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        uint16_t startIndex = getLedIndexForSection(row, section);
        for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
        {
          if (startIndex + j < NUM_LEDS && L[startIndex + j].g < BASE_BRIGHTNESS)
          {
            L[startIndex + j] = CRGB(0, BASE_BRIGHTNESS, 0);
          }
        }
      }
    }
  }
}