all: main reset

main: main.o
	gcc -g main.o func.o -o station -lpigpio -lrt -lpthread

main.o: main.c
	gcc -g -c main.c -lpigpio -lrt -lpthread -lrpio

func.o: func.c
	gcc -g func.o -o func -lpigpio -lrt -lpthread

read: read.o
	gcc -g read.o -o read_test -lpigpio -lrt -lpthread

read.o: read.c
	gcc -g -c read.c -lpigpio -lrt -lpthread -lrpio

reset: station_reset.o
	gcc -g station_reset.o -o reset

station_reset.o: station_reset.c
	gcc -g -c station_reset.c

clean:
	rm -f station main.o func.o station_info.txt reset station_reset.o read_test read.o
