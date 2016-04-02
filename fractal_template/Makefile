CC = gcc
FLAG = -lpthread -lSDL -Wall -Werror
LIB = libfractal/fractal.o libfractal/tools.o

all: main clean
	@echo YOUHOUHOU!!!! CA COMPILE MAGGLE!!

main: main.o
		@$(CC) -o main main.o $(LIB) $(FLAG)

main.o: main.c libfractal/fractal.h
		@$(CC) -c main.c -o main.o


clean:
		@rm -rf *.o

mrproper: clean
	@rm -rf main
