all: main reset

main: main.o
	gcc -g main.o -o station -lpigpio -lrt -lpthread

reset: station_reset.o
	gcc -g station_reset.o -o reset

read: read.o
	gcc -g read.o -o read -lpigpio -lrt -lpthread

station_reset.o: station_reset.c
	gcc -g -c station_reset.c

main.o: main.c
	gcc -g -c main.c -lpigpio -lrt -lpthread

read.o: read.c
	gcc -g -c read.c -lpigpio -lrt -lpthread

clean:
	rm -f station main.o station_info.txt station_reset.o reset read read.o
