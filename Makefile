all: clean neural

neural: main.c types.c
	gcc -o neural main.c formula.c types.c

clean:
	rm ./neural