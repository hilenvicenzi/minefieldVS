#pragma once
#include "board.h"

struct Board; 
struct Coord
{
    unsigned int posX = 0;
    unsigned int posY = 0;
};

namespace MineCoord
{
Coord askValidCoord(const Board &board);
bool containsCoordinate(const std::vector<Coord> &coordinates, Coord coord);
Coord askValidCoordAndEmpty(const Board &board);
} // namespace MineCoord