#include "head.h"

int main(int argc, char *argv[])
{
  int station_control = 1; // Var to terminate program
  char station_id[100];
  FILE *fp;
  int station_state = 0; // Stations current state, 1 = ON, 0 = OFF
  pthread_t thread_id;

  if (init() < 0)
  {
    printf("Failed to initialise\n");
    return 1;
  }

  read_station_info(&fp, station_id); // Get station info from file or create it

  while (station_control == 1) // Exiting this loop will end the program
  {
    //read_125();

    // Here we want to call one of the functions to run in the "background"
    // Need to test to see which Hz reading function will work best here
    pthread_create(&thread_id, NULL, "function name", NULL);
    pthread_join(thread_id, NULL);

    station_control = 0; // Turn off for testing purposes
  }

  cleanup(); // Release resources
  return 0;
}
