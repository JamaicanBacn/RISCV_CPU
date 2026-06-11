CFLAGS = -c -Wall -g
LFLAGS = -g -o assign4a

all : HexGen.o
	g++ HexGen.o -o app

HexGen.o: HexGen.cpp
	g++ HexGen.cpp -c

clean:
	rm -f *.exe *.o