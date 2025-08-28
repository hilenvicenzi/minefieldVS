#pragma once
#include "minefield/board.h"

struct Board; 
struct Coord
{
    unsigned int posX = 0;
    unsigned int posY = 0;
};

namespace MineCoord
{
    Coord askValidCoord(Board const& board, std::istream& in, std::ostream& out);
    bool containsCoordinate(const std::vector<Coord> &coordinates, Coord coord);
    Coord askValidCoordAndEmpty(Board const& board, std::ostream& out);
} // namespace MineCoord