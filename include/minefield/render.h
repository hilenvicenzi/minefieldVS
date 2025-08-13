#pragma once 
#include <string>
#include "board.h"
#include "player.h"

struct Board;
struct Player;
enum class Color
{
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

namespace MineRender
{
char const *const colorString(Color forColor);
std::string applyColorWindows(Color color, std::string const &toMessage);
std::string applyColorPosix(Color color, std::string const &toMessage);
std::string applyColor(Color color, std::string const &toMessage);

void showMenu();

void showGameTittle(const Board &board);

void showPlayerData(const Player &player);

void clearConsoleBuffer();

void enterToContinue(bool isBot);

void clsAndShowBoard(Board const &board, bool isBot);

void showConfigurationTitle();

void showTableMeasurement();

void showMinesLimits();

void showAmountOfHumanPlayers();

void showAmountOfBotPlayers();
}