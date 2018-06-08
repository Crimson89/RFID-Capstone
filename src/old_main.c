#include "head.h"
#include "main.h"

int main(int argc, char *argv[])
{
  int station_control = 1; // Var to terminate program
  char* station_id = (char*) malloc(sizeof(char)*100);
  int station_state = 0; // Stations current state, 1 = ON, 0 = OFF
  pthread_t thread_id1;
  pthread_t thread_id2;

  printf("Initializing settings\n");
  init();
  //init_13();

  printf("init_13() Started\n");
  uint8_t gpio=255;           // GPIO for hard-reset
  uint32_t spi_speed = 1000L; // speed for SP (4 < >125) overruled by config file value

  // must be run as root to open /dev/mem in BMC2835
  if (getuid() != 0)
  {
      p_printf(RED, "Must be run as root.\n");
      exit(1);
  }
  printf("getuid fin\n");
  //Led_On();

  // catch signals
  set_signals();

  printf("set_signals fin\n");
  /* read /etc/rc522.conf */
  if (get_config_file()) exit(1);

  printf("get_config_file fin\n");
  /* set BCM2835 Pins correct */
  if (HW_init(spi_speed,gpio)) close_out(1);

  printf("HW_init fin\n");
  /* initialise the RC522 */
  InitRc522();

  printf("InitRc522 fin\n");
  /* read & set GID and UID from config file */
  if (read_conf_uid()!= 0) close_out(1);

  printf("read_conf_uid fin\n");
  printf("init_13() Completed\n");

  printf("Finished initializing\n");

  read_station_info(station_id); // Get station info from file or create it

  while (station_control == 1) // Exiting this loop will end the program
  {
    void* cardNo125;
    void* cardNo13;

    printf("Starting a 125 read\n");

    pthread_create(&thread_id1, NULL, &read_125, &cardNo125);
    printf("Start a 13.5 read\n");
    pthread_create(&thread_id2, NULL, &send_card_no, &cardNo13);
    printf("Threads created\n");


    while(1);

    station_control = 0; // Turn off for testing purposes
  }

  cleanup(); // Release resources
  return 0;
}
