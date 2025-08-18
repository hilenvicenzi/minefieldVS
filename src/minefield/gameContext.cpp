#include "minefield/gameContext.h"
#include "minefield/botLogic.h"

namespace MineGameContext
{
    // switch based on actions
    void configEventHandler(GameContext &ctx)
    {
        ctx.event = [](const Event &e)
        {
            switch (e.action)
            {
            case Action::PlayerData:
            {
                //auto &data = std::get<OnlyPlayer>(e.args);
                auto& dataPlayer = std::get<Player>(e.args);
                MineRender::showPlayerData(dataPlayer);
                break;
            }
            case Action::PlaceMine:
            {
                auto& dataPlaceMine = std::get<std::pair<unsigned int, Coord>>(e.args);
                MineRender::showMineAtPosition(dataPlaceMine.first, dataPlaceMine.second);
                break;
            }
            case Action::GuessNumber:
            {
                auto& dataGuessNumber = std::get<unsigned int>(e.args);
                MineRender::showGuessNumber(dataGuessNumber);
                break;
            }
            case Action::GuessesFor:
            {
                auto const &dataGuessesFor = std::get < std::pair<std::string, unsigned int >> (e.args);
                MineRender::showAmountOfGuessForAPLayer(dataGuessesFor.first, dataGuessesFor.second);
                break;
            }
            default:
                break;
            }
        };
    }
    //auto &data = std::get<OnlyValue<Player>>(e.args);
    void cleanPlayerMines(GameContext &ctx)
    {
        for (Player &player : ctx.players)
        {
            player.playerMines.clear();
        }
    }

Coord chooseMineCoord(GameContext& ctx, Player& player, unsigned int j, GetCoordFn const& botCoordFn, GetCoordFn const& humanCoordFn)
    {
        Coord mine;
        if (player.isBot)
        {
            mine = botCoordFn(ctx, player, j);
            player.playerMines[j] = mine;
        }
        else
        {
            mine = humanCoordFn(ctx, player, j);
            ctx.event(Event{Action::PlaceMine, std::pair<unsigned int, Coord>{j, mine}});
            player.playerMines[j] = mine;
        }
        return mine;
    }

    void addMines(GameContext& ctx, GetCoordFn const& botCoordFn, GetCoordFn const& humanCoordFn)
    {
        for (Player& player : ctx.players)
        {
            ctx.event(Event{Action::PlayerData, player});
            player.playerMines.resize(player.numberOfmines);

            for (unsigned int j = 0; j < player.numberOfmines; j++)
            {
                Coord mine = chooseMineCoord(ctx, player, j, botCoordFn, humanCoordFn);
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

    Coord chooseGuessCoord(GameContext& ctx, Player& player, unsigned int j, GetCoordFn const& botGuessFn, GetGuessFn const& humanGuessFn)
    {
        Coord& mine = player.playerGuesses[j];
        if (player.isBot)
        {
            mine = botGuessFn(ctx, player, j);
            player.playerGuesses[j] = mine;
        }
        else
        {
            ctx.event(Event{Action::GuessNumber, j});
            mine = humanGuessFn(ctx, player, j);
            ctx.event(Event{Action::GuessMineAt, std::pair<unsigned int,Coord>{j, mine}});
            player.playerGuesses[j] = mine;
        }
        return mine;
    }

    void addGuesses(GameContext& ctx, GetCoordFn const& botGuessFn, GetGuessFn const& humanGuessFn)
    {
        unsigned int guessesCount = MineGameContext::amountOfCurrentGuesses(ctx);
        for (Player &player : ctx.players)
        {
            ctx.event(Event{Action::GuessesFor, std::pair<std::string, unsigned int>{player.name, guessesCount}});
            player.playerGuesses.resize(guessesCount);
            for (unsigned int j = 0; j < guessesCount; j++)
            {
                Coord mine = chooseGuessCoord(ctx, player, j, botGuessFn, humanGuessFn); 
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
                    if (MineCoord::containsCoordinate(defender.playerMines, mine) && defender.numberOfmines > 0)
                    {
                        defender.numberOfmines--;
                    }
                    // player found their own mine
                    if (MineCoord::containsCoordinate(attacker.playerMines, mine) && attacker.numberOfmines > 0)
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