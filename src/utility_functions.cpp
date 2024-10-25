#include "utility_functions.h"
#include "global_defs.h"

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