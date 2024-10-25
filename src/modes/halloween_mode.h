#ifndef HALLOWEEN_MODE_H
#define HALLOWEEN_MODE_H

#include <FastLED.h>

// Main mode functions
void initHalloweenMode(CRGBSet &L);
void updateHalloweenMode(CRGBSet &L);

// Constants specific to spooky Halloween mode
namespace HalloweenConstants
{
  constexpr uint8_t BASE_BRIGHTNESS = 8;
  constexpr uint16_t SPARKLE_INTERVAL = 100;
  constexpr uint8_t FADE_RATE = 60;
  constexpr uint8_t SPARKLE_CHANCE = 32;      // Out of 255
  constexpr uint8_t DRAMATIC_DARK_CHANCE = 5; // Out of 255

  // Flash configuration
  constexpr uint8_t BRIGHT_FLASH_CHANCE = 40; // Out of 255
  constexpr uint8_t FLASH_GREEN_MIN = 200;
  constexpr uint8_t FLASH_GREEN_MAX = 255;
  constexpr uint8_t NEIGHBOR_GLOW_MIN = 20;
  constexpr uint8_t NEIGHBOR_GLOW_MAX = 40;
}

#endif // HALLOWEEN_MODE_H