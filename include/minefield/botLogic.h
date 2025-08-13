#pragma once
#include "coord.h"

namespace MineBot
{
unsigned int makeRandomDistribution(unsigned int measurement);
Coord makeValidRandomCoord(unsigned int height, unsigned int width);
Coord getValidBotCoord(Board &board);
} // namespace MineBot