CC = g++
CFLAGS = -Wall -g 
CLIBS = -lraylib 

all: main run

main: src/pendulum.cpp src/pendulum_vec.cpp
	$(CC) $(CFLAGS) src/pendulum_vec.cpp src/pendulum.cpp src/main.cpp -o bin/main $(CLIBS)

run:
	bin\main
