#include "utility_functions.h"
#include "global_defs.h"
#include "led_config.h"

// In utility_functions.cpp

void setRainbowSections(CRGBSet &L, const CRGBPalette16 &palette)
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