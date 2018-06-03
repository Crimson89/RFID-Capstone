// Functions, prototypes, defines, includes, etc.

#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BADGE_LEN 101 // Number of bits to read

void callback(int gpio, int level, uint32_t tick);
void read_badge();
int init();
void cleanup();
int read_station_info(FILE **fp, char *station_id);


