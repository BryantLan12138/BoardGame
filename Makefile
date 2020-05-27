.default: all

all: azul

clean:
	rm -f azul *.o

azul: CenterOfTable.o Factory.o GameBoard.o menu.o Mosaic.o Player.o Tile.o TileBag.o Score.o BoxLid.o Node.o SaveGame.o LoadGame.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^