#ifndef WITCHY_MODE_H
#define WITCHY_MODE_H

#include <FastLED.h>

// Main mode functions
void initWitchyMode(CRGBSet &L);
void updateWitchyMode(CRGBSet &L);

// Constants specific to witchy mode
namespace WitchyConstants
{
  // Base colors (darker)
  constexpr uint8_t BASE_PURPLE_R = 2; // Reduced from 4
  constexpr uint8_t BASE_PURPLE_G = 0;
  constexpr uint8_t BASE_PURPLE_B = 6; // Reduced from 8

  // Timing and intervals
  constexpr uint16_t MAGIC_INTERVAL = 150;
  constexpr uint8_t FADE_RATE = 30; // Increased from 20 for faster fade

  // Blotch configuration
  constexpr uint8_t MAX_BLOTCHES = 5;
  constexpr uint8_t BLOTCH_RADIUS = 10;
  constexpr uint8_t MAX_BLOTCH_LIFE = 100;
  constexpr uint8_t NEW_BLOTCH_CHANCE = 15; // Reduced from 20

  // Magic surge configuration
  constexpr uint8_t SURGE_CHANCE = 3;       // Reduced from 5
  constexpr uint8_t SURGE_PURPLE_MIN = 64;  // Reduced from 128
  constexpr uint8_t SURGE_PURPLE_MAX = 180; // Reduced from 255

  // Color mixing
  constexpr float PURPLE_INTENSITY = 0.3; // Reduced from 0.5
  constexpr float GREEN_INTENSITY = 0.25; // Reduced from 0.4
}

#endif // WITCHY_MODE_H