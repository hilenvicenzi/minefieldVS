#include <gtest/gtest.h>
#include <minefield/board.h>
#include "minefield/botLogic.h"
#include "minefield/gameContext.h"
#include "minefield/coord.h"
namespace BoardTesting
{
    TEST(BoardTests, TestInitialBoardSize)
    {
        Board board;
        board.width = 10;
        board.height = 8;

        EXPECT_EQ(board.width, 10u);
        EXPECT_EQ(board.height, 8u);
    }

    TEST(BotCoordTests, NeverReturnsDisabledCell)
    {
        Board board;
        board.height = 3;
        board.width = 3;

        board.grid = {{CellState::Empty, CellState::Disabled, CellState::Disabled},
            {CellState::Disabled, CellState::Empty, CellState::Disabled},
            {CellState::Disabled, CellState::Disabled, CellState::Empty}};

        for (int i = 0; i < 20; ++i)
        {
            Coord c = MineBot::getValidBotCoord(board);
            EXPECT_NE(board.grid[c.posX][c.posY], CellState::Disabled);
        }
    }
} // namespace BoardTesting