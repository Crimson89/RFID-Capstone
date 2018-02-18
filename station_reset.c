#include "head.h"

int main()
{
  printf("\nThis will change the Station ID. Do you want to continue? [y/n]\n");
  char temp;
  scanf("%1c", &temp);
  if (temp == 'y' || temp == 'Y')
  {
    char station[100];
    FILE *fp;
    fp = fopen("station_info.txt", "w");
    printf("\nPlease enter a unique Station ID. No spaces. Max 100 characters.\n");
    scanf("%100s", &station);
    printf("\nStation ID: %s\n", station);
    fprintf(fp, station);
    fclose(fp);
    printf("Station ID has been successfully saved!\n");
  }
  else
    printf("\nNo changes were made to the Station ID\n");
  return 0;
}
