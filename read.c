#include "head.h"

int level_buffer[101];
uint32_t tick_buffer[101];
int cb_counter = 0;
int read_ctrl = 1;

void callback(int gpio, int level, uint32_t tick)
{
  // Value indicates when we want to stop reading
  if(cb_counter == 101)
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
    //printf("Level = %d\nTick = %d\n", level, tick);
    return;
  }
}

void signal()
{
 // Call python script to start PWM 
}

int main()
{
  gpioInitialise();
  gpioSetMode(4, PI_INPUT);
  //gpioSetPullUpDown(4, PI_PUD_UP);

  gpioSetAlertFunc(4, callback); // Start callback on GPIO 4

  // Wait until all values have been read
  while(read_ctrl)
  {
    //sleep(1);
  }

  uint32_t time[100];
  for (int i=0; i < 100; i++)
  {
  time[i] = tick_buffer[i+1] - tick_buffer[i];
  }

  for (int i=0; i < 100; i++)
  {
    printf("Time = %d\n",time[i]);
  }
/*
  int bits[50];
  int k = 0;
  for (int i=0; i < 50; i++)
  {
    if((time[k] < 37) || (time[k+1] < 37))
      bits[i] = 0;
    else if((time[k] > 37) || (time[k+1] > 37))
      bits[i] = 1;
    else if((time[k] < 37) || (time[k+1] > 37))
      printf("Error, Time inconsistancy");
    else if((time[k] > 37) || (time[k+1] < 37))
      printf("Error, Time inconsistancy");
    k = k+2;
  }*/
  /*
   Check time[i] and [i+1] to verify they are within the same range.
   Set bits in new array depending on the length of the times.
   Potentially convert bits into more readable form like hex or int
   */

  gpioTerminate();
  return 0;
}
