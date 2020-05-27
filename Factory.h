#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <fstream>
// #include <vector>
// #include <algorithm>

#include <string>
#include "TileBag.h"
#include "CenterOfTable.h"
#include "Mosaic.h"
#include "Player.h"

#define MAX_LENGTH 4

class Factory
{

public:
	Factory();
	~Factory();
	Factory(std::string dataOfTilesToLoad);

	//Keep track of size
	int getSize();

	//Get a pomiter to a tile at a certain index
	Tile *getTile(int index);

	//Fill with random tiles from the Tile Bag
	void fillFactory(TileBag *tileBag);

	//Return factory info sorted
	void printFactoryInfo();

	//Sort Factory Tiles()
	void sortTiles();

	//Pick a tile from the colour chosen by User and move the remaining tiles to center of table
	void pickTiles(char colour, CenterOfTable *centerOfTable, int row, Mosaic *mosaic);

	//Move the remaining tiles to the center of the table
	void moveCenter(CenterOfTable *centerOfTable, int index);

	//Remove the tile at the given index
	void removeTile(int index);

	//Clear the factory
	void clear();

private:
	// TileBag *tileBag;
	int length;
	Tile *tiles[MAX_LENGTH];
};

#endif // !FACTORY_H