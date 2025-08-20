#include <gtest/gtest.h>
#include "minefield/gameContext.h"
namespace AddingMinesTests
{
    TEST(GameLogicTests, AddMinesInPosition)
    {
        GameContext ctx;
        ctx.table.width = 5;
        ctx.table.height = 5;
        ctx.table.grid = std::vector<std::vector<CellState>>(5, std::vector<CellState>(5, CellState::Empty));

        // captured events
        std::vector<Event> capturedEvents;
        ctx.event = [&](Event const& e) { capturedEvents.push_back(e); };

        // captured events UI
        std::vector<UiEvent> capturedUiEvents;
        ctx.uiEvent = [&](UiEvent const& e) { capturedUiEvents.push_back(e); };


        Player bot;
        bot.isBot = true;
        bot.numberOfmines = 2;

        Player human;
        human.isBot = false;
        human.numberOfmines = 2;

        ctx.players = {bot, human};

        auto fakeBotCoord = [](GameContext&, Player&, unsigned) { return Coord{1, 1}; };
        auto fakeHumanCoord = [](GameContext&, Player&, unsigned) { return Coord{2, 2}; };

        MineGameContext::addMines(ctx, fakeBotCoord, fakeHumanCoord);


        for (auto const& mine : ctx.players[0].playerMines)
        {
            EXPECT_EQ(mine.posX, 1);
            EXPECT_EQ(mine.posY, 1);
        }
        for (auto const& mine : ctx.players[1].playerMines)
        {
            EXPECT_EQ(mine.posX, 2);
            EXPECT_EQ(mine.posY, 2);
        }

        EXPECT_EQ(ctx.table.grid[1][1], CellState::Used);
        EXPECT_EQ(ctx.table.grid[2][2], CellState::Used);
    }
} // namespace AddingMinesTests