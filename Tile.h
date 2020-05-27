#ifndef TILE_H
#define TILE_H

#include <string>
enum Colour
{
    FIRST_MARKER,
    RED,
    YELLOW,
    DARK_BLUE,
    LIGHT_BLUE,
    BLACK
};

/**
 * Represents a single Tile in Azul.
 */
class Tile
{
public:
    Tile(Colour colour);
    Tile(Tile &other);
    ~Tile();

    //Return the Tile colour
    Colour getColour();

    //Return the colour of the tile as a Char
    char getColourAsChar();

    //
    void setColourAsChar(char colour);

    //Set x-coordinate of the tile
    void setX(int x);

    //Return x-coordinate of the tile
    int getX();

    //Set y-coordinate of the tile
    void setY(int y);

    //Return y-coordinate of the tile
    int getY();

private:
    Colour colour;
    char colourAsChar;
    int x;
    int y;
};

#endif // TILE_H
