#include "LoadGame.h"

LoadGame::LoadGame()
{
    //Try to load a game right after objects is created
    LoadGameData();
}

LoadGame::~LoadGame()
{
}

void LoadGame::LoadGameData()
{

    std::string fileToRead;

    //Track if file to load is valid
    std::cout << "IsAValid game set true" << std::endl;
    bool isAValidGame = true;
    gameLoadedCorrecty = false;

    //Track the index to know line of information
    int indexLine = 0;

    //Ask for a filename to read and save in fileToRead
    std::cout << "Enter a filename from wich load a game" << std::endl;
    std::cout << "> ";
    std::cin >> fileToRead;

    //Add extension .txt
    fileToRead += ".txt";

    //Charge a file with fileToRead Name
    std::ifstream file(fileToRead);
    std::string str;

    //Check if file exist
    if (!file.fail())
    {

        while (std::getline(file, str))
        {
            /*
			 *each line of the file belongs to a data
			 *so, track iterations in indexLine to know the corresponding line
			 */

            //Load randomSeed
            // if (indexLine == 0)
            // {
            //     try
            //     {
            //         ramdomSeed = std::stoi(str);
            //     }
            //     catch (const std::exception &)
            //     {
            //         std::cout << "Invalid loading random seed" << std::endl;
            //         isAValidGame = false;
            //     }
            // }

            //Load if player 1 turn
            if (indexLine == 0)
            {
                bool boolRead;
                std::stringstream ss(str);
                if (ss >> boolRead)
                {
                    player1Turn = boolRead;
                }
                else
                {
                    std::cout << "Invalid loading player 1 turn" << std::endl;
                    isAValidGame = false;
                }
            }

            //Load player 1 name
            if (indexLine == 1)
            {
                playerNames[0] = str;
            }

            //Load player 1 score
            if (indexLine == 2)
            {
                try
                {
                    //cast string into an integer, set invalidGame as false if can not cast
                    playerScores[0] = std::stoi(str);
                }
                catch (const std::exception &)
                {
                    std::cout << "Invalid loading player 1 score" << std::endl;
                    isAValidGame = false;
                }
            }

            //Load player 2 name
            if (indexLine == 3)
            {
                playerNames[1] = str;
            }

            //Load player 2 score
            if (indexLine == 4)
            {
                //cast string into an integer, set invalidGame as false if can not cast
                try
                {
                    playerScores[1] = std::stoi(str);
                }
                catch (const std::exception &)
                {
                    std::cout << "Invalid loading player 2 score" << std::endl;
                    isAValidGame = false;
                }
            }

            //Load Centre Factory
            if (indexLine == 5)
            {
                centreFactory = str;
            }

            //Load Factory 1
            if (indexLine == 6)
            {
                factoriesStringData[0] = str;
            }

            //Load Factory 2
            if (indexLine == 7)
            {
                factoriesStringData[1] = str;
            }

            //Load Factory 3
            if (indexLine == 8)
            {
                factoriesStringData[2] = str;
            }

            //Load Factory 4
            if (indexLine == 9)
            {
                factoriesStringData[3] = str;
            }

            //Load Factory 5
            if (indexLine == 10)
            {
                factoriesStringData[4] = str;
            }

            // Player1 1st Line
            if (indexLine == 11)
            {
                playerLines[0][0] = str;
            }

            // Player1 2nd Line
            if (indexLine == 12)
            {
                playerLines[0][1] = str;
            }

            // Player1 3rd Line
            if (indexLine == 13)
            {
                playerLines[0][2] = str;
            }

            // Player1 4th Line
            if (indexLine == 14)
            {
                playerLines[0][3] = str;
            }

            // Player1 5th Line
            if (indexLine == 15)
            {
                playerLines[0][4] = str;
            }

            //Player1 broken tiles
            if (indexLine == 16)
            {
                playerBrokenTiles[0] = str;
            }

            //Player1 wall
            if (indexLine == 17)
            {
                playerWalls[0] = str;
            }

            // Player2 1st Line
            if (indexLine == 18)
            {
                playerLines[1][0] = str;
            }

            // Player2 2nd Line
            if (indexLine == 19)
            {
                playerLines[1][1] = str;
            }

            // Player2 3rd Line
            if (indexLine == 20)
            {
                playerLines[1][2] = str;
            }

            // Player2 4th Line
            if (indexLine == 21)
            {
                playerLines[1][3] = str;
            }

            // Player2 5th Line
            if (indexLine == 22)
            {
                playerLines[1][4] = str;
            }

            //Player2 broken tiles
            if (indexLine == 23)
            {
                playerBrokenTiles[1] = str;
            }

            //Player2 wall
            if (indexLine == 24)
            {
                playerWalls[1] = str;
            }

            //Lid
            // if (indexLine == 26)
            // {
            //     lid = str;
            // }

            if (indexLine == 25)
            {
                tileBag = str;
            }

            //Track the next line and next data to save
            indexLine++;
        }

        //check if valid file
        //At the moment, IsAValidGame set to false, when fails trying to cast numbers (like randomSeed and player points)
        if (isAValidGame)
        {
            //Load data in correspond objects
            std::cout << "\nAzul game succesfully loaded\n"
                      << std::endl;

            //For Testing just print all data
            // printLoadedGameData();
            gameLoadedCorrecty = true;
            //Start the loaded game
            startTheLoadedGame();
        }
        else
        {
            //Print feedback for invalid game to load
            std::cout << "File have an invalid format" << std::endl;
        }
    }
    else
    {
        std::cout << "File does not exist" << std::endl;
    }
}

