#include "head.h"
#include <unistd.h>

uint32_t old_tick;
uint32_t duration;
int old_level;
int control = 0;

void callback(int gpio, int level, uint32_t tick)
{
  if (control == 0) // First callback
  {
    old_tick = tick;
    old_level = level;
    control = 1;
    return;
  }
  else
  {
    duration = tick - old_tick;
    old_tick = tick;
    printf("GPIO %d went from %d to %d in %d microseconds\n", gpio, old_level, level, duration);
    old_level = level;
    return;
  }
}

int main()
{
  gpioInitialise();
  gpioSetMode(4, PI_INPUT);
  gpioSetAlertFunc(4, callback);

  for (int i=0; i < 4; i++)
  {
    gpioWrite(4,0);
    usleep(100);
    gpioWrite(4,1);
    usleep(100);
  }

  gpioTerminate();
  return 0;
}
