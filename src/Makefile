all: main reset

main: main.o funcs.o read_125.o value.o config.o rfid.o rc522.o
	gcc -g main.o funcs.o read_125.o value.o config.o rfid.o rc522.o -o station -lrt -lpthread -lpython2.7 -lbcm2835 -lwiringPi

funcs.o: funcs.c
	gcc -g -c funcs.c -lrt

read_125.o: read_125.c
	gcc -g -c read_125.c -lpython2.7

main.o: main.c value.c config.c rfid.c rc522.c
	gcc -g -c -Wall -Wextra main.c value.c config.c rfid.c rc522.c -lwiringPi -lbcm2835

reset: station_reset.o
	gcc -g station_reset.o -o reset

station_reset.o: station_reset.c
	gcc -g -c station_reset.c

clean:
	rm -f station main.o funcs.o read_125.o station_info.txt reset station_reset.o read_13.o value.o config.o rfid.o rc522.o
