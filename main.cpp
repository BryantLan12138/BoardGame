#include <iostream>

#include "Factory.h"
#include "GameBoard.h"

int main(void)
{
    //Testing gameBoard
    // GameBoard *gameBoard = new GameBoard(1000);
    // gameBoard->fillFactories();
    // std::cout << "Printing factories" << std::endl;
    // gameBoard->printFactories();
    // gameBoard->createPlayer("A", "B");
    // std::cout << std::endl;

    // std::cout << "Player Mosaics for " << gameBoard->getPlayer(0)->getPlayerName() << std::endl;
    // gameBoard->getPlayer(0)->getMosaic()->printMosaic();
    // std::cout << std::endl;

    // gameBoard->pickTileFromFactory(4, 'U', 1, 0);

    //Testing factory
    TileBag *tileBag = new TileBag(2000);
    // CenterOfTable *centerOfTable = new CenterOfTable();
    // Mosaic *mosaic = new Mosaic();
    Factory *factory1 = new Factory();
    Factory *factory2 = new Factory();
    factory1->fillFactory(tileBag);
    factory2->fillFactory(tileBag);

    factory1->printFactoryInfo();
    std::cout << std::endl;
    factory2->printFactoryInfo();
    std::cout << std::endl;

    std::cout << "Printing after sorting" << std::endl;
    factory1->sortTiles();
    factory1->printFactoryInfo();
    std::cout << std::endl;
    factory2->sortTiles();
    factory2->printFactoryInfo();
    std::cout << std::endl;

    // for (int i = 0; i < factory1->getSize() - 1; ++i)
    // {
    //     if (factory1->getTile(i)->getColourAsChar() == 'L')
    //     {
    //         factory1->removeTile(i);
    //     }
    // }

    // factory1->removeTile(3);
    // std::cout << factory1->getSize() << std::endl;
    // for (int i = 0; factory1->getSize() - 1; ++i)
    // {
    //     std::cout << factory1->getTile(i)->getColourAsChar() << std::endl;
    // }
    // std::cout << std::endl;
    // factory1->pickTiles('R', centerOfTable);
    // factory2->pickTiles('L', centerOfTable);
}