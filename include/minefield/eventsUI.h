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
using BoardWithBool = std::pair<std::reference_wrapper<const Board>, bool>;
using PlayersWithBoard = std::pair<std::reference_wrapper<const std::vector<Player>>, std::reference_wrapper<const Board>>;

using UiEventArgs = std::variant<std::monostate,
    std::reference_wrapper<Board const>,
    const std::string,
    bool,
    BoardWithBool,
    PlayersWithBoard>;
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