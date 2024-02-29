CC = g++
CFLAGS = -Wall -g 
CLIBS = -lraylib 

all: main run

main: ./src/main.cpp
	$(CC) $(CFLAGS) ./src/main.cpp -o ./bin/main $(CLIBS)

run:
	bin\main
