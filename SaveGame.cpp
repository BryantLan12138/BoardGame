#include "SaveGame.h"

SaveGame::SaveGame()
{
}

SaveGame::~SaveGame() {}
void SaveGame::SaveGameState(GameBoard *gameBoard)
{
    std::ofstream save("SaveGame.txt");
    if (gameBoard != nullptr)
    {
        //Save player info for playerTurn, playerName, playerPoints(score)
        savePlayers(gameBoard, save);

        //Save centerOfTable
        saveCenter(gameBoard, save);

        //Save tiles of each factory
        saveFactories(gameBoard, save);

        //Save mosaic for each player
        savePlayerMosaic(gameBoard, save);

        //Save the boxLid
        saveBoxLid(gameBoard, save);

        //Save the tileBag
        saveTileBag(gameBoard, save);
    }
    else
    {
        std::cout << "NULL" << std::endl;
    }

    save.close();
}

void SaveGame::savePlayers(GameBoard *gameBoard, std::ofstream &save)
{
    save << gameBoard->getPlayer(0)->getTurn() << std::endl;
    for (int i = 0; i < 2; ++i)
    {
        save << gameBoard->getPlayer(i)->getPlayerName() << std::endl;
        save << gameBoard->getPlayer(i)->getPlayerPoints() << std::endl;
    }
}

void SaveGame::saveCenter(GameBoard *gameBoard, std::ofstream &save)
{
    for (int i = 0; i < gameBoard->getCenter()->size(); ++i)
    {
        //If empty print an empty line otherwise save all the tiles
        if (gameBoard->getCenter()->size() != 0)
        {
            save << gameBoard->getCenter()->get(i)->getColourAsChar();
        }
        else if (gameBoard->getCenter()->size() == 0)
        {
            save << '\n';
        }
    }
    save << '\n';
}

void SaveGame::saveFactories(GameBoard *gameBoard, std::ofstream &save)
{
    for (int i = 0; i < 5; ++i)
    {
        //Make sure factory is not empty
        if (gameBoard->getFactory(i)->getSize() != 0)
        {
            for (int j = 0; j < 4; ++j)
            {
                save << gameBoard->getFactory(i)->getTile(j)->getColourAsChar();
            }
            save << '\n';
        }
        //If factory is empty print an empty line
        else if (gameBoard->getFactory(i)->getSize() == 0)
        {
            save << '\n';
        }
    }
}

void SaveGame::saveMosaicLeftPart(GameBoard *gameBoard, std::ofstream &save, bool player)
{
    char **leftpart = gameBoard->getPlayer(player)->getMosaic()->getLeftPart();
    if (leftpart != nullptr)
    {
        for (int i = FIRST; i < MOSAIC_LENGTH + 1; i++)
        {
            for (int j = 0; j < i; j++)
            {
                save << leftpart[i - 1][j];
            }
            save << '\n';
        }
    }
}

void SaveGame::saveMosaicBroken(GameBoard *gameBoard, std::ofstream &save, bool player)
{

    char *broken = gameBoard->getPlayer(player)->getMosaic()->getBroken();
    for (int i = 0; i < BROKEN_LENGTH; ++i)
    {
        if (broken[i] != '0')
        {
            save << broken[i];
        }
    }
    save << '\n';
}

void SaveGame::saveMosaicRightPart(GameBoard *gameBoard, std::ofstream &save, bool player)
{

    char **rightPart = gameBoard->getPlayer(player)->getMosaic()->getRightPart();
    for (int i = FIRST; i < MOSAIC_LENGTH + 1; i++)
    {
        for (int j = 0; j < MOSAIC_LENGTH; ++j)
        {
            save << rightPart[i - 1][j];
        }
    }
}

void SaveGame::savePlayerMosaic(GameBoard *gameBoard, std::ofstream &save)
{
    //loop twice for each player
    for (int i = 0; i < 2; ++i)
    {
        //Save left part of mosaic
        saveMosaicLeftPart(gameBoard, save, i);
        //Save mosaic broken
        saveMosaicBroken(gameBoard, save, i);
        //Save mosaic right side (wall)
        saveMosaicRightPart(gameBoard, save, i);
        save << '\n';
    }
}

void SaveGame::saveBoxLid(GameBoard *gameBoard, std::ofstream &save)
{
    for (int i = 0; i < gameBoard->getBoxLid()->size() - 1; ++i)
    {
        if (gameBoard->getBoxLid()->size() != 0)
        {
            save << gameBoard->getBoxLid()->getTile(i)->getColourAsChar();
        }
        else if (gameBoard->getBoxLid()->size() != 0)
        {
            save << '\n';
        }
    }
}

//Save the tileBag
void SaveGame::saveTileBag(GameBoard *gameBoard, std::ofstream &save)
{
    for (int i = 0; i < gameBoard->getTileBag()->size() - 1; ++i)
    {
        save << gameBoard->getTileBag()->get(i)->getColourAsChar();
    }
    save << '\n';
}