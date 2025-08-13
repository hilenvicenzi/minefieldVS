#include "minefield/gameContext.h"
#include "minefield/botLogic.h"

namespace MineGameContext
{
void cleanPlayerMines(GameContext &ctx)
{
    for (Player &player : ctx.players)
    {
        player.playerMines.clear();
    }
}

void addMines(GameContext &ctx)
{
    for (Player &player : ctx.players)
    {
        MineRender::showPlayerData(player);
        player.playerMines.resize(player.numberOfmines);
        for (unsigned int j = 0; j < player.numberOfmines; j++)
        {
            Coord &mine = player.playerMines[j];
            if (player.isBot)
            {
                mine = MineBot::getValidBotCoord(ctx.table);
                player.playerMines[j] = mine;
#ifdef DEBUG
                std::cout << "BotMine #" << (j + 1) << " will be at [" << mine.posX << ", " << mine.posY << "]" << std::endl;
#endif
            }
            else
            {
                mine = MineCoord::askValidCoordAndEmpty(ctx.table);
                std::cout << "Mine #" << j + 1 << " will be at [" << mine.posX << ", " << mine.posY << "]\n";
                player.playerMines[j] = mine;
            }
            MineBoard::makeCellUsed(ctx.table, mine);
        }
        MineRender::clsAndShowBoard(ctx.table, player.isBot);
    }
}

unsigned int amountOfCurrentGuesses(const GameContext &ctx)
{
    if (ctx.players.empty())
    {
        return 0;
    }
    unsigned int minGuesses = ctx.players[0].playerMines.size();
    for (int i = 1; i < ctx.players.size(); i++)
    {
        unsigned int size = ctx.players[i].playerMines.size();
        minGuesses = std::min(minGuesses, size);
    }
    return minGuesses;

}

void addGuesses(GameContext &ctx)
{
    unsigned int guessesCount = MineGameContext::amountOfCurrentGuesses(ctx);
    for (Player &player : ctx.players)
    {
        std::cout << "Player " << player.name << " can enter " << guessesCount << " guesses\n";
        player.playerGuesses.resize(guessesCount);
        for (unsigned int j = 0; j < guessesCount; j++)
        {
            Coord &mine = player.playerGuesses[j];
            if (player.isBot)
            {
                mine = MineBot::getValidBotCoord(ctx.table);
                player.playerGuesses[j] = mine;
#ifdef DEBUG
                std::cout << "BotGuess #" << (j + 1) << " will be at [" << mine.posX << ", " << mine.posY << "]\n";
#endif
            }
            else
            {
                std::cout << "Guess #" << (j + 1) << '\n';
                mine = MineCoord::askValidCoordAndEmpty(ctx.table);
                std::cout << "Guess #" << (j + 1) << " will be at [" << mine.posX << ", " << mine.posY << "]\n";
                player.playerGuesses[j] = mine;
            }
            MineBoard::makeCellUsed(ctx.table, mine);
        }
        MineRender::clsAndShowBoard(ctx.table, player.isBot);
    }
}

void processGuesses(GameContext &ctx)
{
    for (Player &attacker : ctx.players)
    {
        for (Player &defender : ctx.players)
        {
            if (&attacker == &defender)
            {
                continue;
            }
            for (const Coord &mine : attacker.playerGuesses)
            {
                // player found another player mine
                if (MineCoord::containsCoordinate(defender.playerMines, mine))
                {
                    defender.numberOfmines--;
                }
                // player found their own mine
                if (MineCoord::containsCoordinate(attacker.playerMines, mine))
                {
                    attacker.numberOfmines--;
                }
                MineBoard::makeCellUsed(ctx.table, mine);
            }
        }
    }
}

void resetMines(GameContext &ctx)
{
    for (Player &player : ctx.players)
    {
        for (const Coord &mine : player.playerMines)
        {
            // changes cell state from used to disabled
            if (ctx.table.grid[mine.posX][mine.posY] == CellState::Used)
            {
                ctx.table.grid[mine.posX][mine.posY] = CellState::Disabled;
                --ctx.table.cellCount;
            }
        }
        player.playerMines.clear();
    }
}
} // namespace MineGameContext