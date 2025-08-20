#include "minefield/gameContext.h"
#include "minefield/states.h"
//eventHandler.placeMine(Action::PlaceMine, ...);
int main()
{
    GameContext ctx;
    MineGameContext::configEventHandler(ctx);
    ctx.uiEvent = MineUiEvents::configUiEventHandler();
    ctx.currentState = State { &MineGameStates::stateMainMenuUpdate };
    while (ctx.currentState.updateFunction != nullptr)
    {
        ctx.currentState = (*ctx.currentState.updateFunction)(ctx);
    }
    return 0;
}