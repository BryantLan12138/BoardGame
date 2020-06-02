#ifndef BOXLID_H
#define BOXLID_H

#include "Tile.h"

// A doubly linked list node
struct Node
{
    Tile *tile;
    struct Node *next;
    struct Node *prev;
};

class BoxLid
{
public:
    BoxLid();
    ~BoxLid();

    //Get size
    int size();

    //Empty the list
    void clear();

    //Get a pointer to a tile
    Tile *getTile(int i);

    //Add tiles to the front
    void addFront(struct Node **head, Tile *newTile);

    //Add tiles after the specific node
    void addAfter(struct Node *prev_node, Tile *newTile);

    //Add tiles to the back
    void addBack(struct Node **head, Tile *newTile);

    //Delete tiles from front
    void deleteFront();

    //Delete tiles from back
    void deleteBack();

private:
    struct Node *boxLidHead;
    int length;
};

#endif