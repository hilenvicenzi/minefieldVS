#pragma once
#include <functional>
#include <iostream>
#include <variant>
#include "board.h"

enum class UiAction
{
    ClearConsoleBuffer,
    ShowMenu,
    ClearScreenAndShowBoard,
    ShowConfigurationTitle,
    ShowTableMeasurement,
    ShowMinesLimits,
    ShowAmountOfHumanPlayers,
    ShowAmountOfBotPlayers,
    ShowBoard,
    ShowMessage,
    ShowWinner,
    EnterToContinue,
    ShowPlayersUsernames,
    MoreMinesThanCells
};

using UiEventArgs = std::variant<std::monostate,
    const Board,
    const std::string,
    bool,
    std::pair<const Board, bool>,
    std::pair<const std::vector<Player>, const Board>
>;
struct UiEvent
{
    UiAction action;
    UiEventArgs args;
};
using UiEventHandler = std::function<void(const UiEvent&)>;

namespace MineUiEvents
{
    UiEventHandler configUiEventHandler();
}