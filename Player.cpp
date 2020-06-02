#include "Player.h"

Player::Player()
{
}

Player::Player(std::string playerNameToLoad, int scoreToLoad, bool playerTurnToLoad)
{
    this->playerName = playerNameToLoad;
    this->playerPoints = scoreToLoad;
    playerTurn = playerTurnToLoad;
}

Player::Player(std::string playerName, int playerPoints)
{
    this->playerName = playerName;
    this->playerPoints = playerPoints;
    playerTurn = false;
}

Player::Player(Player &other)
{
    this->playerName = other.playerName;
    this->playerPoints = other.playerPoints;
}

Player::~Player()
{
}

std::string Player::getPlayerName()
{
    return playerName;
}

int Player::getPlayerPoints()
{
    return playerPoints;
}

void Player::setPlayerPoints(int playerPoints)
{
    this->playerPoints = playerPoints;
}

void Player::setPlayerName(std::string playerName)
{
    this->playerName = playerName;
}

void Player::setTurn(bool playerTurn)
{
    this->playerTurn = playerTurn;
}

bool Player::getTurn()
{
    return playerTurn;
}

void Player::setMosaic(Mosaic *mosaic)
{
    this->mosaic = mosaic;
}

Mosaic *Player::getMosaic()
{
    return mosaic;
}

