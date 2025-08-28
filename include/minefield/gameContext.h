#pragma once
#include "states.h"
#include "botLogic.h"
#include "board.h"
#include "player.h"
#include "render.h"
#include "Coord.h"
#include "eventsUI.h"

#include <vector>
#include <iostream>
#include <functional>
#include <variant>
#include <tuple>

struct State;
struct GameContext;
struct UiEvent;

// all the events that can happend in the game
enum class Action : std::uint8_t
{
    PlayerData,
    PlaceMine,
    GuessesFor,
    GuessMineAt,
    GuessNumber,
    GameOver,
    PlayerTurn,
    PlayerWin,
    MoreCellsThanMines,
};

using EventArgs = std::variant<
    std::monostate,
    Player,
    Board, 
    unsigned int, 
    bool, 
    std::string, 
    std::pair<Board, bool>,
    std::pair<unsigned int, Coord>,
    std::pair<std::string, unsigned int> 
>;

struct Event
{
    Action action;
    EventArgs args;
};

using EventHandler = std::function<void(const Event&)>;
struct GameContext
{
    State currentState;
    Board table;
    std::vector<Player> players;
    unsigned int guesses = 0;
    EventHandler event;
    UiEventHandler uiEvent;
};

namespace MineGameContext
{

void configEventHandler(GameContext &ctx);
void cleanPlayerMines(GameContext &ctx);

using GetCoordFn = std::function<Coord(GameContext&, Player&, unsigned int)>;

Coord chooseMineCoord(GameContext& ctx, Player& player, unsigned int j, GetCoordFn const& botCoordFn, GetCoordFn const& humanCoordFn);

void addMines(GameContext& ctx,
             GetCoordFn const& botCoordFn = [](GameContext& c, Player&, unsigned int) { return MineBot::getValidBotCoord(c.table); },
    GetCoordFn const& humanCoordFn = [](GameContext& c, Player&, unsigned int)
    { return MineCoord::askValidCoordAndEmpty(c.table, std::cout); });

using GetGuessFn = std::function<Coord(GameContext&, Player&, unsigned int)>;

Coord chooseGuessCoord(GameContext& ctx, Player& player, unsigned int j, GetCoordFn const& botGuessFn, GetGuessFn const& humanGuessFn);

void addGuesses(GameContext& ctx,
                GetCoordFn const& botGuessdFn = [](GameContext& c, Player&, unsigned int){ return MineBot::getValidBotCoord(c.table); },
    GetGuessFn const& humanGuessFn = [](GameContext& c, Player&, unsigned int)
    { return MineCoord::askValidCoordAndEmpty(c.table, std::cout); });

unsigned int amountOfCurrentGuesses(const GameContext &ctx);


void processGuesses(GameContext &ctx);
void resetMines(GameContext &ctx);
}