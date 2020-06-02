#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Mosaic.h"

/**
 * Represents a single player in Azul.
 */
class Player
{
public:
    Player();
    Player(std::string playerName, int playerPoints);
    Player(Player &other);
    Player(std::string playerNameToLoad, int scoreToLoad, bool playerTurnToLoad);
    ~Player();

    //Return the player name
    std::string getPlayerName();

    //Return the player score
    int getPlayerPoints();

    //Set the player score
    void setPlayerPoints(int playerPoints);

    //Set the player name
    void setPlayerName(std::string playerName);

    //If the player's turn or not
    void setTurn(bool playerTurn);

    //Return bool playTurn
    bool getTurn();

    //Initialise player with a mosaic
    void setMosaic(Mosaic *mosaic);

    //Return player Mosaic (Mosaic class to be implemented)
    Mosaic *getMosaic();

    void savePlayerInfo();

private:
    std::string playerName;
    int playerPoints;
    bool playerTurn;
    Mosaic *mosaic;
};

#endif // PLAYER_H
