#include <iostream>
#include <iomanip>
#include "minefield/board.h"

namespace MineBoard
{
void showBoard(const Board &board)
{
    MineRender::showGameTittle(board);
    std::cout << "   ";
    for (unsigned int j = 0; j < board.width; ++j)
    {
        std::cout << std::setw(4) << j;
    }
    std::cout << '\n';
    std::cout << "   ";
    for (unsigned int j = 0; j < board.width; ++j)
    {
        std::cout << "----";
    }
    std::cout << "-\n";

    for (int i = 0; i < board.grid.size(); ++i)
    {
        std::cout << std::setw(2) << i << '|';

        for (const auto &cell : board.grid[i])
        {
            std::string symbol = (cell == CellState::Disabled) ? MineRender::applyColor(Color::Red, "   X") : " O";
            std::cout << std::setw(4) << symbol;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void makeCellUsed(Board &board, const Coord &cord)
{
    if (cord.posX < board.width && cord.posY < board.height && board.grid[cord.posX][cord.posY] == CellState::Empty)
    {
        board.grid[cord.posX][cord.posY] = CellState::Used;
    }
}

unsigned int askValidDimensions(AxisOptions axisOption)
{
    unsigned int value = 0;
    while (value < kMinDim || value > kMaxDim)
    {
        if (axisOption == AxisOptions::AxisOptionWidth)
        {
            std::cout << "Width: ";
        }
        else
        {
            std::cout << "Height: ";
        }
        std::cin >> value;
    }
    return value;
}
} // namespace MineBoard

