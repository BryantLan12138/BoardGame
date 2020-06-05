#include "Mosaic.h"
#include "Factory.h"

Mosaic::Mosaic()
{
    //Initialise score for each player
    leftPart = new char *[MOSAIC_LENGTH];
    for (int i = 0; i < MOSAIC_LENGTH; i++)
    {
        leftPart[i] = new char[MOSAIC_LENGTH + 1];
    }

    rightPart = new char *[MOSAIC_LENGTH];
    for (int i = 0; i < MOSAIC_LENGTH; i++)
    {
        rightPart[i] = new char[MOSAIC_LENGTH + 1];
    }

    for (int i = FIRST; i < MOSAIC_LENGTH + 1; i++)
    {
        for (int k = 0; k < i; k++)
        {
            leftPart[i - 1][k] = '.';
        }
        for (int l = 0; l < MOSAIC_LENGTH; l++)
        {
            rightPart[i - 1][l] = '.';
        }
    }
    brokenTiles = new char[BROKEN_LENGTH];
    for (int i = 0; i < BROKEN_LENGTH; i++)
    {
        brokenTiles[i] = '0';
    }

    for (int i = 0; i < 2; ++i)
    {
        score[i] = new Score();
    }

    boxlid = new BoxLid();
    head = NULL;
}
Mosaic::Mosaic(std::string dataOfBrokenTilesToLoad, std::string dataOfWallToLoad, std::string dataOfLinesToLoad[5])
{
    //Initialise score for each player
    leftPart = new char *[MOSAIC_LENGTH];
    for (int i = 0; i < MOSAIC_LENGTH; i++)
    {
        leftPart[i] = new char[MOSAIC_LENGTH + 1];
    }

    rightPart = new char *[MOSAIC_LENGTH];
    for (int i = 0; i < MOSAIC_LENGTH; i++)
    {
        rightPart[i] = new char[MOSAIC_LENGTH + 1];
    }

    for (int i = FIRST; i < MOSAIC_LENGTH + 1; i++)
    {
        for (int k = 0; k < i; k++)
        {
            leftPart[i - 1][k] = '.';
        }
        for (int l = 0; l < MOSAIC_LENGTH; l++)
        {
            rightPart[i - 1][l] = '.';
        }
    }
    brokenTiles = new char[BROKEN_LENGTH];
    for (int i = 0; i < BROKEN_LENGTH; i++)
    {
        brokenTiles[i] = '0';
    }

    //Load left part
    for (int row = 0; row < MOSAIC_LENGTH; row++)
    {
        for (int i = 0; i < MOSAIC_LENGTH; i++)
        {
            leftPart[row][i] = dataOfLinesToLoad[row][i];
        }
    }

    //Load Wall
    int wallDataIndex = 0;
    for (int row = 0; row < MOSAIC_LENGTH; row++)
    {
        for (int j = 0; j < MOSAIC_LENGTH; j++)
        {
            if (isupper(dataOfWallToLoad[wallDataIndex]))
            {
                rightPart[row][j] = dataOfWallToLoad[wallDataIndex];
            }
            else
            {
                rightPart[row][j] = '.';
            }

            wallDataIndex++;
        }
    }
    for (int i = 0; i< 7;i++){
        //Load brokenTiles
        for (char c : dataOfWallToLoad)
        {
            if (c){
                brokenTiles[i] = c;
            }
            
        }
    }
   
}
Mosaic::~Mosaic()
{
    delete boxlid;
    for (int i = 0; i < 2; ++i)
    {
        delete score[i];
    }
    delete leftPart;
    delete rightPart;
    delete brokenTiles;
}

void Mosaic::printMosaic(bool extension)
{
    this->extension = extension;
    if (extension){
        mosaic_length = 6;
    }else{
        mosaic_length = 5;
    }
    for (int i = FIRST; i < mosaic_length + 1; i++)
    {
        std::cout << i << ": ";
        for (int j = mosaic_length; j > i; j--)
        {
            std::cout << "  ";
        }
        for (int k = 0; k < i; k++)
        {
            printColour(leftPart[i - 1][k]);
        }
        std::cout << " ||";
        for (int l = 0; l < mosaic_length; l++)
        {
            printColour(rightPart[i - 1][l]);
        }
        std::cout << std::endl;
    }
}

void Mosaic::printColour(char colour){
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
    if (colour == 'O'){
        std::cout << "\033[1;39m" << colour << "\033[0m" << ' ';
    }
    if (colour == '.'){
        std::cout << '.' << ' ';
    }
}
void Mosaic::addBroken(Colour colour)
{
    Tile *newTile = new Tile(colour);
    for (int i = 0; i < BROKEN_LENGTH; i++)
    {
        if (i > 7)
        {
            // put access broken tiles to boxlid
            boxlid->addFront(&head, newTile);
        }
        if (brokenTiles[i] == '0')
        {
            brokenTiles[i] = newTile->getColourAsChar();
            return;
        }
        else
        {
            continue;
        }
    }
}
void Mosaic::checkBroken()
{
    std::cout << "Broken: ";
    for (int i = 0; i < BROKEN_LENGTH; i++)
    {
        if (brokenTiles[i] != '0')
        {
            printColour(brokenTiles[i]);
        }
    }
    std::cout << std::endl;
}

