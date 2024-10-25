#include "witchy_mode.h"
#include "../global_defs.h"
#include "../led_config.h"
#include "../utility_functions.h"

using namespace WitchyConstants;

void initWitchyMode(CRGBSet &L)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    L[i] = CRGB::Black;
  }
}

// Helper to get neighboring sections
void getNeighboringSections(uint8_t row, uint8_t section, uint8_t (&neighbors)[6][2], uint8_t &numNeighbors)
{
  numNeighbors = 0;

  // Add previous and next section in same row
  if (section > 0)
  {
    neighbors[numNeighbors][0] = row;
    neighbors[numNeighbors][1] = section - 1;
    numNeighbors++;
  }
  if (section < SECTIONS_PER_ROW - 1)
  {
    neighbors[numNeighbors][0] = row;
    neighbors[numNeighbors][1] = section + 1;
    numNeighbors++;
  }

  // Add sections from row above
  if (row > 0)
  {
    neighbors[numNeighbors][0] = row - 1;
    neighbors[numNeighbors][1] = section;
    numNeighbors++;
    if (section > 0)
    {
      neighbors[numNeighbors][0] = row - 1;
      neighbors[numNeighbors][1] = section - 1;
      numNeighbors++;
    }
  }

  // Add sections from row below
  if (row < NUM_ROWS - 1)
  {
    neighbors[numNeighbors][0] = row + 1;
    neighbors[numNeighbors][1] = section;
    numNeighbors++;
    if (section < SECTIONS_PER_ROW - 1)
    {
      neighbors[numNeighbors][0] = row + 1;
      neighbors[numNeighbors][1] = section + 1;
      numNeighbors++;
    }
  }
}

