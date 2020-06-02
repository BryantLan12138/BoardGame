#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "GameBoard.h"
#include <fstream>

class SaveGame
{
public:
    SaveGame();
    ~SaveGame();

    //Save the current state of game board
    void SaveGameState(GameBoard *gameBoard);
    //Save each player information
    void savePlayers(GameBoard *gameBoard, std::ofstream &save);
    //Save center of table (center factory)
    void saveCenter(GameBoard *gameBoard, std::ofstream &save);
    //Save each factory and the tiles it contains
    void saveFactories(GameBoard *gameBoard, std::ofstream &save);
    //Save the triangle part of the player's mosaic (left side) row by row
    void saveMosaicLeftPart(GameBoard *gameBoard, std::ofstream &save, bool player);
    //Save the broken tiles of player's mosaic
    void saveMosaicBroken(GameBoard *gameBoard, std::ofstream &save, bool player);
    //Save the wall area of player's mosaic (right side)
    void saveMosaicRightPart(GameBoard *gameBoard, std::ofstream &save, bool player);
    //Save the whole mosaic of player (left, broken and right sides combined)
    void savePlayerMosaic(GameBoard *gameBoard, std::ofstream &save);
    //Save the box lid
    void saveBoxLid(GameBoard *gameBoard, std::ofstream &save);
    //Save the tile bag
    void saveTileBag(GameBoard *gameBoard, std::ofstream &save);

private:
    // GameBoard *gameBoard;
};
#endif // !SAVE_GAME_H