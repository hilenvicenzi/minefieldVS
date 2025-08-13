#include "minefield/botLogic.h"
#include <random>

namespace MineBot
{
unsigned int makeRandomDistribution(unsigned int measurement)
{
    static std::random_device random;
    static std::mt19937 gen(random());
    std::uniform_int_distribution<unsigned int> dist(0, measurement - 1);
    unsigned int pos = dist(gen);
    return pos;
}

Coord makeValidRandomCoord(unsigned int height, unsigned int width)
{
    Coord c;
    c.posX = makeRandomDistribution(height);
    c.posY = makeRandomDistribution(width);
    return c;
}

Coord getValidBotCoord(Board &board)
{
    Coord cBot = makeValidRandomCoord(board.height, board.width);
    while (board.grid[cBot.posX][cBot.posY] == CellState::Disabled)
    {
        cBot = makeValidRandomCoord(board.height, board.width);
    }
    return cBot;
}
} // namespace minebot