void updateWitchyMode(CRGBSet &L)
{
  static struct BlotchInfo
  {
    uint8_t row;
    uint8_t section;
    uint8_t life;
    uint8_t type; // 0 = dark purple, 1 = light purple, 2 = green
    bool active;
  } blotches[MAX_BLOTCHES];

  EVERY_N_MILLISECONDS(MAGIC_INTERVAL)
  {
    fadeToBlackBy(L, NUM_LEDS, FADE_RATE);

    // Update existing blotches
    for (int i = 0; i < MAX_BLOTCHES; i++)
    {
      if (blotches[i].active && blotches[i].life > 0)
      {
        float intensity = sin((float)blotches[i].life / MAX_BLOTCH_LIFE * PI) * 0.8;

        // Get neighboring sections
        uint8_t neighbors[6][2];
        uint8_t numNeighbors;
        getNeighboringSections(blotches[i].row, blotches[i].section, neighbors, numNeighbors);

        // Light up main section
        uint16_t startIndex = getLedIndexForSection(blotches[i].row, blotches[i].section);
        uint8_t sectionLength = SECTION_LENGTHS[blotches[i].row][blotches[i].section];

        // Apply effect to main section
        for (int j = 0; j < sectionLength; j++)
        {
          if (startIndex + j < NUM_LEDS)
          {
            CRGB newColor;
            uint8_t brightness = intensity * 255;

            switch (blotches[i].type)
            {
            case 0: // Dark purple
            {
              uint8_t purpleRed = qsub8(brightness * DARK_PURPLE_INTENSITY, 50);
              newColor = CRGB(purpleRed, 0, purpleRed * 1.5);
            }
            break;
            case 1: // Light purple
            {
              uint8_t purpleRed = qsub8(brightness * LIGHT_PURPLE_INTENSITY, 20);
              newColor = CRGB(purpleRed, 0, purpleRed * 1.2);
            }
            break;
            case 2: // Green
              newColor = CRGB(0, qsub8(brightness * GREEN_INTENSITY, 100), 0);
              break;
            }

            if (newColor.getAverageLight() > L[startIndex + j].getAverageLight())
            {
              L[startIndex + j] = newColor;
            }
          }
        }

        // Apply dimmer effect to neighboring sections
        for (int n = 0; n < numNeighbors; n++)
        {
          uint16_t neighStart = getLedIndexForSection(neighbors[n][0], neighbors[n][1]);
          uint8_t neighLength = SECTION_LENGTHS[neighbors[n][0]][neighbors[n][1]];

          for (int j = 0; j < neighLength; j++)
          {
            if (neighStart + j < NUM_LEDS)
            {
              CRGB newColor;
              uint8_t brightness = intensity * 127; // Half brightness for neighbors

              switch (blotches[i].type)
              {
              case 0: // Dark purple
              {
                uint8_t purpleRed = qsub8(brightness * DARK_PURPLE_INTENSITY, 50);
                newColor = CRGB(purpleRed, 0, purpleRed * 1.5);
              }
              break;
              case 1: // Light purple
              {
                uint8_t purpleRed = qsub8(brightness * LIGHT_PURPLE_INTENSITY, 20);
                newColor = CRGB(purpleRed, 0, purpleRed * 1.2);
              }
              break;
              case 2: // Green
                newColor = CRGB(0, qsub8(brightness * GREEN_INTENSITY, 100), 0);
                break;
              }

              if (newColor.getAverageLight() > L[neighStart + j].getAverageLight())
              {
                L[neighStart + j] = newColor;
              }
            }
          }
        }

        blotches[i].life--;
        if (blotches[i].life == 0)
        {
          blotches[i].active = false;
        }
      }
      else if (!blotches[i].active && random8() < NEW_BLOTCH_CHANCE)
      {
        // Start new blotch
        blotches[i].row = random8(NUM_ROWS);
        blotches[i].section = random8(SECTIONS_PER_ROW);
        blotches[i].life = MAX_BLOTCH_LIFE;
        blotches[i].active = true;

        uint8_t rnd = random8();
        if (rnd < 128)
        { // 50% chance for dark purple
          blotches[i].type = 0;
        }
        else if (rnd < 192)
        { // 25% chance for light purple
          blotches[i].type = 1;
        }
        else
        { // 25% chance for green
          blotches[i].type = 2;
        }
      }
    }

    // Occasional magical surge along connected sections
    if (random8() < SURGE_CHANCE)
    {
      uint8_t startRow = random8(NUM_ROWS);
      uint8_t startSection = random8(SECTIONS_PER_ROW);
      bool lightPurple = (random8() < 128);

      // Surge through main section and neighbors
      uint8_t neighbors[6][2];
      uint8_t numNeighbors;
      getNeighboringSections(startRow, startSection, neighbors, numNeighbors);

      // Main section
      uint16_t startIndex = getLedIndexForSection(startRow, startSection);
      uint8_t sectionLength = SECTION_LENGTHS[startRow][startSection];

      for (int j = 0; j < sectionLength; j++)
      {
        if (startIndex + j < NUM_LEDS)
        {
          uint8_t surgeRed;
          if (lightPurple)
          {
            surgeRed = qsub8(random8(SURGE_LIGHT_PURPLE_MIN, SURGE_LIGHT_PURPLE_MAX), 20);
            L[startIndex + j] = CRGB(surgeRed, 0, surgeRed * 1.2);
          }
          else
          {
            surgeRed = qsub8(random8(SURGE_DARK_PURPLE_MIN, SURGE_DARK_PURPLE_MAX), 100);
            L[startIndex + j] = CRGB(surgeRed, 0, surgeRed * 1.5);
          }
        }
      }

      // Neighboring sections (dimmer)
      for (int n = 0; n < numNeighbors; n++)
      {
        if (random8() < 180)
        { // 70% chance to include each neighbor
          uint16_t neighStart = getLedIndexForSection(neighbors[n][0], neighbors[n][1]);
          uint8_t neighLength = SECTION_LENGTHS[neighbors[n][0]][neighbors[n][1]];

          for (int j = 0; j < neighLength; j++)
          {
            if (neighStart + j < NUM_LEDS)
            {
              uint8_t surgeRed;
              if (lightPurple)
              {
                surgeRed = qsub8(random8(SURGE_LIGHT_PURPLE_MIN / 2, SURGE_LIGHT_PURPLE_MAX / 2), 20);
                L[neighStart + j] = CRGB(surgeRed, 0, surgeRed * 1.2);
              }
              else
              {
                surgeRed = qsub8(random8(SURGE_DARK_PURPLE_MIN / 2, SURGE_DARK_PURPLE_MAX / 2), 100);
                L[neighStart + j] = CRGB(surgeRed, 0, surgeRed * 1.5);
              }
            }
          }
        }
      }
    }
  }
}