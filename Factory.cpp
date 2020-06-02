#include "Factory.h"


Factory::Factory()
{
	//Initialising length to zero, since the factory is empty at first
	length = 0;
	newTree = new BSTree<Tile>();
	//Initialsing the whole array of Factory to nullptr
	// for (int i = 0; i < MAX_LENGTH; ++i)
	// {
	// 	tiles[i] = nullptr;
	// }
}
//Clear memory
Factory::~Factory()
{
	clear();
}

Factory::Factory(std::string dataOfTilesToLoad)
{
	//Loop through dataOfTiles to get each character in string
	for (unsigned int i = 0; i < MAX_LENGTH; ++i)
	{
		if (i < dataOfTilesToLoad.size())
		{
			if (dataOfTilesToLoad[i] == 'R')
			{
				Tile *red = new Tile(RED);
				tiles[i] = red;
			}
			else if (dataOfTilesToLoad[i] == 'Y')
			{
				Tile *yellow = new Tile(YELLOW);
				tiles[i] = yellow;
			}
			else if (dataOfTilesToLoad[i] == 'B')
			{
				Tile *darkBlue = new Tile(DARK_BLUE);
				tiles[i] = darkBlue;
			}
			else if (dataOfTilesToLoad[i] == 'L')
			{
				Tile *lightBlue = new Tile(LIGHT_BLUE);
				tiles[i] = lightBlue;
			}
			else if (dataOfTilesToLoad[i] == 'U')
			{
				Tile *black = new Tile(BLACK);
				tiles[i] = black;
			}
		}
		else if (dataOfTilesToLoad.size() == 0)
		{

			tiles[i] = nullptr;
			length = 0;
		}
	}

	// length = MAX_LENGTH;
}

//Returns size
int Factory::getSize()
{
	return length;
}

//Get a pointer to a tile at index
Tile *Factory::getTile(int index)
{
	
	Tile *tile = nullptr;
	if (index >= 0 && index < length)
	{
		tile = tiles[index];
	}
	return tile;
}

// Tile *Factory::getTile()

// Fill factory with tiles taken from TileBag
void Factory::fillFactory(TileBag *tileBag)
{
	

	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		newTree->Insert(*tileBag->get(i));
		// tiles[i] = new Tile(tileBag->get(i)->getColour());
		// tileBag->deleteTile(i);
	}

	length = MAX_LENGTH;
}

// new one with binary tree
// void Factory::fillFactory(TileBag *tileBag){
// 	for (int i = 0; i < MAX_LENGTH; ++i)
// 	{
// 		newTree->Insert(tileBag->get(i));
// 		tileBag->deleteTile(i);
// 	}
// 	length = MAX_LENGTH;
// }

bool Factory::checkFactory(char colour)
{
	if (length != 0){
		for (int i = 0; i < MAX_LENGTH; i++)
		{
			if (tiles[i]->getColourAsChar() == colour)
			{
				return true;
			}
		}
	}
	return false;
}

// // new checkFactory with binary tree
// bool Factory::checkFactory(Colour colour)
// {
// 	if (newTree != nullptr)
// 	{
// 		for (int i = 0; i < MAX_LENGTH; i++)
// 		{
// 			if (newTree->get(colour, )->getColourAsChar() == colour)
// 			{
// 				return true;
// 			}
// 		}
// 	}
// 	return false;
// }

//Pick a tile and move it to the mosaic, while the rest gets moved to the center
void Factory::pickTiles(char colour, CenterOfTable *centerOfTable, int row, Mosaic *mosaic)
{

	if (length != 0)
	{
		for (int i = 0; i < length; ++i)
		{
			//Get the specific colour
			if (colour == tiles[i]->getColourAsChar())
			{
				//Move the tile to the mosaic
				Tile *newTile = new Tile(tiles[i]->getColour());
				mosaic->addTiles(newTile, row, false);

				//Uncomment for testsing
				// std::cout << tiles[i]->getColourAsChar() << " Picked" << std::endl;
			}
			//Move the remaining tiles to the center
			else if (colour != tiles[i]->getColourAsChar())
			{
				moveCenter(centerOfTable, i);
			}
		}
		//Clear memory of factory
		clear();
	}
	else
	{
		std::cout << "Factory empty" << std::endl;
	}
}

//Print factory info
void Factory::printFactoryInfo()
{
	 
	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		char colour = tiles[i]->getColourAsChar();
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
	}
}

//Add tiles to the center of table
void Factory::moveCenter(CenterOfTable *centerOfTable, int index)
{

	centerOfTable->addTiles(new Tile(tiles[index]->getColour()));
}

//Remove tiles at specific index (unused)
void Factory::removeTile(int index)
{
	if (length > 0 &&
		index >= 0 && index < length)
	{
		Tile *toRemove = tiles[index];
		for (int i = index; i < length; ++i)
		{

			tiles[i] = tiles[i + 1];
		}

		tiles[length] = nullptr;
		delete toRemove;
		--length;
	}
	else
	{
		std::cout << "Error" << std::endl;
	}
}

//Sort tiles in order of colour
void Factory::sortTiles()
{
	Tile *temp = nullptr;
	for (int i = 0; i < length; ++i)
	{
		for (int j = i + 1; j < length; ++j)
		{
			if (tiles[i]->getColour() > tiles[j]->getColour())
			{
				temp = tiles[i];
				tiles[i] = tiles[j];
				tiles[j] = temp;
			}
		}
	}
}

//Clear memeory and reset length
void Factory::clear()
{
	for (int i = 0; i < length; ++i)
	{
		delete tiles[i];
		tiles[i] = nullptr;
	}
	length = 0;
}
