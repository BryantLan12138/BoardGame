#ifndef NODE_H
#define NODE_H

#include "Tile.h"
class Node
{
public:
    Node(Tile *tile, Node *next, Node *prev);
    Node(Node &other);

    Tile *tile;
    Node *next;
    Node *prev;
};

#endif // NODE_H