void LoadGame::printLoadedGameData()
{

    std::cout << std::endl;

    //Print RandomSeed
    std::cout << "Random seed: " << ramdomSeed << std::endl;

    //Print if is player 1 turn
    if (player1Turn)
    {
        std::cout << "Player 1 turn: true" << std::endl;
    }
    else
    {
        std::cout << "Player 1 turn: false" << std::endl;
    }

    //Print Player Names And Score
    for (size_t i = 0; i < sizeof(playerNames) / sizeof(playerNames[0]); i++)
    {

        std::cout << "Player" << i + 1 << " name: " << playerNames[i] << std::endl;
        std::cout << "Player" << i + 1 << " score: " << playerScores[i] << std::endl;
    }

    //CentreFactory
    std::cout << "Centre Factory: " << centreFactory << std::endl;

    //Factories
    for (size_t i = 0; i < sizeof(factoriesStringData) / sizeof(factoriesStringData[0]); i++)
    {
        std::cout << "Factory " << i + 1 << ": " << factoriesStringData[i] << std::endl;
    }

    //Print player lines, broken tiles and mosaic
    for (size_t i = 0; i < sizeof(playerLines) / sizeof(playerLines[0]); i++)
    {
        //Loop every line in playersLines to save the lines of each player
        for (size_t j = 0; j < sizeof(playerLines[0]) / sizeof(playerLines[0][0]); j++)
        {
            //Save lines/storage
            std::cout << "Player" << i + 1 << " Line " << j + 1 << ": " << playerLines[i][j] << std::endl;
        }

        //Lines storage of player are saved, now will save broken tiles
        std::cout << "Player" << i + 1 << " Broken tiles: " << playerBrokenTiles[i] << std::endl;

        //save mosaic wall
        std::cout << "Player" << i + 1 << " Wall: " << playerWalls[i] << std::endl;
    }

    //Print Lid
    std::cout << "Lid: " << lid << std::endl;

    //Print Tile Bag
    std::cout << "TileBag: " << tileBag << std::endl;

    std::cout << std::endl;
}

GameBoard *LoadGame::startTheLoadedGame()
{

    //Create a new gameBoard with all strings data loaded
    loadedGameBoard = new GameBoard(ramdomSeed, player1Turn, playerNames, playerScores, playerLines,
                                    playerBrokenTiles, playerWalls, centreFactory, factoriesStringData, tileBag, lid);

    return loadedGameBoard;
}

bool LoadGame::gameLoadCorrectly()
{

    return gameLoadedCorrecty;
}