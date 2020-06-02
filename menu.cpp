#include <iostream>
#include <exception>
#include <sstream>
#include <vector>

#include "GameBoard.h"
#include "SaveGame.h"
#include "LoadGame.h"

void printMenu();
void gameLoop(GameBoard *gameBoard, bool playerTurn, bool greyBoardMode, bool extension);
void printCredits();
void printMosaic(GameBoard *gameBoard, int playerTurn);
bool endGame(GameBoard *gameBoard, int playerTurn);
void endRound(GameBoard *gameBoard, int playerTurn);
void menuSelection(int userInput, int seed);
void playNewGame(int seed);
void helpCenter();
void loadGame();
void LoadNewGame();

int main(int argc, char **argv)
{
    std::string userInput;
    if (argc == 3)
    {
        int seed = atoi(argv[2]);
        //Menu will display until the user chooser to Quit or hit EOF
        while (userInput != "4" && !std::cin.eof())
        {
            printMenu();
            std::cout << "> ";
            std::cin >> userInput;

            //Check if input is valid and within range
            if (std::cin.good() && (userInput == "1" || userInput == "2" || userInput == "3"))
            {
                menuSelection(std::stoi(userInput), seed);
            }
            else if (std::cin.good() && (userInput == "help")){
                helpCenter();
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

void helpCenter(){
    int choice;
    std::cout << std::endl;
    while (std::cin.good() && choice != 6){
        std::cout << "Which part you want to get help with? Please enter the following number. " << std::endl;
        std::cout << "1. Azul history" << std::endl
                  << "2. How to play a new game" << std::endl
                  << "3. How to load a new game" << std::endl
                  << "4. How to get the credit for the game" << std::endl
                  << "5. How to quit the game" << std::endl
                  << "6. I want to go back to the menu." << std::endl << "> ";
        std::cin >> choice;
        if (choice == 1){
            std::cout << std::endl << "Azul history: " << std::endl
                      << "Introduced by the Moors, azulejos (originally white and blue ceramic tiles) were fully embraced by the Portuguese, when their king Manuel I,"
                      << "on a visit to the Alhambra palace in Southern Spain, was mesmerized by the stunning beauty of the Moorish decorative tiles. "
                      << "The king, awestruck by the interior beauty of the Alhambra, immediately ordered that his own palace in Portugal be decorated with similar wall tiles."
                      << "Azul brings you, a tile laying artist, to embellish the walls of the Royal Palace of Evora."<< std::endl
                      << "referenced by https://www.ultraboardgames.com/azul/game-rules.php" << std::endl<< std::endl;
        }
        else if (choice == 2){
            std::cout << std::endl << "Enter 1 for new game." << std::endl
                      << "Where there is a command you need to enter: Turn x X x" << std::endl
                      << "For example \"Turn 4 B 2\", meaning Take all the blue tiles on the fourth factories and put them into second mosaic row." << std::endl
                      << "Please be careful while you entering, as this will take your tiles to broken tiles, which may deduct your final score." << std::endl << std::endl;
        }
        else if (choice == 3){
            std::cout << std::endl << "Enter 2 for loading a existing game." << std::endl
                      << "Where there is a file name you need to enter without suffix: filename" << std::endl
                      << "For example \"GameToLoad\"" << std::endl
                      << "Make sure the file is existed and in the same directory."<< std::endl << std::endl;
        } else if (choice == 4){
            std::cout << std::endl << "Simply enter 3 in the main menu" << std::endl << std::endl;
        }else if (choice == 5){
            std::cout << std::endl << "Ctrl+C will take you out of the game." << std::endl << std::endl;
        }else{
            std::cout << std::endl << "Sorry I'm not sure what you are asking, please type again." << std::endl << std::endl;
        }  
    }
    std::cout << std::endl << "Feel free to come back for more help information. Bye for now!" << std::endl << std::endl;
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
    std::cout << "Or enter \"help\" for more information." << std::endl;
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
void printMosaic(GameBoard *gameBoard, int playerTurn){
    //Print the mosaic for player
    gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
    gameBoard->getPlayer(playerTurn)->getMosaic()->checkBroken();
}

bool endGame(GameBoard *gameBoard, int playerTurn){   
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

        if (score1 > score2){
            std::cout << gameBoard->getPlayer(playerTurn)->getPlayerName() << " wins! " << std::endl;
        }
        else if (score2 > score1){
            std::cout << gameBoard->getPlayer(!playerTurn)->getPlayerName() << " wins! " << std::endl;
        }
        else{
            std::cout << "The game is draw. " << std::endl;
        }
        return true;
    }
    return false;
}
void endRound(GameBoard *gameBoard, int playerTurn){
    if (gameBoard->endRound())
    {
        std::cout << std::endl
                  << "=== END ROUND ===" << std::endl;
        std::cout << "FOR PLAYER: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl
                  << std::endl;
        gameBoard->getPlayer(playerTurn)->getMosaic()->wallTiling();
        gameBoard->getPlayer(playerTurn)->getMosaic()->printMosaic();
        std::cout << "The round score: " << gameBoard->getPlayer(playerTurn)->getMosaic()->getRoundScore(playerTurn) << std::endl;
        std::cout << "The total score: " << gameBoard->getPlayer(playerTurn)->getMosaic()->getTotalScore(playerTurn) << std::endl;
        std::cout << std::endl;

        std::cout << "FOR PLAYER: " << gameBoard->getPlayer(!playerTurn)->getPlayerName() << std::endl
                  << std::endl;
        gameBoard->getPlayer(!playerTurn)->getMosaic()->wallTiling();
        gameBoard->getPlayer(!playerTurn)->getMosaic()->printMosaic();
        std::cout << "The round score: " << gameBoard->getPlayer(!playerTurn)->getMosaic()->getRoundScore(!playerTurn) << std::endl;
        std::cout << "The total score: " << gameBoard->getPlayer(!playerTurn)->getMosaic()->getTotalScore(!playerTurn) << std::endl;
        std::cout << std::endl;

        //Set points for each player
        gameBoard->getPlayer(playerTurn)->setPlayerPoints(gameBoard->getPlayer(playerTurn)->getMosaic()->getRoundScore(playerTurn));
        gameBoard->getPlayer(!playerTurn)->setPlayerPoints(gameBoard->getPlayer(!playerTurn)->getMosaic()->getRoundScore(!playerTurn));

        //Refil factories after each round
        gameBoard->fillFactories();
        gameBoard->getCenter()->addFMarker();
    }
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
    char greyBoardMode;
    char extension;
    bool gMode, eMode, successA=false,successB=false;
    std::cout << "Enter a name for player 1" << std::endl << "> ";
    std::cin >> playerName1;
    std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
    std::cin >> playerName2;
    while (!std::cin.eof() && !(successA && successB)){
        std::cout << std::endl
                  << "Do you want to enable GreyBoard mode? (y/n)" << std::endl
                  << "> ";
        std::cin >> greyBoardMode;
        std::cout << std::endl
                  << "Do you want to enable 6x6 mode? (y/n)" << std::endl
                  << "> ";
        std::cin >> extension;
        if (std::cin.good()){
            if (tolower(greyBoardMode) == 'y')
            {
                gMode = true;
                successA = true;
            }
            if (tolower(greyBoardMode) == 'n')
            {
                gMode = false;
                successA = true;
            }
            if (tolower(extension) == 'y')
            {
                eMode = true;
                successB = true;
            }
            if (tolower(extension) == 'n')
            {
                eMode = false;
                successB = true;
            }
            else
            {
                std::cout << std::endl
                          << "INVALID INPUT, please enter 'y' or 'n'" << std::endl;
            }
        }
    }
    //Create both players
    gameBoard->createPlayer(playerName1, playerName2);
    //Fill all the factories
    gameBoard->fillFactories();

    std::cout << std::endl;
    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;
    std::cout << "=== Start Round ===" << std::endl;

    bool playerTurn = 0;
    gameLoop(gameBoard, playerTurn, greyBoardMode, extension);

    delete saveGame;
    delete gameBoard;
}

void menuSelection(int userInput, int seed)
{
    if (userInput == 3)
    {
        printCredits();
    }
    else if (userInput == 1)
    {
        playNewGame(seed);
    }
    else if (userInput == 2)
    {
        LoadGame *loadGameInstance = new LoadGame();
        //Continue the game

        if (loadGameInstance->gameLoadCorrectly())
        {
            GameBoard *gameBoard = loadGameInstance->startTheLoadedGame();

            // gameLoop(gameBoard, gameBoard->getPlayer(0)->getTurn());
        }
    }
}
void gameLoop(GameBoard *gameBoard, bool playerTurn, bool greyBoardMode, bool extension)
{

    //Create instance of save
    SaveGame* saveGameInstace = new SaveGame();

    // bool playerTurn = !playerStart;
    while (!(std::cin.eof()))
    {
        // gameBoard->getPlayer(playerTurn)->setTurn(false);
        // gameBoard->getPlayer(!playerTurn)->setTurn(true);
        std::cout << "TURN FOR PLAYER: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;
        std::cout << std::endl;

        //Print all 5 factories
        gameBoard->printFactories();

        std::cout << std::endl;
        std::cout << "Mosaic for player: " << gameBoard->getPlayer(playerTurn)->getPlayerName() << std::endl;
        printMosaic(gameBoard, playerTurn);
        int factory = -1;
        char colour = ' ';
        int mosaicRow = 0;
        std::cout << "> turn ";
        std::cin >> factory >> colour >> mosaicRow;
        //Consider all the conditions
        if (std::cin.fail())
        {
            std::cout << "Invalid input, please enter again." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else if (factory == -1 || colour == ' ' || mosaicRow == 0)
        {
            std::cout << "Lack of command, please enter again." << std::endl;
        }
        else if (factory > 5 || factory < 0)
        {
            std::cout << "Wrong factory number" << std::endl;
        }
        else if (!(colour == 'R' || colour == 'Y' || colour == 'B' || colour == 'L' || colour == 'U'))
        {
            std::cout << "Wrong colour" << std::endl;
        }
        else if (mosaicRow > 5 || mosaicRow < 1)
        {
            std::cout << "The mosaic row you want to put is wrong" << std::endl;
        }
        else
        {
            bool success = gameBoard->pickTileFromFactory(factory, colour, mosaicRow, playerTurn);
            if (success){
                std::cout << std::endl;
                std::cout << "New Mosaic:" << std::endl;
                //Print each player's Mosaic after a Player has picked tiles
                printMosaic(gameBoard, playerTurn);
                //End game
                if (endGame(gameBoard, playerTurn)){
                    return;
                };
                //End round
                endRound(gameBoard, playerTurn);
                playerTurn = !playerTurn;
            }else{
                std::cout << "Your decision is unsuccessful. Please redo in the next round." << std::endl;
                //Print each player's Mosaic after a Player has picked tiles
                printMosaic(gameBoard, playerTurn);
                std::cout << std::endl;
            }
        }

        //Change player turn
        
    }
    saveGameInstace->SaveGameState(gameBoard);
    delete saveGameInstace;
}