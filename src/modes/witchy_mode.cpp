#include "witchy_mode.h"
#include "../global_defs.h"
#include "../led_config.h"
#include "../utility_functions.h"

using namespace WitchyConstants;

void initWitchyMode(CRGBSet &L)
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
          L[startIndex + j] = CRGB(BASE_PURPLE_R, BASE_PURPLE_G, BASE_PURPLE_B);
        }
      }
    }
  }
}

void updateWitchyMode(CRGBSet &L)
{
  static uint16_t blotchCenters[MAX_BLOTCHES] = {0};
  static uint8_t blotchLife[MAX_BLOTCHES] = {0};

  EVERY_N_MILLISECONDS(MAGIC_INTERVAL)
  {
    // Clear all LEDs first to prevent color addition
    fadeToBlackBy(L, NUM_LEDS, FADE_RATE);

    // Update existing blotches
    for (int i = 0; i < MAX_BLOTCHES; i++)
    {
      if (blotchLife[i] > 0)
      {
        float intensity = sin((float)blotchLife[i] / MAX_BLOTCH_LIFE * PI) * 0.8;

        for (int row = 0; row < NUM_ROWS; row++)
        {
          for (int section = 0; section < SECTIONS_PER_ROW; section++)
          {
            uint16_t startIndex = getLedIndexForSection(row, section);
            for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
            {
              uint16_t currentPos = startIndex + j;
              if (currentPos < NUM_LEDS)
              {
                int16_t distance = abs((int16_t)currentPos - (int16_t)blotchCenters[i]);

                if (distance < BLOTCH_RADIUS)
                {
                  float distanceFactor = 1.0 - (distance / (float)BLOTCH_RADIUS);
                  uint8_t brightness = intensity * 255 * distanceFactor;

                  // Instead of adding colors, we'll set them directly
                  if ((currentPos + blotchLife[i]) % 2 == 0)
                  {
                    // Magical purple
                    CRGB newColor = CRGB(
                        qsub8(brightness * PURPLE_INTENSITY, 50), // Reduced red
                        0,
                        brightness);
                    // Only update if it's brighter than what's there
                    if (newColor.getAverageLight() > L[currentPos].getAverageLight())
                    {
                      L[currentPos] = newColor;
                    }
                  }
                  else
                  {
                    // Witchy green (darker)
                    CRGB newColor = CRGB(
                        0,
                        qsub8(brightness * GREEN_INTENSITY, 50), // Reduced green
                        0);
                    // Only update if it's brighter than what's there
                    if (newColor.getAverageLight() > L[currentPos].getAverageLight())
                    {
                      L[currentPos] = newColor;
                    }
                  }
                }
              }
            }
          }
        }

        blotchLife[i]--;
      }
      else if (random8() < NEW_BLOTCH_CHANCE)
      {
        blotchCenters[i] = random16(NUM_LEDS);
        blotchLife[i] = MAX_BLOTCH_LIFE;
      }
    }

    // Magical surge with controlled colors
    if (random8() < SURGE_CHANCE)
    {
      int row = random8(NUM_ROWS);
      int section = random8(SECTIONS_PER_ROW);
      uint16_t startIndex = getLedIndexForSection(row, section);
      uint8_t sectionLength = SECTION_LENGTHS[row][section];

      for (int j = 0; j < sectionLength; j++)
      {
        if (startIndex + j < NUM_LEDS)
        {
          // Deep purple surge
          L[startIndex + j] = CRGB(
              qsub8(random8(SURGE_PURPLE_MIN, SURGE_PURPLE_MAX), 100), // Reduced red
              0,
              random8(SURGE_PURPLE_MIN, SURGE_PURPLE_MAX));
        }
      }
    }

    // Restore base color only where completely dark
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        uint16_t startIndex = getLedIndexForSection(row, section);
        for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
        {
          if (startIndex + j < NUM_LEDS)
          {
            CRGB &led = L[startIndex + j];
            if (led.getAverageLight() < 3)
            {
              led = CRGB(BASE_PURPLE_R, BASE_PURPLE_G, BASE_PURPLE_B);
            }
          }
        }
      }
    }
  }
}