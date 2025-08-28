#include "minefield/coord.h"
#include <iostream>
#include <functional>

namespace MineCoord
{

Coord askValidCoord(Board const& board, std::istream& in, std::ostream& out)
    {
    unsigned int row = board.width + 1;
    unsigned int column = board.height + 1;
    while (row < 0 || row >= board.width || column < 0 || column >= board.width)
    {
        out << "Coordinate: ";
        in >> row >> column;
    }

    return {row, column};
}

bool containsCoordinate(const std::vector<Coord> &coordinates, Coord coord)
{
    for (auto const& c : coordinates)
    {
        if (c.posX == coord.posX && c.posY == coord.posY)
        {
            return true;
        }
    }
    return false;
}

Coord askValidCoordAndEmpty(Board const& board, std::ostream& out)
{
    Coord validCoord = askValidCoord(board, std::cin, std::cout);
    while (board.grid[validCoord.posX][validCoord.posY] == CellState::Disabled)
    {
        out << "Cell already disabled. Pick another.\n";
        validCoord = askValidCoord(board, std::cin, std::cout);
    }
    return validCoord;
}

} // namespace MineCoord