#include "minefield/coord.h"
#include <iostream>

namespace MineCoord
{
Coord askValidCoord(const Board &board)
{
    unsigned int row = board.width + 1;
    unsigned int column = board.height + 1;
    while (row < 0 || row >= board.width)
    {
        std::cout << "Row: ";
        std::cin >> row;
    }
    while (column < 0 || column >= board.height)
    {
        std::cout << "Column: ";
        std::cin >> column;
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

Coord askValidCoordAndEmpty(const Board &board)
{
    Coord validCoord = askValidCoord(board);
    while (board.grid[validCoord.posX][validCoord.posY] == CellState::Disabled)
    {
        std::cout << "Cell already disabled. Pick another.\n";
        validCoord = askValidCoord(board);
    }
    return validCoord;
}
} // namespace MineCoord