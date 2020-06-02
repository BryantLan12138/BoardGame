#ifndef TILEBAG_H
#define TILEBAG_H
#include <vector>

#include "Tile.h"

class TileBag
{
public:
    TileBag(int seed);
    TileBag(TileBag &other);
    TileBag(std::string loadData);

    ~TileBag();

    int size();
    void clear();
    Tile *get(int i);

    // void addFront(Tile *tile);
    void addTiles(int seed);

    // void deleteFront();
    // void deleteBack();

    void deleteTile(int index);

private:
    std::vector<Tile *> tileBag;
};

#endif