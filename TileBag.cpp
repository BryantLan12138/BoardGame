#include "TileBag.h"
#include <algorithm>
#include <random>

TileBag::TileBag(int seed) : tileBag()
{
    this->addTiles(seed);
}

TileBag::TileBag(TileBag &other) : tileBag(other.tileBag)
{
}
TileBag::TileBag(std::string loadData)
{
    //Loop through dataOfTiles to get each character in string
    for (char &c : loadData)
    {
        if (c == 'R')
        {
            Tile *red = new Tile(RED);
            tileBag.push_back(red);
        }
        else if (c == 'Y')
        {
            Tile *yellow = new Tile(YELLOW);
            tileBag.push_back(yellow);
        }
        else if (c == 'B')
        {
            Tile *darkBlue = new Tile(DARK_BLUE);
            tileBag.push_back(darkBlue);
        }
        else if (c == 'L')
        {
            Tile *lightBlue = new Tile(LIGHT_BLUE);
            tileBag.push_back(lightBlue);
        }
        else if (c == 'U')
        {
            Tile *black = new Tile(BLACK);
            tileBag.push_back(black);
        }
    }
}
TileBag::~TileBag()
{
    clear();
}

int TileBag::size()
{
    return tileBag.size();
}

void TileBag::clear()
{
    tileBag.clear();
}

Tile *TileBag::get(int i)
{
    Tile *tile = nullptr;
    if (i >= 0 && i < size())
    {
        tile = tileBag[i];
    }
    //return tile at the given index
    return tile;
}

//Adding to the back
void TileBag::addTiles(int seed)
{
    // Create 20 of each tile and place it in the bag
    for (int i = 0; i < 20; ++i)
    {
        Tile *red = new Tile(RED);
        Tile *yellow = new Tile(YELLOW);
        Tile *darkBlue = new Tile(DARK_BLUE);
        Tile *lightBlue = new Tile(LIGHT_BLUE);
        Tile *black = new Tile(BLACK);
        tileBag.push_back(red);
        tileBag.push_back(yellow);
        tileBag.push_back(darkBlue);
        tileBag.push_back(lightBlue);
        tileBag.push_back(black);
        
    }
    //random version
    std::shuffle(tileBag.begin(), tileBag.end(), std::default_random_engine(seed));
}

//Delete tile at certain index
void TileBag::deleteTile(int index)
{
    if (tileBag.size() > 0 &&
        index >= 0 && index < size())
    {
        for (int i = index; i < size() - 1; ++i)
        {
            tileBag[i] = tileBag[i + 1];
        }

        tileBag.pop_back();
    }
}