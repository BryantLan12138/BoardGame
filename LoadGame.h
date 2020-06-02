#ifndef LOAD_GAME_H
#define LOAD_GAME_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "GameBoard.h"

/**
 * Instance of LoadGame automatically laod a textfile
 */
class LoadGame
{
public:
    LoadGame();
    ~LoadGame();

    /*
	 *Ask for a file to read
	 *check if file exist
	 *check if is a valid game
	 *save data one by one on variables
	 */
    void LoadGameData();

    //Create a gameboard with Loaded Data and start a game, also return the gameboard created
    GameBoard *startTheLoadedGame();

    //Print all variables that are loaded in this instance
    void printLoadedGameData();

    bool gameLoadCorrectly();

private:
    GameBoard *loadedGameBoard;

    bool gameLoadedCorrecty;

    //RandomSeed of the game
    int ramdomSeed;

    //Know if is the turn of player1
    bool player1Turn;

    //Names and score of both players
    std::string playerNames[2];
    int playerScores[2];

    //Two Player - Five lines in each player Mosaic
    std::string playerLines[2][5];
    //Broken tiles in mosaic of both players
    std::string playerBrokenTiles[2];
    //Wall in mosaic of both players
    std::string playerWalls[2];

    //CentreFactory/CenterOfTable and five factories of gameboard
    std::string centreFactory;
    std::string factoriesStringData[5];

    std::string lid;
    std::string tileBag;
};

#endif // !LOAD_GAME_H
