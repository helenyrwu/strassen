CC=gcc

default: strassen.o
	gcc -o strassen strassen.o -I.

all: strassen.o
	gcc -o strassen strassen.o -I.