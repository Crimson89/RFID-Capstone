#include "head.h"
#define BADGE_LEN 9

int main(int argc, char *argv[])
{
  int station_control = 1; // Var to terminate program
  char station_id[100];
  FILE *fp;
  int station_state = 0; // Stations current state, 1 = ON, 0 = OFF
  int user_id = 0; // Maybe need to change type ****************
  char response[6]; // The "OK" signal var, might need to change **********
  CURL * curl;
  CURLcode res;

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

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  while (station_control == 1) // Exiting this loop will end the program
  {
    // Read for incoming badge
    // {
    //  Read/Poll for incoming badge code here
    // }

    // If there is an ID and it's a valid lenght
    if (user_id != 0 && user_id >= BADGE_LEN) // Will need a change here ***********
    {
      // Send user_id, station_id, and station_state
      if(curl)
      {
        struct string s;
        init_string(&s);
        // Set URL that will receive POST
        curl_easy_setopt(curl, CURLOPT_URL, "https://ruby.cecs.pdx.edu:3001/");
        // Specify POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Station=3DPrinter1 UserID=138902 State=Off");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);
        // Check return and turn machine on or off
        /*if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
*/
        printf("%s\n", s.ptr);

        curl_easy_cleanup(curl);
      }
    }
   }
  // Cleanup
  gpioTerminate(); // Release resources
  free(s.ptr);
  curl_global_cleanup();

  return 0;
}
