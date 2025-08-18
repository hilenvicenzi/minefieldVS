#include <iostream>
#include "minefield/board.h"

namespace MineBoard
{

void makeCellUsed(Board &board, const Coord &cord)
{
    if (cord.posX < board.width && cord.posY < board.height && board.grid[cord.posX][cord.posY] == CellState::Empty)
    {
        board.grid[cord.posX][cord.posY] = CellState::Used;
    }
}

} // namespace MineBoard

