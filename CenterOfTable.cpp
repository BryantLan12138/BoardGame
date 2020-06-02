#include "CenterOfTable.h"

CenterOfTable::CenterOfTable() : centerOfTable()
{
}

CenterOfTable::~CenterOfTable() {}

CenterOfTable::CenterOfTable(CenterOfTable &other) : centerOfTable(other.centerOfTable) {}

CenterOfTable::CenterOfTable(std::string dataOfTilesToLoad)
{
	//Loop through dataOfTiles to get each character in string
	for (char &c : dataOfTilesToLoad)
	{
		if (c == 'R')
		{
			Tile *red = new Tile(RED);
			centerOfTable.push_back(red);
		}
		else if (c == 'Y')
		{
			Tile *yellow = new Tile(YELLOW);
			centerOfTable.push_back(yellow);
		}
		else if (c == 'B')
		{
			Tile *darkBlue = new Tile(DARK_BLUE);
			centerOfTable.push_back(darkBlue);
		}
		else if (c == 'L')
		{
			Tile *lightBlue = new Tile(LIGHT_BLUE);
			centerOfTable.push_back(lightBlue);
		}
		else if (c == 'U')
		{
			Tile *black = new Tile(BLACK);
			centerOfTable.push_back(black);
		}
		else if (c == 'F')
		{
			Tile *firstMarker = new Tile(FIRST_MARKER);
			centerOfTable.push_back(firstMarker);
		}
	}
}
int CenterOfTable::size()
{
	return centerOfTable.size();
}

//Empty all elements
void CenterOfTable::clear()
{
	centerOfTable.clear();
}

//Get a pointer to the tile at a certain index
Tile *CenterOfTable::get(int i)
{
	Tile *tile = nullptr;
	if (i >= 0 && i < size())
	{
		tile = centerOfTable[i];
	}
	return tile;
}

//Add tiles to the back
void CenterOfTable::addTiles(Tile *tile)
{
	centerOfTable.push_back(tile);
}

//Add the F marker
void CenterOfTable::addFMarker()
{
	Tile *tile = new Tile(FIRST_MARKER);
	addTiles(tile);
}

//Remove tiles at certain index
void CenterOfTable::deleteTile(int index)
{
	if (size() > 0 &&
		index >= 0 && index < size())
	{
		for (int i = index; i < size() - 1; ++i)
		{ //Shift everrything to left
			centerOfTable[i] = centerOfTable[i + 1];
		}
		//Delete the last element since it is empty
		centerOfTable.pop_back();
	}
}

bool CenterOfTable::checkCenter(char colour){
	for (int i = 0; i < size(); i++){
		if (centerOfTable[i]->getColourAsChar() == colour){
			return true;
		}
	}
	return false;
}

//Print center tiles
void CenterOfTable::printCenter()
{
	std::cout << "0: ";
	for (int i = 0; i < size(); ++i)
	{
		char colour = centerOfTable[i]->getColourAsChar();
		if (colour == 'R'){
			std::cout << "\033[1;31m" << colour << "\033[0m" <<' ';
		}
		if (colour == 'Y'){
			std::cout << "\033[1;33m" << colour << "\033[0m" <<' ';
		}
		if (colour == 'U'){
			std::cout << "\033[1;30m" << colour << "\033[0m" <<' ';
		}
		if (colour == 'B'){
			std::cout << "\033[1;34m" << colour << "\033[0m" <<' ';
		}
		if (colour == 'L'){
			std::cout << "\033[1;96m" << colour << "\033[0m" <<' ';
		}
		if (colour == 'F'){
			std::cout << "\033[1;95m" << colour << "\033[0m" <<' ';
		}
	}
}

//Sort tiles in order of colour
void CenterOfTable::sortTiles()
{
	Tile *temp = nullptr;
	for (int i = 0; i < size(); ++i)
	{
		for (int j = i + 1; j < size(); ++j)
		{
			if (centerOfTable[i]->getColour() > centerOfTable[j]->getColour())
			{
				temp = centerOfTable[i];
				centerOfTable[i] = centerOfTable[j];
				centerOfTable[j] = temp;
			}
		}
	}
}

//Pick Tiles from given colour
void CenterOfTable::pickTiles(char colour, int row, Mosaic *mosaic)
{
	if (size() != 0)
	{
		// to set Mosaic display the First Player as broken tile
		bool firstPlayer = false;

		//If First Marker is present move that to the player's Mosaic
		if (centerOfTable[0]->getColour() == FIRST_MARKER)
		{
			deleteTile(0);
			firstPlayer = true;
		}
		int i = 0;
		while (i < size())
		{

			if (colour == centerOfTable[i]->getColourAsChar())
			{
				//Move the tile to the mosaic
				Tile *newTile = new Tile(centerOfTable[i]->getColour());
				mosaic->addTiles(newTile, row, firstPlayer);

				//Print out statement for testing
				std::cout << centerOfTable[i]->getColourAsChar() << " Picked" << std::endl;

				//Delete the tile that has been picked up from center
				deleteTile(i);

				firstPlayer = false;

				//Loop from index 0 again since size decreases after picking tiles
				i = 0;
			}
			else
			{
				i++;
			}
		}
	}
}
