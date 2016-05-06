FLAG = -lpthread -lSDL -Wall -Werror
LIB = libfractal/fractal.o libfractal/tools.o
MT = --maxthreads 100

all: main clean

main: main.o
	@gcc -o main main.o $(LIB) $(FLAG)

testlib: libfractal/fractal.o test/testlib.o
	@gcc -o test/fractal libfractal/fractal.o test/testlib.o -lcunit
	@./test/fractal

main.o: main.c libfractal/fractal.h
	@gcc -c main.c -o main.o

clean:
	@rm -rf *.o
	@rm -rf test/*.o

testlib.o: test/testlib.c libfractal/fractal.h
	@gcc -c testlib.c -lcunit -o test/testlib.o

mrproper: clean
	@rm -rf main
	@rm -rf test/fractal

#-----------------------------------------------------------------------------------

exemple1:
	@./main $(MT) ../fract_inputs/02input_fewbig.txt best.bmp

exemple2:
		@./main ../exemple_fractales.txt out.bmp

exemple3:
	@./main $(MT) ../exemple_fractales_original out.bmp

exemple4:
	@./main ../exemple_fractales_original out.bmp

exemple5:
	@./main $(MT) ../fract_inputs/03input_manysmall.txt best.bmp
