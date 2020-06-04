#ifndef MOSAIC_H
#define MOSAIC_H
#define MOSAIC_LENGTH 6
#define BROKEN_LENGTH 20
#define FIRST 1

#include <iostream>
#include <algorithm>
#include "Tile.h"
#include "Score.h"
#include "BoxLid.h"

class Mosaic
{
public:
	Mosaic();
	~Mosaic();
	Mosaic(std::string dataOfBrokenTilesToLoad, std::string dataOfWallToLoad, std::string dataOfLinesToLoad[5]);

	//Add tiles to mosaic
	void addTiles(Tile *tile, int row, bool firstPlayer);

	//Print Mosaic
	void printMosaic(bool extension);

	char **getLeftPart();
	char **getRightPart();
	char *getBroken();
	//To finish the wall tiling
	void wallTiling();

	// check if the tiles adding to mosaic needs to put on floor lines as called as BROKEN TILES
	void checkBroken();

	// add new broken tiles into the 2d array
	void addBroken(Colour colour);

	// get each round score
	int getRoundScore(int playerTurn);

	// the final score
	int getFinalScore(int playerTurn);

	// by checking 2d array (the right part), return true if the game is end, else false
	bool checkEndGame();

	// getting the colourofChar and return a enum Colour
	Colour getColour(char colour);

	//get boxLid
	BoxLid *getBoxLid();

	void printColour(char colour);

	int getTotalScore(int playerTurn);

private:
	int mosaic_length;
	bool extension;
	struct Node *head;
	char **leftPart = nullptr;
	char **rightPart = nullptr;
	char *brokenTiles = nullptr;
	char final_tiles[MOSAIC_LENGTH][MOSAIC_LENGTH + 1] = {"BYRUL", "LBYRU", "ULBYR", "RULBY", "YRULB"};
	Score *score[2];
	BoxLid *boxlid;
};

#endif // MOSAIC_H
