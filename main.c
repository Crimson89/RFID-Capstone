#include "head.h"

// Golbals for the callback to access
struct global
{
  int level_buffer[BADGE_LEN];
  uint32_t tick_buffer[BADGE_LEN];
  int cb_counter; // Counter to keep track of how many bits have been read
  int read_ctrl; // Variable to hold or stop reading loop
}data;

int main(int argc, char *argv[])
{
  int station_control = 1; // Var to terminate program
  char station_id[100];
  FILE *fp;
  int station_state = 0; // Stations current state, 1 = ON, 0 = OFF
  //CURL * curl;
  //CURLcode res;

  if (init() < 0)
  {
    printf("Failed to initialise\n");
    return 1;
  }

  read_station_info(&fp, station_id); // Get station info from file or create it

  //curl_global_init(CURL_GLOBAL_ALL);
  //curl = curl_easy_init();

  while (station_control == 1) // Exiting this loop will end the program
  {
    read_badge(); // Wait for badge swipe
    //send_id(station_id, badge_num, station_state); // Send the station id, badge number, and state

    //Do things based on return of send_id 

    station_control = 0; // Turn off for testing purposes
  }

  cleanup(); // Release resources
  return 0;
}

void callback(int gpio, int level, uint32_t tick)
{
  // Value indicates when we want to stop reading
  if(data.cb_counter == BADGE_LEN)
  {
    data.read_ctrl = 0; // Done reading
    data.cb_counter = 0; // Reset callback counter
    return;
  }
  else
  {
    data.level_buffer[data.cb_counter] = level;
    data.tick_buffer[data.cb_counter] = tick;
    data.cb_counter++;
    return;
  }
}

void read_badge()
{
  // Wait until all values have been read
  while(data.read_ctrl)
  {
    sleep(1);
  }

  for (int i=0; i<BADGE_LEN; i++)
  {
    printf("Timestamp: %d\n", data.tick_buffer[i]);
  }

  printf("\nRaw binary\n");

  for (int i=0; i<BADGE_LEN; i++)
  {
    printf("%d", data.level_buffer[i]);
  }

  printf("\n");

  return;
}
