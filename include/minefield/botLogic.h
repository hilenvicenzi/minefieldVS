#pragma once
#include "minefield/coord.h"

namespace MineBot
{
unsigned int makeRandomDistribution(unsigned int measurement);
Coord makeValidRandomCoord(unsigned int height, unsigned int width);
Coord getValidBotCoord(const Board &board);
} // namespace MineBot