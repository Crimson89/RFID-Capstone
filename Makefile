all: main

main: main.o
	gcc -g main.o -o station

main.o: main.c
	gcc -g -c main.c

clean:
	rm -f station main.o station_info.txt
