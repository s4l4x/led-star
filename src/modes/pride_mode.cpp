#include "pride_mode.h"
#include "../global_defs.h"
#include "../led_config.h"

void initPrideMode(CRGBSet &L, const CRGBPalette16 &palette)
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
        color = CRGB(10, 0, 255); // Indigo
      }
      else if (row == 2 && i == SECTIONS_PER_ROW - 1)
      {
        color = CRGB(15, 0, 255); // Violet
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

  while (ledIndex < NUM_LEDS)
  {
    L[ledIndex] = CRGB::Black;
    ledIndex++;
  }
}

void updatePrideMode(CRGBSet &L)
{
  // Static display, no updates needed
}