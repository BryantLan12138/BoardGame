#ifndef CENTER_OF_TABLE_H
#define CENTER_OF_TABLE_H

#include <iostream>
#include <vector>

#include "Tile.h"
#include "Mosaic.h"

class CenterOfTable
{

public:
	CenterOfTable();
	CenterOfTable(CenterOfTable &other);
	CenterOfTable(std::string dataOfTilesToLoad);
	~CenterOfTable();

	//Returns size of center
	int size();
	//Cleat center
	void clear();
	//Get a point to a Tile at index
	Tile *get(int i);
	//Add tiles to center
	void addTiles(Tile *tile);
	//Add the F marker
	void addFMarker();
	//Pick a tile from the center and move it to the Mosaic
	void pickTiles(char colour, int row, Mosaic *mosaic);
	//Delete tile at certain index
	void deleteTile(int index);
	//Print out all the tiles
	void printCenter();
	//Sort tiles in order of colour
	void sortTiles();
	bool checkCenter(char colour);

private:
	std::vector<Tile *> centerOfTable;
};

#endif // CENTER_OF_TABLE_H
