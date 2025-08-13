#pragma once
#include <string>
#include <vector>
#include "coord.h"

struct Coord;

struct Player
{
    std::string name;
    int id = 0;
    unsigned int numberOfmines = 0;
    bool isBot = false;
    std::vector<Coord> playerMines;
    std::vector<Coord> playerGuesses;
};

namespace MinePlayer
{
void addNewPlayer (std::vector<Player> &player, std::string playername, int number, unsigned int mines, bool isBot);

void setPlayersNames(std::vector<Player> &player, int number, unsigned int mines, bool isBot);

int getPlayersWithMines(const std::vector<Player> &players);

void eraseLoser(std::vector<Player> &players);

Player winnerPlayer (const std::vector<Player> &players);

unsigned int amountOfTotalMines(const std::vector<Player> &players);
} // namespace MinePlayer
