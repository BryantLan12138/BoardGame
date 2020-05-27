#include <iostream>

#include "BoxLid.h"

BoxLid::BoxLid()
{
    boxLid = new LinkedList();
    boxLid->head = nullptr;
    boxLid->tail = nullptr;
    length = 0;
}

BoxLid::~BoxLid()
{
    clear();
    delete boxLid;
}

int BoxLid::size()
{
    return length;
}

void BoxLid::clear()
{
    while (boxLid->head != nullptr)
    {
        deleteFront();
        boxLid->head = nullptr;
        boxLid->tail = nullptr;
        length = 0;
    }
}

Tile *BoxLid::getTile(int i)
{
    int count = 0;
    Node *current = boxLid->head;
    Tile *returnValue = nullptr;

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

void BoxLid::addFront(Tile *tile)
{
    Node *toAdd = new Node(tile, nullptr, nullptr);
    Node *current = boxLid->head;

    if (boxLid->head == nullptr)
    {
        boxLid->head = toAdd;
        boxLid->tail = toAdd;
    }
    else
    {
        toAdd->next = boxLid->head;
        current->prev = toAdd;
        boxLid->head = toAdd;
    }
    ++length;
}

void BoxLid::addBack(Tile *tile)
{
    Node *toAdd = new Node(tile, nullptr, nullptr);
    if (boxLid->head == nullptr)
    {
        boxLid->head = toAdd;
        boxLid->tail = toAdd;
    }
    else
    {
        boxLid->tail->next = toAdd;
        toAdd->prev = boxLid->tail;
        boxLid->tail = toAdd;
    }
    ++length;
}

void BoxLid::deleteFront()
{
    if (boxLid->head != nullptr)
    {
        Node *newHead = boxLid->head->next;
        delete boxLid->head;
        boxLid->head = newHead;

        if (boxLid->head == nullptr)
        {
            boxLid->tail = nullptr;
        }
        else
        {
            newHead->prev = nullptr;
        }

        --length;
    }
    else
    {
        throw std::logic_error("Deleting on empty list");
    }
}

void BoxLid::deleteBack()
{
    if (boxLid->head != nullptr)
    {
        Node *newTail = boxLid->tail->prev;
        delete boxLid->tail;
        boxLid->tail = newTail;

        if (size() == 1)
        {
            deleteFront();
        }
        else
        {
            newTail->next = nullptr;
        }
        --length;
    }
    else
    {
        throw std::logic_error("Deleting on empty list");
    }
}