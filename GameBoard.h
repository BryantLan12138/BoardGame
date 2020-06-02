#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include "Factory.h"
#include "Player.h"
#include "CenterOfTable.h"
#include "Mosaic.h"

#define TOTAL_FACTORY_NUM 5
#define TOTAL_PLAYERS 2
#define TOTAL_MOSAICS 2
class GameBoard
{

public:
	GameBoard();
	GameBoard(int seed);
	GameBoard(int ramdomSeed, bool player1Turn, std::string playerNames[2],
			  int playerScores[2], std::string playerLines[2][5], std::string playerBrokenTiles[2],
			  std::string playerWalls[2], std::string centreFactory, std::string factoriesStringData[5],
			  std::string tileBagString, std::string boxLidString);
	~GameBoard();

	//Create the two players
	void createPlayer(std::string playerName1, std::string playerName2);

	//Returns a player at given index
	Player *getPlayer(int index);

	//Fill each factory with tiles from the bag
	void fillFactories();

	//Prints each factory
	void printFactories();

	//Returns a factory at given row
	Factory *getFactory(int row);

	//Pick a tile from factory
	bool pickTileFromFactory(int factory, char colour, int row, int player);

	//Declares the end of the round
	bool endRound();

	//Declares the end of game
	bool endGame(Mosaic *mosaic);

	//Get a pointer to center
	CenterOfTable *getCenter();

	//Get a pointer to tileBag
	TileBag *getTileBag();

	//Get a pointer to boxLid
	BoxLid *getBoxLid();

	void loadLid(std::string lid);

	void loadFactories(std::string factories[5]);

	void loadCenterOfTable(std::string centreFactory);

	void loadMosaic(std::string playerLines[2][5]);

	void loadWall(std::string playerWalls[2]);

	void loadBroken(std::string playerBrokenTiles[2]);

private:
	TileBag *tileBag;

	BoxLid *boxLid;

	CenterOfTable *centerOfTable;

	//Mosaic for each player
	Mosaic *mosaic[TOTAL_PLAYERS];

	//Array that contains the two players
	Player *players[TOTAL_PLAYERS];

	//Array that contains all five factories
	Factory *factories[TOTAL_FACTORY_NUM];
};

#endif // !GAMEBOARD_H