#include "Tile.h"

Tile::Tile(Colour colour)
{
    this->colour = colour;
    x = 0;
    y = 0;
}

Tile::Tile(Tile &other)
{
    this->colour = other.colour;
}

Tile::~Tile() {}

Colour Tile::getColour()
{
    return colour;
}

char Tile::getColourAsChar()
{
    char returnVal = {};
    if (colour == 0)
    {
        returnVal = 'F';
    }
    else if (colour == 1)
    {
        returnVal = 'R';
    }
    else if (colour == 2)
    {
        returnVal = 'Y';
    }
    else if (colour == 3)
    {
        returnVal = 'B';
    }
    else if (colour == 4)
    {
        returnVal = 'L';
    }
    else if (colour == 5)
    {
        returnVal = 'U';
    }
    return returnVal;
}

void Tile::setColourAsChar(char colour)
{
    this->colourAsChar = colour;
}

void Tile::setX(int x)
{
    this->x = x;
}

int Tile::getX()
{
    return x;
}

void Tile::setY(int y)
{
    this->y = y;
}

int Tile::getY()
{
    return y;
}