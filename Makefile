CC = gcc
CFLAGS = -std=gnu17 -march=native -mtune=native -flto -O2 -Wall -Wextra
LDLIBS = -luuid -lpthread -lpq

.PHONY: all clean

all: zero

zero: main.o network.o database.o game.o
	$(CC) main.o network.o database.o game.o -o zero $(LDLIBS) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

network.o: network.c network.h
	$(CC) -c network.c $(CFLAGS)

database.o: database.c database.h
	$(CC) -c database.c $(CFLAGS)

game.o: game.c game.h
	$(CC) -c game.c $(CFLAGS)

clean:
	rm *.o zero
