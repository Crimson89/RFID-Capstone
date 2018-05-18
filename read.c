#include "head.h"

// Golbals for the callback to access
  int level_buffer[BADGE_LEN];
  uint32_t tick_buffer[BADGE_LEN];
  int cb_counter = 0; // Counter to keep track of how many bits have been read
  int read_ctrl = 1; // Variable to hold or stop reading loop

void callback(int gpio, int level, uint32_t tick)
{
  // Value indicates when we want to stop reading
  if(cb_counter == BADGE_LEN)
  {
    read_ctrl = 0; // Done reading
    cb_counter = 0; // Reset callback counter
    return;
  }
  else
  {
    level_buffer[cb_counter] = level;
    tick_buffer[cb_counter] = tick;
    cb_counter++;
    return;
  }
}

int main()
{
  gpioInitialise();
  gpioSetMode(18, PI_INPUT);
  gpioSetAlertFunc(18, callback);

  // Wait until all values have been read
  while(read_ctrl)
  {
    sleep(1);
  }

  for (int i=0; i<BADGE_LEN; i++)
  {
    printf("Level: %d\nTime: %d\n", level_buffer[i], (tick_buffer[i+1]-tick_buffer[i]));
  }

  printf("\nRaw binary\n");

  for (int i=0; i<BADGE_LEN; i++)
  {
    printf("%d", level_buffer[i]);
  }

  printf("\n");

  gpioTerminate();
  return 0;
}
