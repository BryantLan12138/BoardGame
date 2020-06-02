#include <iostream>

#include "BoxLid.h"

BoxLid::BoxLid()
{
    boxLidHead = NULL;
}

BoxLid::~BoxLid()
{
    clear();
    delete boxLidHead;
}


//inserts node at the front of the list
void BoxLid::addFront(struct Node **head, Tile *newTile)
{
    //allocate memory for New node
    struct Node *newNode = new Node;

    //assign data to new node
    newNode->tile = newTile;

    //new node is head and previous is null, since we are adding at the front
    newNode->next = (*head);
    newNode->prev = NULL;

    //previous of head is new node
    if ((*head) != NULL)
        (*head)->prev = newNode;

    //head points to new node
    (*head) = newNode;

    length++;
}

/* Given a node as prev_node, insert a new node after the given node */
void BoxLid::addAfter(struct Node *prev_node, Tile *newTile)
{
    //check if prev node is null
    if (prev_node == NULL)
    {
        std::cout << "Previous node is required , it cannot be NULL";
        return;
    }
    //allocate memory for new node
    struct Node *newNode = new Node;

    //assign data to new node
    newNode->tile = newTile;

    //set next of newnode to next of prev node
    newNode->next = prev_node->next;

    //set next of prev node to newnode
    prev_node->next = newNode;

    //now set prev of newnode to prev node
    newNode->prev = prev_node;

    //set prev of new node's next to newnode
    if (newNode->next != NULL)
        newNode->next->prev = newNode;

    length++;
}

//insert a new node at the end of the list
void BoxLid::addBack(struct Node **head, Tile *newTile)
{
    //allocate memory for node
    struct Node *newNode = new Node;

    struct Node *last = *head; //set last node value to head

    //set data for new node
    newNode->tile = newTile;

    //new node is the last node , so set next of new node to null
    newNode->next = NULL;

    //check if list is empty, if yes make new node the head of list
    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    //otherwise traverse the list to go to last node
    while (last->next != NULL)
        last = last->next;

    //set next of last to new node
    last->next = newNode;

    //set last to prev of new node
    newNode->prev = last;
    return;
    length++;
}


int BoxLid::size()
{
    return length;
}

void BoxLid::clear()
{
    while (boxLidHead != NULL)
    {
        deleteFront();
    }
    length = 0;
}

Tile* BoxLid::getTile(int i)
{
    int count = 0;
    struct Node *current = boxLidHead;
    Tile *returnValue = NULL;

    if (i < size())
    {
        while (count < i)
        {
            ++count;
            current = current->next;
        }
        returnValue = current->tile;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }

    return returnValue;
}


void BoxLid::deleteFront()
{
    if (boxLidHead != NULL)
    {
        Node *newHead = boxLidHead->next;
        delete boxLidHead;
        boxLidHead = newHead;

        if (boxLidHead == NULL)
        {
            boxLidHead->next = NULL;
        }
        else
        {
            newHead->prev = NULL;
        }

        --length;
    }
    else
    {
        throw std::logic_error("Deleting on empty list");
    }
}