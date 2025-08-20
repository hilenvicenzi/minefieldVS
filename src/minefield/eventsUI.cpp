#include "minefield/render.h"
#include "minefield/eventsUI.h"

namespace MineUiEvents
{
    UiEventHandler configUiEventHandler() {
        return [](UiEvent const& e)
        {
            switch (e.action)
            {
            case UiAction::ClearConsoleBuffer:
            {
                MineRender::clearConsoleBuffer();
                break;
            }
            case UiAction::ClearScreenAndShowBoard:
            {
                if (std::holds_alternative<std::pair<const Board, bool>>(e.args))
                {
                    auto& data = std::get<std::pair<const Board, bool>>(e.args);
                    MineRender::clsAndShowBoard(data.first, data.second);
                }
                break;
            }
            case UiAction::ShowMenu:
            {
                MineRender::showMenu();
                break;
            }
            case UiAction::ShowConfigurationTitle:
            {
                MineRender::showConfigurationTitle();
                break;
            }
            case UiAction::ShowTableMeasurement:
            {
                MineRender::showTableMeasurement();
                break;
            }
            case UiAction::ShowMinesLimits:
            {
                MineRender::showMinesLimits();
                break;
            }
            case UiAction::ShowAmountOfHumanPlayers:
            {
                MineRender::showAmountOfHumanPlayers();
                break;
            }
            case UiAction::ShowAmountOfBotPlayers:
            {
                MineRender::showAmountOfBotPlayers();
                break;
            }
            case UiAction::ShowPlayersUsernames:
            {
                MineRender::showPlayersUsernamesTitle();
                break;
            }
            case UiAction::ShowBoard:
            {
                if (std::holds_alternative<const Board>(e.args))
                {
                    auto& dataBoard = std::get<const Board>(e.args);
                    MineRender::showBoard(dataBoard);
                }
                break;
            }
            case UiAction::ShowMessage:
            {
                if (std::holds_alternative<const std::string>(e.args))
                {
                    auto& dataMessage = std::get<const std::string>(e.args);
                    MineRender::showMessage(dataMessage);
                }
                break;
            }
            case UiAction::ShowWinner:
            {
                if (std::holds_alternative<const std::string>(e.args))
                {
                    auto& dataWinner = std::get<const std::string>(e.args);
                    MineRender::showWinner(dataWinner);
                }
                break;
            }
            case UiAction::EnterToContinue:
            {
                if (std::holds_alternative<bool>(e.args))
                {
                    bool isBot = std::get<bool>(e.args);
                    MineRender::enterToContinue(isBot);
                }
                break;
            }
            case UiAction::MoreMinesThanCells:
            {
                if (std::holds_alternative<std::pair<const std::vector<Player>, Board const>>(e.args))
                {
                    auto& moreMinesData = std::get<std::pair<std::vector<Player> const, Board const>>(e.args);
                    MineRender::showMoreMinesThanCells(moreMinesData.first, moreMinesData.second);
                }
                break;
            }
            default:
                break;
            };
        };
    }
} // namespace MineUiEvents