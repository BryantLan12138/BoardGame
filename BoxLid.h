#ifndef BOXLID_H
#define BOXLID_H

#include "Node.h"
#include "Tile.h"

class LinkedList
{
public:
    Node *head;
    Node *tail;
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
    void addFront(Tile *tile);

    //Add tiles to the bakck
    void addBack(Tile *tile);

    //Delete tiles from front
    void deleteFront();

    //Delete tiles from back
    void deleteBack();

private:
    LinkedList *boxLid;
    int length;
};

#endif