void Mosaic::addTiles(Tile *tile, int row, bool firstPlayer)
{
    // add tiles to mosaic
    Tile *newTile = new Tile(tile->getColour());

    char colour = newTile->getColourAsChar();
    for (int i = row; i >= 0; i--)
    {
        for (int j = 0; j < mosaic_length; j++)
        {
            if (colour == rightPart[row - 1][j]){
                std::cout << "You put the tiles existing in right part of mosaic, incorrect action." << std::endl;
                return;
            }
        }
        if (firstPlayer)
        {
            addBroken(FIRST_MARKER);
            firstPlayer = false;
        }
        if (leftPart[row - 1][i - 1] != colour && leftPart[row - 1][i - 1] != '.')
        {
            std::cout << "You put wrong tiles in this row" << std::endl;
            addBroken(tile->getColour());
            return;
        }
        else
        {
            if (leftPart[row - 1][i - 1] == colour)
            {
                continue;
            }
            else
            {
                leftPart[row - 1][i - 1] = colour;
                return;
            }
        }
    }
}

void Mosaic::wallTiling()
{
    Tile *newTile;
    // each row will be checked see if it is filled
    bool complete[mosaic_length];
    for (int i = 0; i < mosaic_length; i++){
        complete[i] = true;
    }
    for (int row = 1; row < mosaic_length + 1; row++)
    {
        for (int i = 0; i < row; i++)
        {
            // if not filled yet, return false
            if (leftPart[row - 1][i] == '.')
            {
                complete[row - 1] = false;
            }
        }
    }
    if (!extension){
        for (int row = 0; row < mosaic_length; row++)
        {
            if (complete[row])
            {
                char tmp = leftPart[row][0];
                // char tmp = left_part[row][0];
                newTile = new Tile(getColour(tmp));
                for (int i = 0; i < mosaic_length; i++)
                {
                    if (final_tiles[row][i] == tmp)
                    {
                        rightPart[row][i] = tmp;
                        // right_part[row][i] = tmp;
                    }
                }
                // to remove the tiles on left part of mosaic
                for (int i = 0; i < row + 1; i++)
                {
                    leftPart[row][i] = '.';
                    // left_part[row][i] = '.';
                }

                // others go to boxlid
                for (int i = 0; i < row; i++)
                {
                    boxlid->addFront(&head, newTile);
                }
            }
        }
    }else{
        int row = 0;
        while(row < mosaic_length){
            int newCol=0;
            bool success=true;
            if (complete[row])
            {
                printMosaic(extension);
                std::cout << "Row " << row+1 << " is completed." << std::endl;
                std::cout << "Which mosaic col you want to put? Input ONE integer indicating col, e.g.: 2 " << std::endl << "> ";
                std::cin >> newCol;
                if (std::cin.good()){
                    char tmp = leftPart[row][0];
                    newTile = new Tile(getColour(tmp));
                    for (int i = 0; i < mosaic_length && success; i++){
                        if (rightPart[i][newCol-1] == tmp){
                            std::cout << "Already existing the same colour tile on the same column, please re-enter the col you want to put." << std::endl;
                            success = false;
                        }
                    }
                    if (rightPart[row][newCol-1] != '.'){
                        std::cout<<"Already existing tile, please re-enter the col you want to put." << std::endl;
                        success = false;
                    }
                    if (success){
                        rightPart[row][newCol - 1] = tmp;

                        // wall tiling let them become empty
                        for (int i = 0; i < row + 1; i++)
                        {
                            leftPart[row][i] = '.';
                        }
                        // others go to boxlid
                        for (int i = 0; i < row; i++)
                        {
                            boxlid->addFront(&head, newTile);
                        }
                        row++;
                    }
                }
                else{
                    std::cout << "Invalid input, please enter again." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            }else{
                row++;
            }
        }
    }
}

Colour Mosaic::getColour(char colour)
{
    Colour returnVal = {};
    if (colour == 'F')
    {
        returnVal = FIRST_MARKER;
    }
    else if (colour == 'R')
    {
        returnVal = RED;
    }
    else if (colour == 'Y')
    {
        returnVal = YELLOW;
    }
    else if (colour == 'B')
    {
        returnVal = DARK_BLUE;
    }
    else if (colour == 'L')
    {
        returnVal = LIGHT_BLUE;
    }
    else if (colour == 'U')
    {
        returnVal = BLACK;
    }
    return returnVal;
}

int Mosaic::getRoundScore(int playerTurn)
{
    score[playerTurn]->scoreTile(rightPart, extension);
    score[playerTurn]->brokenScore(brokenTiles);
    // restart
    for (int i = 0; i < BROKEN_LENGTH; i++)
    {
        brokenTiles[i] = '0';
    }
    return score[playerTurn]->getRoundScore();
}

int Mosaic::getTotalScore(int playerTurn){
    return score[playerTurn]->getFinalScore();
}

int Mosaic::getFinalScore(int playerTurn)
{
    score[playerTurn]->rowBonus(rightPart);
    score[playerTurn]->colBonus(rightPart);
    score[playerTurn]->colorBonus(rightPart);
    return score[playerTurn]->getFinalScore();
}

char **Mosaic::getLeftPart()
{
    return leftPart;
}

char **Mosaic::getRightPart()
{
    return rightPart;
}

char *Mosaic::getBroken()
{
    return brokenTiles;
}

bool Mosaic::checkEndGame()
{
    bool complete[mosaic_length];
    for (int i = 0; i < mosaic_length; i++)
    {
        complete[i] = true;
    }
    for (int i = 0; i < mosaic_length; i++)
    {
        for (int j = 0; j < mosaic_length; j++)
        {
            if (rightPart[i][j] == '.')
            {
                // if (right_part[i][j] == '.'){
                complete[i] = false;
            }
        }
    }
   
    for (int i = 0; i < mosaic_length; i++)
    {
        if (complete[i])
        {
            return true;
        }
    }
    return false;
}