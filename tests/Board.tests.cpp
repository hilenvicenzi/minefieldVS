#include <gtest/gtest.h>
#include <minefield/Board.h>

TEST(BoardTests, TestInitialBoardSize)
{
    Board board;
    board.width = 10;
    board.height = 8;

    EXPECT_EQ(board.width, 10u);
    EXPECT_EQ(board.height, 8u);
}