all: main.c
	gcc -o work12 main.c

run: all
	./work12
