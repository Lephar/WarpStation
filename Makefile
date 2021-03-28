CC = gcc
CFLAGS = -std=gnu17 -march=native -mtune=native -flto -O2 -Wall -Wextra

.PHONY: all clean

all: zero

zero: main.o game.o network.o database.o
	$(CC) main.o game.o network.o -o zero $(CFLAGS)

main.o: main.c main.h.gch
	$(CC) -c main.c -o main.o $(CFLAGS)

main.h.gch: main.h
	$(CC) -c main.h -o main.h.gch $(CFLAGS)

game.o: game.c game.h.gch
	$(CC) -c game.c -o game.o -lm -luuid -lpthread $(CFLAGS)

game.h.gch: game.h
	$(CC) -c game.h -o game.h.gch $(CFLAGS)

network.o: network.c network.h.gch
	$(CC) -c network.c -o network.o -luuid -lpthread $(CFLAGS)

network.h.gch: network.h
	$(CC) -c network.h -o network.h.gch $(CFLAGS)

database.o: database.c database.h.gch
	$(CC) -c database.c -o database.o -luuid -lpthread -lpq $(CFLAGS)

database.h.gch: database.h
	$(CC) -c database.h -o database.h.gch $(CFLAGS)

clean:
	rm *.gch *.o zero
