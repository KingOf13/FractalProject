CC = gcc
FLAG = -lpthread -lSDL -Wall -Werror
LIB = libfractal/fractal.o libfractal/tools.o

all: main clean

main: main.o
		@$(CC) -o main main.o $(LIB) $(FLAG)

main.o: main.c libfractal/fractal.h
		@$(CC) -c main.c -o main.o

clean:
		@rm -rf *.o

mrproper: clean
	@rm -rf main

exemple:
	@./main -d --maxthreads 4 exemple_fractales.txt best.bmp
