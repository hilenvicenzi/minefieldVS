#include "minefield/states.h"
#include "minefield/gameContext.h"
#include "minefield/inputs.h"
#include "minefield/player.h"

namespace MineGameStates
{
NextState stateMainMenuUpdate(GameContext &ctx)
{
    MineRender::clearConsoleBuffer();
    MineRender::showMenu();
    int opt = 0;
    static constexpr int kOptionPlay = 1;
    std::cin >> opt;
    if (opt == kOptionPlay)
    {
        return {&stateConfigUpdate};
    }
    return {nullptr};
}

unsigned int askValidNumberOfMines()
{
    unsigned int mines = 0;
    while (mines < kMinMine || mines > kMaxMine)
    {
        std::cin >> mines;
    }
    return mines;
}

State stateConfigUpdate(GameContext &ctx)
{
    MineRender::clearConsoleBuffer();
    ctx.players.clear();
    MineRender::showConfigurationTitle();

    MineRender::showTableMeasurement();
    unsigned int validWidth = MineInputs::askValidDimensions(AxisOptions::AxisOptionWidth);
    unsigned int validHeight = MineInputs::askValidDimensions(AxisOptions::AxisOptionHeight);
    ctx.table.cellCount = validHeight * validWidth;

    MineRender::showMinesLimits();
    unsigned int validMines = askValidNumberOfMines();

    int amountOfRealPlayers = 0;
    MineRender::showAmountOfHumanPlayers();
    std::cin >> amountOfRealPlayers;

    int amountOfBotPlayers = 0;
    MineRender::showAmountOfBotPlayers();
    std::cin >> amountOfBotPlayers;

    int totalAmountOfPlayers = amountOfRealPlayers + amountOfBotPlayers;

    std::string playersUsernamesTittle = MineRender::applyColor(Color::Magenta, "\nPlayers usernames\n");
    std::cout << playersUsernamesTittle;

    for (int i = 0; i < totalAmountOfPlayers; i++)
    {
        bool isBot = (i >= amountOfRealPlayers) ? true : false;
        std::string name = MineInputs::getPlayerNameFromUser(i, isBot);
        MinePlayer::setPlayersNames(ctx.players, name, i, validMines, isBot);
    }

    ctx.table.height = validHeight;
    ctx.table.width = validWidth;
    ctx.table.grid = std::vector<std::vector<CellState>>(validHeight, std::vector<CellState>(validWidth, CellState::Empty));
    static const bool kContinueForHuman = false;
    MineRender::enterToContinue(kContinueForHuman);
    return {&statePlaceMines};
}

State statePlaceMines(GameContext &ctx)
{
    MineRender::clearConsoleBuffer();
    MineRender::showBoard(ctx.table);
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
        MineRender::clearConsoleBuffer();
        MineRender::showBoard(ctx.table);
        MineRender::showMessage("It's a draw!\n");
        MineRender::enterToContinue(false);
        return {&stateMainMenuUpdate};
    }

    if (playersWithMines == 1)
    {
        for (const Player &player : ctx.players)
        {
            if (player.numberOfmines > 0)
            {
                MineRender::clearConsoleBuffer();
                MineRender::showBoard(ctx.table);
                MineRender::showWinner(player.name);
                MineRender::enterToContinue(false);
            }
        }
        return {&stateMainMenuUpdate};
    }

    MineGameContext::resetMines(ctx);
    if (ctx.table.cellCount < MinePlayer::amountOfTotalMines(ctx.players))
    {
        MineRender::clearConsoleBuffer();
        MineRender::showBoard(ctx.table);
        std::cout <<"There are "<< MinePlayer::amountOfTotalMines(ctx.players) 
                <<" mines left to place but there are " << ctx.table.cellCount 
                << " cells in the board\n";
        std::string noCellsLeftMessage = "There is no more available cells in the board D:\n";
        MineRender::applyColor(Color::Red, noCellsLeftMessage);
        std::cout << noCellsLeftMessage;
        MineRender::showWinner(MinePlayer::winnerPlayer(ctx.players).name);
        MineRender::enterToContinue(false);
        return {&stateMainMenuUpdate};
    }
    MinePlayer::eraseLoser(ctx.players);
    return {&statePlaceMines};
}
} //namespace MineGameStates
