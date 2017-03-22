CC=gcc

default: strassen.o
	gcc -o strassen strassen.o -I.

all: strassen.o
	gcc -o strassen strassen.o -I.

strassen: strassen.o
	gcc -o strassen strassen.o -I.

matrix: matrix.o
	gcc -o matrix matrix.o -I.