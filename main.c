#include "head.h"

int main(int argc, char *argv[])
{
  char station[100];
  FILE *fp;
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
      scanf("%100s", &station);
      printf("\nStation ID: %s\n", station);
      fprintf(fp, station); // Store station id to station_info.txt
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
    fscanf(fp, "%s", station);
    printf("Station ID is: %s\n", station);
    fclose(fp);
  }

  return 0;
}
