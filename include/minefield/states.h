#pragma once

struct GameContext;
struct State; 

typedef State NextState;
typedef NextState (*StateUpdateFn)(GameContext &);


struct State
{
    StateUpdateFn updateFunction;
};


namespace MineGameStates
{
NextState stateMainMenuUpdate(GameContext &ctx);
NextState stateConfigUpdate(GameContext &ctx);
NextState statePlaceMines(GameContext &ctx);
NextState stateAddGuesses(GameContext &ctx);
NextState stateProcessGuesses(GameContext &ctx);
NextState stateCheckVictory(GameContext &ctx);
} // namespace MineGameStates