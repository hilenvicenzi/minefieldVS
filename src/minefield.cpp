#include "minefield/gameContext.h"
#include "minefield/states.h"

int main()
{
    GameContext ctx;
    ctx.currentState = State { &MineGameStates::stateMainMenuUpdate };
    while (ctx.currentState.updateFunction != nullptr)
    {
        ctx.currentState = (*ctx.currentState.updateFunction)(ctx);
    }
    return 0;
}