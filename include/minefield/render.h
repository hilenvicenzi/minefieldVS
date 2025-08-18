#pragma once 
#include <string>
#include "minefield/board.h"
#include "minefield/player.h"

struct Board;
struct Player;
struct Coord;
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

void showBoard(const Board &board);

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

void showMineAtPosition(int j, Coord const &mine);

void showGuessNumber(int j);

void showGuessAtPosition(int j, Coord const &mine);

void showAmountOfGuessForAPLayer(const std::string &name, const unsigned int &guesses);

void showMessage(std::string message);

void showWinner(std::string name);

}