all: main

main: 
	g++ -o bin/mnist-1lnn -Iutil main.c 1lnn.c util/screen.c util/mnist-utils.c util/mnist-stats.c

