FLAG = -lpthread -lSDL -Wall -Werror -g
LIB = libfractal/fractal.o libfractal/tools.o
ARG = exemple_fractales.txt best.bmp
MT = --maxthreads 4

all: main clean

main: main.o
		@gcc -o main main.o $(LIB) $(FLAG)

main.o: main.c libfractal/fractal.h
		@gcc -c main.c -o main.o

clean:
		@rm -rf *.o

tests1.o: tests1.c ../libfractal/fractal.h
	@gcc -c tests1.c -lcunit -o tests1.o

mrproper: clean cleanV
	@rm -rf main

#-----------------------------------------------------------------------------------

exemple1:
	@./main -d --maxthreads 5 02input_fewbig.txt best.bmp

exemple2:
		@./main exemple_fractales.txt out.bmp

exemple3:
	@./main $(MT) exemple_fractales_original out.bmp

valgrind :
	@G_SLICE=always-malloc G_DEBUG=gc-friendly  valgrind -v --tool=memcheck --leak-check=full --num-callers=40 --log-file=valgrind.log ./main $(ARG)
	@tar -zcf valgrind-logs-main.tar.gz valgrind.log*
	@rm -rf valgrind-logs-main.tar.gz

cleanV:
	@rm -rf *.log
