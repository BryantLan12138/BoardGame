#include "GameBoard.h"

GameBoard::GameBoard(int seed, bool extension)
{
	centerOfTable = new CenterOfTable();
	tileBag = new TileBag(seed, extension);
	boxLid = new BoxLid();

	//Initialise mosaic for each player
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		mosaic[i] = new Mosaic();
	}

	//Initialise both players to nullptr
	for (int i = 0; i < TOTAL_PLAYERS; ++i)
	{
		players[i] = nullptr;
	}

	//Initialise each factory to nullptr
	for (int i = 0; i < TOTAL_FACTORY_NUM; ++i)
	{
		factories[i] = nullptr;
	}
}

GameBoard::GameBoard() {}

GameBoard::GameBoard(int ramdomSeed, bool player1Turn, std::string playerNames[2],
					 int playerScores[2], std::string playerLines[2][5], std::string playerBrokenTiles[2],
					 std::string playerWalls[2], std::string centreFactory, std::string factoriesStringData[5],
					 std::string tileBagString, std::string boxLidString)
{

	//Load seedRandom and set
	// this->seedRandom = ramdomSeed;
	// srand(seedRandom);

	//Load and set TileBag
	tileBag = new TileBag(tileBagString);

	//Load Mosaics
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		mosaic[i] = new Mosaic(playerBrokenTiles[i], playerWalls[i], playerLines[i]);
	}

	/*
	 *Players Load Data constructor
	 *Players created one after anothoer, send player1turn to first player and the opposite value to player two
	 */
	players[0] = new Player(playerNames[0], playerScores[0], player1Turn);
	players[0]->setMosaic(mosaic[0]);

	players[1] = new Player(playerNames[1], playerScores[1], !player1Turn);
	players[1]->setMosaic(mosaic[1]);

	//Load and set factories
	for (int i = 0; i < TOTAL_FACTORY_NUM; i++)
	{
		factories[i] = new Factory(factoriesStringData[i]);
	}

	//Load and set CenterOfTable
	centerOfTable = new CenterOfTable(centreFactory);
}

GameBoard::~GameBoard()
{
	//Clear each Mosaic
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		if (mosaic[i] != nullptr)
		{
			delete mosaic[i];
			mosaic[i] = nullptr;
		}
	}

	//Clear each player
	for (int i = 0; i < TOTAL_PLAYERS; ++i)
	{
		if (players[i] != nullptr)
		{
			delete players[i];
			players[i] = nullptr;
		}
	}

	//Clear each factory
	for (int i = 0; i < TOTAL_FACTORY_NUM; ++i)
	{
		if (factories[i]->getSize() != 0)
		{
			factories[i]->clear();
			factories[i] = nullptr;
		}
	}

	delete tileBag;
	delete centerOfTable;
	delete boxLid;
}

void GameBoard::loadLid(std::string lid)
{
	if (!lid.empty())
	{
		// boxLid->addFront()
	}
}

void GameBoard::loadFactories(std::string factories[5])
{
}

void GameBoard::loadMosaic(std::string playerLines[2][5])
{
}

void GameBoard::loadWall(std::string playerWalls[2])
{
}

void GameBoard::loadBroken(std::string playerBrokenTiles[2])
{
}

//Create both players
void GameBoard::createPlayer(std::string playerName1, std::string playerName2)
{

	players[0] = new Player(playerName1, 0);
	players[0]->setMosaic(mosaic[0]);

	players[1] = new Player(playerName2, 0);
	players[1]->setMosaic(mosaic[1]);
}

//Return a player at certain index
Player *GameBoard::getPlayer(int index)
{
	Player *player = nullptr;
	if (index >= 0 && index < TOTAL_PLAYERS)
	{
		player = players[index];
	}
	return player;
}

//Fill each factory with 4 tiles and sort in correct order
void GameBoard::fillFactories()
{
	for (int i = 0; i < TOTAL_FACTORY_NUM; ++i)
	{
		factories[i] = new Factory();
		factories[i]->fillFactory(tileBag);
		factories[i]->sortTiles();
	}
}

//Print out the each factory in a row
void GameBoard::printFactories()
{
	centerOfTable->sortTiles();
	centerOfTable->printCenter();
	std::cout << std::endl;
	for (int i = 0; i < TOTAL_FACTORY_NUM; ++i)
	{
		if (factories[i]->getSize() != 0)
		{
			std::cout << i + 1 << ": ";
			factories[i]->printFactoryInfo();
			std::cout << std::endl;
		}
		else
		{
			std::cout << i + 1 << ": " << std::endl;
		}
	}
}

//Return a factory at certain index
Factory *GameBoard::getFactory(int row)
{
	Factory *factory = nullptr;
	if (row >= 0 && row < TOTAL_FACTORY_NUM)
	{
		factory = factories[row];
	}
	return factory;
}

//Pick a tile from factory to move to the speicified row of player's mosaic, remaining tiles moved to center of table
bool GameBoard::pickTileFromFactory(int factory, char colour, int row, int playerTurn)
{
	if (factory >= 0 && factory <= TOTAL_FACTORY_NUM)
	{
		if (factory == 0)
		{
			if (centerOfTable->checkCenter(colour)){
				//Pick tiles from center of table
				centerOfTable->pickTiles(colour, row, mosaic[playerTurn]);
			}else{
				std::cout << "Center of table doesn't have the colour tile you pick." << std::endl;
				return false;
			}
		}
		else
		{
			if (factories[factory - 1]->checkFactory(colour)){
				// to minus one because of index starting at 0
				factories[factory - 1]->pickTiles(colour, centerOfTable, row, mosaic[playerTurn]);
			}else{
				std::cout << "The factory doesn't have the colour tile you pick." << std::endl;
				return false;
			}
		}
		players[playerTurn]->setMosaic(mosaic[playerTurn]);
		return true;
	}
	else{
		return false;
	}
}

//End the round when there are no more tile on center of table
bool GameBoard::endRound()
{
	bool complete[TOTAL_FACTORY_NUM] = {false, false, false, false, false};
	for (int i = 0; i < TOTAL_FACTORY_NUM; i++)
	{
		if (!(factories[i]->getSize() != 0 || centerOfTable->size() != 0))
		{
			complete[i] = true;
		}
	}

	for (int i = 0; i < TOTAL_FACTORY_NUM; i++)
	{
		if (!complete[i])
		{
			return false;
		}
	}

	return true;
}

//End the whole game
bool GameBoard::endGame(Mosaic *mosaic)
{
	bool returnVal = false;
	if (mosaic->checkEndGame())
	{
		returnVal = true;
	}
	return returnVal;
}

CenterOfTable *GameBoard::getCenter()
{
	return centerOfTable;
}

TileBag *GameBoard::getTileBag()
{
	return tileBag;
}

BoxLid *GameBoard::getBoxLid()
{
	return boxLid;
}