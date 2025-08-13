#include "minefield/render.h"
#include <iostream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <chrono> 

namespace MineRender 
{
char const *const colorString(Color forColor)
{
    switch (forColor)
    {
    case Color::Red:
        return "\033[1;31m";
    case Color::Green:
        return "\033[1;32m";
    case Color::Yellow:
        return "\033[1;33m";
    case Color::Blue:
        return "\033[1;34m";
    case Color::Magenta:
        return "\033[1;35m";
    case Color::Cyan:
        return "\033[1;36m";
    case Color::White:
        return "\033[1;37m";
    default:
        return "InvalidColor";
    }
}

std::string applyColorWindows(Color color, std::string const &toMessage)
{
    static char const* const kResetColor = "\033[0m";
    return std::string{MineRender::colorString(color)} + toMessage + kResetColor;
}

std::string applyColorPosix(Color color, std::string const &toMessage)
{
    static char const *const kResetColor = "\033[0m";
    return std::string{MineRender::colorString(color)} + toMessage + kResetColor;
}

std::string applyColor(Color color, std::string const &toMessage)
{
#ifdef WIN32
    return applyColorWindows(color, toMessage);
#else
    return MineRender::applyColorPosix(color, toMessage);
#endif
}

void showMenu()
{
    std::string titleMenu = MineRender::applyColor(Color::Yellow, "===== MENU =====\n");
    std::cout << titleMenu;
    std::cout << "1. Play\n2. Quit\n> ";
}

void showGameTittle(const Board &board)
{
    static const unsigned int kCellWidth = 4;
    static const unsigned int kEdge = 12;
    unsigned int boardWidth = (board.width * kCellWidth) + kEdge;
    std::string boardTitle = MineRender::applyColor(Color::Red, "MINEFIELD");
    unsigned int padding = (boardWidth - boardTitle.length()) / 2;
    std::cout << std::setfill('=') << std::setw(padding)        // left fill
              << ' ' << boardTitle << ' '                       // tittle with spaces
              << std::setw(padding) << ' ' << std::setfill(' ') // right fill
              << '\n';
}

void showPlayerData(Player const &player)
{
    if (player.isBot)
    {
        std::cout << "The computer is locating the mines\n";
        std::cout << "The computer "<< player.name <<" has " << player.numberOfmines << " mines left\n";
    }
    else
    {
        std::cout << "Player " << player.name << " can enter the coordinates of the mines\n";
        std::cout << "You have " << player.numberOfmines << " mines left\n";
    }
}

void clearConsoleBuffer()
{
    static std::mutex mutex;
    std::lock_guard<std::mutex> lock(mutex);

    static char const *const kClearConsoleBufferCommand = "cls";
    system(kClearConsoleBufferCommand);
}

void enterToContinue(bool isBot)
{ 
    if(isBot)
    {
        std::string outMessageBot = MineRender::applyColor(Color::Yellow, "\nThe computer is thinking...");
        std::cout << outMessageBot;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    else
    {
        std::string outMessageEnter = MineRender::applyColor(Color::Yellow, "\nPress ENTER to continue...");
        std::cout << outMessageEnter;
        std::cin.ignore();
        std::cin.get();
    }
}

void clsAndShowBoard(Board const &board, bool isBot)
{
    enterToContinue(isBot);
    clearConsoleBuffer();
    MineBoard::showBoard(board);
}

void showConfigurationTitle()
{
    std::string configurationTitle = MineRender::applyColor(Color::Yellow, "===== CONFIGURATION =====\n");
    std::cout << configurationTitle;
}

void showTableMeasurement()
{
    std::cout << "\nTable measurements must be between " << kMinDim << " and " << kMaxDim << '\n';
}

void showMinesLimits()
{
    std::cout << "\nYou can play with between " << kMinMine << " to " << kMaxMine << " mines" << '\n';
    std::string amountOfPlayerTittle = MineRender::applyColor(Color::Cyan, "How many mines per players?: ");
    std::cout << amountOfPlayerTittle;
}

void showAmountOfHumanPlayers()
{
    std::string amountOfHumanPlayersTitle = MineRender::applyColor(Color::Green, "\nHow many human players?: ");
    std::cout << amountOfHumanPlayersTitle;
}

void showAmountOfBotPlayers()
{
    std::string amountOfBotPlayersTittle = MineRender::applyColor(Color::Green, "How many bot players: ");
    std::cout << amountOfBotPlayersTittle;
}
}