#include "utility_functions.h"
#include "global_defs.h"
#include "led_config.h"

void setPrideMode(CRGBSet &L, const CRGBPalette16 &palette)
{
  const CRGB rainbow[] = {
      CRGB(255, 0, 0),   // Red
      CRGB(255, 127, 0), // Orange
      CRGB(255, 255, 0), // Yellow
      CRGB(0, 255, 0),   // Green
      CRGB(0, 0, 255),   // Blue
      CRGB(75, 0, 130),  // Indigo (standard)
      CRGB(143, 0, 255)  // Violet (standard)
  };

  int ledIndex = 0;

  for (int row = 0; row < NUM_ROWS; row++)
  {
    for (int i = 0; i < SECTIONS_PER_ROW; i++)
    {
      CRGB color;
      if (row == 2 && i == SECTIONS_PER_ROW - 2)
      {
        // Second to last section of third row (Indigo)
        color = CRGB(10, 0, 255); // Increased blue, reduced red for Indigo
      }
      else if (row == 2 && i == SECTIONS_PER_ROW - 1)
      {
        // Last section of third row (Violet)
        color = CRGB(15, 0, 255); // Increased blue, adjusted red for Violet
      }
      else
      {
        int colorIndex = (row % 2 == 0) ? i : (SECTIONS_PER_ROW - 1 - i);
        color = rainbow[colorIndex];
      }

      for (int j = 0; j < SECTION_LENGTHS[row][i]; j++)
      {
        if (ledIndex < NUM_LEDS)
        {
          L[ledIndex] = color;
          ledIndex++;
        }
      }
    }
  }

  // Turn off any remaining LEDs
  while (ledIndex < NUM_LEDS)
  {
    L[ledIndex] = CRGB::Black;
    ledIndex++;
  }
}

uint16_t getLedIndexForSection(uint8_t row, uint8_t section)
{
  uint16_t index = 0;
  // Calculate starting index for the given section
  for (int r = 0; r < row; r++)
  {
    for (int s = 0; s < SECTIONS_PER_ROW; s++)
    {
      index += SECTION_LENGTHS[r][s];
    }
  }
  for (int s = 0; s < section; s++)
  {
    index += SECTION_LENGTHS[row][s];
  }
  return index;
}

void setHalloweenMode(CRGBSet &L)
{
  int ledIndex = 0;

  // Set base color for each section
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

  // Turn off any remaining LEDs
  while (ledIndex < NUM_LEDS)
  {
    L[ledIndex] = CRGB::Black;
    ledIndex++;
  }
}

void updateHalloweenSparkles(CRGBSet &L)
{
  static uint16_t lastSparkleTime = 0;
  static const uint16_t SPARKLE_INTERVAL = 100;

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

          // Add 1-3 sparkles within this section
          uint8_t numSparkles = random8(1, 4);
          for (int i = 0; i < numSparkles; i++)
          {
            uint16_t pos = startIndex + random8(sectionLength);
            if (pos < NUM_LEDS)
            {
              // Vary the green intensity for more dynamic sparkles
              L[pos] = CRGB(0, random8(180, 255), 0);
            }
          }
        }
      }
    }

    // Fade all LEDs slightly
    fadeToBlackBy(L, NUM_LEDS, 40);

    // Restore base color section by section
    for (int row = 0; row < NUM_ROWS; row++)
    {
      for (int section = 0; section < SECTIONS_PER_ROW; section++)
      {
        uint16_t startIndex = getLedIndexForSection(row, section);
        for (int j = 0; j < SECTION_LENGTHS[row][section]; j++)
        {
          if (startIndex + j < NUM_LEDS)
          {
            if (L[startIndex + j].g < 32)
            {                                     // If LED has faded too much
              L[startIndex + j] = CRGB(0, 32, 0); // Reset to base dark green
            }
          }
        }
      }
    }
  }
}