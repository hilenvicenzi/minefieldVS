#include "minefield/player.h"
#include <iostream>
#include <sstream>

namespace MinePlayer
{
    void addNewPlayer(std::vector<Player> &players, std::string playerName, int number, unsigned int mines, bool isBot)
    {
        Player newPlayer{playerName, number, mines, isBot, {}, {}};
        players.push_back(newPlayer);
    }

    void setPlayersNames(std::vector<Player> &player, const std::string &playerName, int number, unsigned int mines, bool isBot)
    {
        MinePlayer::addNewPlayer(player, playerName, number, mines, isBot);
    }

    int getPlayersWithMines(const std::vector<Player> &players)
    {
        int playersWithMines = 0;
        for (const Player &player : players)
        {
            if (player.numberOfmines > 0)
            {
                playersWithMines++;
            }
        }
        return playersWithMines;
    }

    void eraseLoser(std::vector<Player> &players)
    {
        players.erase(
            std::remove_if(players.begin(), players.end(), [](const Player &player)
                           { return player.numberOfmines == 0; }),
            players.end());
    }

    Player winnerPlayer(const std::vector<Player> &players)
    {
        Player winner = players[0];
        for (const Player &player : players)
        {
            if (player.numberOfmines > winner.numberOfmines)
            {
                winner = player;
            }
        }
        return winner;
    }

    unsigned int amountOfTotalMines(const std::vector<Player> &players)
    {
        unsigned int mineCount = 0;
        for (const Player &player : players)
        {
            mineCount += player.numberOfmines;
        }
        return mineCount;
    }
}