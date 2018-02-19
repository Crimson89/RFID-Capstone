#include "head.h"
#define BADGE_LEN 9

int main(int argc, char *argv[])
{
  int station_control = 1; // Var to terminate program
  char station_id[100];
  FILE *fp;
  int station_state = 0; // Stations current state, 1 = ON, 0 = OFF
  int user_id = 0; // Maybe need to change type ****************
  int waiting_mode = 0; // Var to control waiting for access request
  char response[6]; // The "OK" signal var, might need to change **********

  // Start GPIO init
  if (gpioInitialise() < 0)
  {
    fprintf(stderr, "pigpio init failed\n");
    return 1;
  }

  // Set GPIO modes here
  gpioSetMode(18, PI_OUTPUT); // GPIO 18 as logic output for machine state

  fp = fopen("station_info.txt", "r");
  // If there is no Station ID, prompt the user to make one
  if (fp == NULL)
  {
    printf("\nStation ID not found. Would you like to create one?\n[y/n]\n");
    char temp;
    scanf("%1c", &temp);
    if (temp == 'y' || temp == 'Y')
    {
      fp = fopen("station_info.txt", "w");
      printf("\nPlease enter a unique Station ID. No spaces. Max 100 characters.\n");
      scanf("%100s", &station_id);
      printf("\nStation ID: %s\n", station_id);
      fprintf(fp, station_id); // Store station_id id to station_id_info.txt
      fclose(fp);
      printf("Station ID has been successfully saved!\n");
    }
    else
    {
      printf("\nCannot run program without Station ID. Exiting...\n");
      return 1;
    }
  }
  else
  {
    // Read Station ID from file
    fscanf(fp, "%s", station_id);
    printf("Station ID is: %s\n", station_id);
    fclose(fp);
  }


  while (station_control == 1) // Exiting this loop will end the program
  {
    // While station is in OFF state, poll for badge swipe
    while (station_state == 0)
    {
      // Read for incoming badge
      if (user_id != 0 && user_id >= BADGE_LEN) // Will need a change here ***********
      {
        // Send user_id, station_id, and station_state
        waiting_mode = 1; // Wait for response
        while (waiting_mode == 1)
        {
          // Look for response
          if (response == "200 OK") // If granted access
          {
            station_state = 1; // Set state to active
            waiting_mode = 0; // Exit wait mode
          }
          else // No access, leave state as 0
          {
            waiting_mode = 0; // Exit wait mode
          }
        }
      }
    }

    // While station is in ON state, output a 1 on GPIO 18
    while (station_state == 1)
    {
      gpioWrite(18, 1); // Turn ON
      // More to go here like LED's and a way to turn off the machine
    }
  }

  gpioTerminate(); // Release resources

  return 0;
}
