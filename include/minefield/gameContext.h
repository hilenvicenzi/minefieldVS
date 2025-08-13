#pragma once
#include "states.h"
#include "board.h"
#include "player.h"
#include <vector>
#include <iostream>

struct State;
struct GameContext
{
    State currentState;
    Board table;
    std::vector<Player> players;
    unsigned int guesses = 0;
};

namespace MineGameContext
{
void cleanPlayerMines(GameContext &ctx);
void addMines(GameContext &ctx);
unsigned int amountOfCurrentGuesses(const GameContext &ctx);
void addGuesses(GameContext &ctx);
void processGuesses(GameContext &ctx);
void resetMines(GameContext &ctx);
}