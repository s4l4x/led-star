#ifndef WITCHY_MODE_H
#define WITCHY_MODE_H

#include <FastLED.h>

// Main mode functions
void initWitchyMode(CRGBSet &L);
void updateWitchyMode(CRGBSet &L);

// Constants specific to witchy mode
namespace WitchyConstants
{
  // Timing and intervals
  constexpr uint16_t MAGIC_INTERVAL = 2;
  constexpr uint8_t FADE_RATE = 60;

  // Blotch configuration
  constexpr uint8_t MAX_BLOTCHES = 5; // Increased for more activity
  constexpr uint8_t BLOTCH_RADIUS = 5;
  constexpr uint8_t MAX_BLOTCH_LIFE = 80;
  constexpr uint8_t NEW_BLOTCH_CHANCE = 25; // Increased for more activity

  // Color intensities
  constexpr float DARK_PURPLE_INTENSITY = 0.4;
  constexpr float LIGHT_PURPLE_INTENSITY = 0.2; // Brighter for light purple
  constexpr float GREEN_INTENSITY = 0.4;

  // Magic surge configuration
  constexpr uint8_t SURGE_CHANCE = 10;
  constexpr uint8_t SURGE_DARK_PURPLE_MIN = 40;
  constexpr uint8_t SURGE_DARK_PURPLE_MAX = 150;
  constexpr uint8_t SURGE_LIGHT_PURPLE_MIN = 100; // Brighter minimum for light purple
  constexpr uint8_t SURGE_LIGHT_PURPLE_MAX = 200; // Brighter maximum for light purple

  // Dark sections
  constexpr uint8_t DARK_SECTION_CHANCE = 5;
}

#endif // WITCHY_MODE_H