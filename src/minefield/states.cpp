#include "minefield/states.h"
#include "minefield/gameContext.h"
#include "minefield/inputs.h"
#include "minefield/player.h"
#include "minefield/eventsUI.h"

namespace MineGameStates
{
    std::istream& getInputStream()
    {
        return std::cin; 
    }

    NextState stateMainMenuUpdate(GameContext& ctx)
    {
    ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
    ctx.uiEvent(UiEvent{UiAction::ShowMenu, std::monostate{}});
    int opt = 0;
    static constexpr int kOptionPlay = 1;
    auto& in = getInputStream();
    in >> opt;
    if (opt == kOptionPlay)
    {
        return {&stateConfigUpdate};
    }
    return {nullptr};
}

unsigned int askValidNumberOfMines(std::istream& in)
{
    unsigned int mines = 0;
    while (mines < kMinMine || mines > kMaxMine)
    {
        in >> mines;
    }
    return mines;
}

State stateConfigUpdate(GameContext& ctx)
{
    ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
    ctx.players.clear();
    ctx.uiEvent(UiEvent{UiAction::ShowConfigurationTitle, std::monostate{}});

    ctx.uiEvent(UiEvent{UiAction::ShowTableMeasurement, std::monostate{}});
    unsigned int validWidth = MineInputs::askValidDimensions(AxisOptions::AxisOptionWidth, std::cin, std::cout);
    unsigned int validHeight = MineInputs::askValidDimensions(AxisOptions::AxisOptionHeight, std::cin, std::cout);
    ctx.table.cellCount = validHeight * validWidth;

    ctx.uiEvent(UiEvent{UiAction::ShowMinesLimits, std::monostate{}});
    unsigned int validMines = askValidNumberOfMines(std::cin);

    int amountOfRealPlayers = 0;
    ctx.uiEvent(UiEvent{UiAction::ShowAmountOfHumanPlayers, std::monostate{}});
    auto& in = getInputStream();
    in >> amountOfRealPlayers;

    int amountOfBotPlayers = 0;
    ctx.uiEvent(UiEvent{UiAction::ShowAmountOfBotPlayers, std::monostate{}});
    in >> amountOfBotPlayers;

    int totalAmountOfPlayers = amountOfRealPlayers + amountOfBotPlayers;

    ctx.uiEvent(UiEvent{UiAction::ShowPlayersUsernames, std::monostate{}});

    for (int i = 0; i < totalAmountOfPlayers; i++)
    {
        bool isBot = (i >= amountOfRealPlayers) ? true : false;
        std::string name = MineInputs::getPlayerNameFromUser(i, isBot, std::cin, std::cout);
        MinePlayer::setPlayersNames(ctx.players, name, i, validMines, isBot);
    }

    ctx.table.height = validHeight;
    ctx.table.width = validWidth;
    ctx.table.grid = std::vector<std::vector<CellState>>(validHeight, std::vector<CellState>(validWidth, CellState::Empty));
    static const bool kContinueForHuman = false;
    ctx.uiEvent(UiEvent{UiAction::EnterToContinue, kContinueForHuman});
    return {&statePlaceMines};
}

State statePlaceMines(GameContext &ctx)
{
    ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
    ctx.uiEvent(UiEvent{UiAction::ShowBoard, ctx.table});
    MineGameContext::cleanPlayerMines(ctx);
    MineGameContext::addMines(ctx);
    return {&stateAddGuesses};
}

State stateAddGuesses(GameContext &ctx)
{
    MineGameContext::addGuesses(ctx);
    return {&stateProcessGuesses};
}

State stateProcessGuesses(GameContext &ctx)
{
    MineGameContext::processGuesses(ctx);
    return {&stateCheckVictory};
}

State stateCheckVictory(GameContext &ctx)
{
    int playersWithMines = MinePlayer::getPlayersWithMines(ctx.players);
    if (playersWithMines == 0)
    {
        ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
        ctx.uiEvent(UiEvent{UiAction::ShowBoard, ctx.table});
        ctx.uiEvent(UiEvent{UiAction::ShowMessage, "It's a draw!\n"});
        ctx.uiEvent(UiEvent{UiAction::EnterToContinue, false});
        return {&stateMainMenuUpdate};
    }

    if (playersWithMines == 1)
    {
        for (const Player &player : ctx.players)
        {
            if (player.numberOfmines > 0)
            {
                ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
                ctx.uiEvent(UiEvent{UiAction::ShowBoard, ctx.table});
                ctx.uiEvent(UiEvent{UiAction::ShowWinner, player.name});
                ctx.uiEvent(UiEvent{UiAction::EnterToContinue, false});
            }
        }
        return {&stateMainMenuUpdate};
    }

    MineGameContext::resetMines(ctx);
    if (ctx.table.cellCount < MinePlayer::amountOfTotalMines(ctx.players))
    {
        ctx.uiEvent(UiEvent{UiAction::ClearConsoleBuffer, std::monostate{}});
        ctx.uiEvent(UiEvent{UiAction::ShowBoard, ctx.table});
        ctx.uiEvent(UiEvent{UiAction::MoreMinesThanCells, std::pair<std::vector<Player> const, Board const>{ctx.players, ctx.table}});
        ctx.uiEvent(UiEvent{UiAction::ShowWinner, MinePlayer::winnerPlayer(ctx.players).name});
        ctx.uiEvent(UiEvent{UiAction::EnterToContinue, false});
        return {&stateMainMenuUpdate};
    }
    MinePlayer::eraseLoser(ctx.players);
    return {&statePlaceMines};
}
} //namespace MineGameStates
