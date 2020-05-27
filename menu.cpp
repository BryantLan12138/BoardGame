#include <iostream>
#include <exception>
#include <sstream>
#include <vector>

#include "GameBoard.h"
#include "SaveGame.h"

#include "LoadGame.h"

#define NEW_GAME 1
#define LOAD_GAME 2
#define CREDITS 3
#define QUIT 4

//Command class to handle user commands
class Commands
{
public:
    std::string fileName;
    std::string commandType;
};

void printMenu();
void gameLoop(GameBoard *gameBoard, bool playerStart);
void printCredits();
void menuSelection(int userInput, int seed);
void playNewGame(int seed);
void processCommands(int position, char **input, Commands *commands);

void loadGame();

void LoadNewGame();

int main(int argc, char **argv)
{
    int userInput = 0;
    if (argc == 3)
    {
        int seed = atoi(argv[2]);
        //Menu will display until the user chooser to Quit or hit EOF
        while (userInput != QUIT && !std::cin.eof())
        {
            printMenu();
            std::cout << "> ";
            std::cin >> userInput;

            //Check if input is valid and within range
            if (std::cin.good() && (userInput > 0 && userInput < 5))
            {
                menuSelection(userInput, seed);
            }
            //Print out an appropriate error message (NOTE: EOF will be not considered as an error)
            else if (!std::cin.eof())
            {
                std::cout << "Please select an Integer from 1 to 4" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
        }
    }
    else
    {
        std::cout << "Invalid command. Please enter mode and seed number." << std::endl;
    }

    std::cout << "GoodBye!" << std::endl;
    return EXIT_SUCCESS;
}

void printMenu()
{
    std::cout << std::endl;
    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "-------------------" << std::endl;

    std::cout << std::endl;
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;

    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << std::endl;
}

void printCredits()
{
    std::string credits[3][3] =
        {
            {"Isuru Wijesinghe", "s3719421", "s3719421@student.rmit.edu.au"},
            {"Tu Lan", "s3652591", "s3652591@student.rmit.edu.au"},
            {"Ghaida Faleh M Alharbi", "s3756970", "s3756970@student.rmit.edu.au"}};

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "--------------------------------" << std::endl;
        std::cout << std::endl;

        std::cout << "Name: " << credits[i][0] << std::endl;
        std::cout << "Student ID: " << credits[i][1] << std::endl;
        std::cout << "Email: " << credits[i][2] << std::endl;

        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
}

void playNewGame(int seed)
{
    SaveGame *saveGame = new SaveGame();

    std::cout << "Starting a new Game" << std::endl;
    std::cout << std::endl;

    //Create a new game board
    GameBoard *gameBoard = new GameBoard(seed);
    gameBoard->getCenter()->addFMarker();

    std::string playerName1 = "";
    std::string playerName2 = "";
    std::cout << "Enter a name for player 1" << std::endl;
    std::cout << "> ";
    std::cin >> playerName1;
    std::cout << std::endl;
    std::cout << "Enter a name for player 2" << std::endl;
    std::cout << "> ";
    std::cin >> playerName2;

    //Create both players
    gameBoard->createPlayer(playerName1, playerName2);
    //Fill all the factories
    gameBoard->fillFactories();

    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;
    std::cout << "=== Start Round ===" << std::endl;

    bool playerTurn = 0;
    while (!(std::cin.eof()))
    {
        gameBoard->getPlayer(playerTurn)->setTurn(false);
        gameBoard->getPlayer(!playerTurn)->setTurn(true);
        std::cout << "TURN FOR PLAYER: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;
        std::cout << std::endl;

        //Print all 5 factories
        gameBoard->printFactories();

        std::cout << std::endl;
        std::cout << "Mosaic for player: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;

        //Print the mosaic for player
        gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
        gameBoard->getPlayer(playerTurn)->getMosaic()->checkBroken();

        int factory = 0;
        char colour = {};
        int mosaicRow = 0;
        std::string input;
        std::cout << "> turn ";
        std::cin >> factory >> colour >> mosaicRow;
        //Take user input to pick Tiles
        gameBoard->pickTileFromFactory(factory, colour, mosaicRow, playerTurn);

        std::cout << std::endl;
        std::cout << "You succesfully placed your Tile/Tiles in your Mosaic!" << std::endl;
        //Print each player's Mosaic after a Player has picked tiles
        gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
        gameBoard->getPlayer(playerTurn)->getMosaic()->checkBroken();

        //End game
        if (gameBoard->endGame(gameBoard->getPlayer(playerTurn)->getMosaic()) || gameBoard->endGame(gameBoard->getPlayer(!playerTurn)->getMosaic()))
        {
            int score1 = gameBoard->getPlayer(playerTurn)->getMosaic()->getFinalScore(playerTurn);
            int score2 = gameBoard->getPlayer(!playerTurn)->getMosaic()->getFinalScore(!playerTurn);
            gameBoard->getPlayer(playerTurn)->setPlayerPoints(score1);
            gameBoard->getPlayer(!playerTurn)->setPlayerPoints(score2);
            std::cout << std::endl
                      << "=== END GAME ===" << std::endl;
            std::cout << "The final score for PLAYER " << gameBoard->getPlayer(playerTurn)->getPlayerName() << " : "
                      << score1 << std::endl;
            std::cout << "The final score for PLAYER " << gameBoard->getPlayer(!playerTurn)->getPlayerName() << " : "
                      << score2 << std::endl;

            if (score1 > score2)
            {
                std::cout << gameBoard->getPlayer(playerTurn)->getPlayerName() << " wins! " << std::endl;
            }
            else if (score2 > score1)
            {
                std::cout << gameBoard->getPlayer(!playerTurn)->getPlayerName() << " wins! " << std::endl;
            }
            else
            {
                std::cout << "The game is draw. " << std::endl;
            }
            break;
        }

        //End round
        if (gameBoard->endRound())
        {
            // int roundScore1 = gameBoard->getPlayer(playerTurn)->getMosaic()->getRoundScore(playerTurn);
            // int roundScore2 = gameBoard->getPlayer(!playerTurn)->getMosaic()->getRoundScore(!playerTurn);
            std::cout << std::endl
                      << "=== END ROUND ===" << std::endl;
            std::cout << "FOR PLAYER: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl
                      << std::endl;
            gameBoard->getPlayer(playerTurn)->getMosaic()->wallTiling();
            gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
            std::cout << "The round score: " << gameBoard->getPlayer(playerTurn)->getMosaic()->getRoundScore(playerTurn) << std::endl;
            std::cout << std::endl;

            std::cout << "FOR PLAYER: " << gameBoard->getPlayer(!playerTurn)->getPlayerName() << std::endl
                      << std::endl;
            gameBoard->getPlayer(!playerTurn)->getMosaic()->wallTiling();
            gameBoard->getPlayer(!playerTurn)->getMosaic()->printMosaic();
            std::cout << "The round score: " << gameBoard->getPlayer(!playerTurn)->getMosaic()->getRoundScore(!playerTurn) << std::endl;

            //Set points for each player
            gameBoard->getPlayer(playerTurn)->setPlayerPoints(gameBoard->getPlayer(playerTurn)->getMosaic()->getRoundScore(playerTurn));
            gameBoard->getPlayer(!playerTurn)->setPlayerPoints(gameBoard->getPlayer(!playerTurn)->getMosaic()->getRoundScore(!playerTurn));

            //Refil factories after each round
            gameBoard->fillFactories();
            gameBoard->getCenter()->addFMarker();
        }

        //Change player turn
        playerTurn = !playerTurn;

        //Save game after each player's turn
        saveGame->SaveGameState(gameBoard);
    }

    delete saveGame;
    delete gameBoard;
}

void processCommands(int position, char **input, Commands *commands)
{
}

void menuSelection(int userInput, int seed)
{
    if (userInput == CREDITS)
    {
        printCredits();
    }
    else if (userInput == NEW_GAME)
    {
        playNewGame(seed);
    }
    else if (userInput == LOAD_GAME)
    {
        LoadGame *loadGameInstance = new LoadGame();
        //Continue the game

        if (loadGameInstance->gameLoadCorrectly())
        {
            GameBoard *gameBoard = loadGameInstance->startTheLoadedGame();

            gameLoop(gameBoard, gameBoard->getPlayer(0)->getTurn());
        }
    }
}
void gameLoop(GameBoard *gameBoard, bool playerStart)
{

    //Create instance of save
    SaveGame* saveGameInstace = new SaveGame();

    bool playerTurn = !playerStart;
    while (!(std::cin.eof()))
    {
        gameBoard->getPlayer(playerTurn)->setTurn(false);
        gameBoard->getPlayer(!playerTurn)->setTurn(true);
        std::cout << "TURN FOR PLAYER: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;
        std::cout << std::endl;

        //Print all 5 factories
        gameBoard->printFactories();

        std::cout << std::endl;
        std::cout << "Mosaic for player: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;

        //Print the mosaic for player
        gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
        gameBoard->getPlayer(playerTurn)->getMosaic()->checkBroken();

        int factory = 0;
        char colour = {};
        int mosaicRow = 0;
        std::string input;
        std::cout << "> turn ";
        std::cin >> factory >> colour >> mosaicRow;
        //Take user input to pick Tiles
        gameBoard->pickTileFromFactory(factory, colour, mosaicRow, playerTurn);

        std::cout << std::endl;
        std::cout << "You succesfully placed your Tile/Tiles in your Mosaic!" << std::endl;
        //Print each player's Mosaic after a Player has picked tiles
        gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
        gameBoard->getPlayer(playerTurn)->getMosaic()->checkBroken();

        playerTurn = !playerTurn;
    }
    saveGameInstace->SaveGameState(gameBoard);
    delete saveGameInstace;
}