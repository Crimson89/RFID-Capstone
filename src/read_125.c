#include "head.h"
#include <python2.7/Python.h>

#define SIZE 99
// Compile with gcc run_py.c -lpython2.7
// Requires Python 2.7 libraries to be installed

char* read_125()
{
    printf("Starting python interpreter\n");
    // This run the python code to read the incoming data on I2C
    Py_Initialize();
    PyObject* obj = PyFile_FromString("i2c.py", "r");
    PyRun_SimpleFileEx(PyFile_AsFile(obj), "i2c.py", 1);
    Py_Finalize();
    printf("Python interpreter finalized\n");

    char str[80];
    FILE* data;
    data = fopen("data.txt", "r");
    if (data == NULL)
    {
      printf("Could not open file\n");
      return 0;
    }

    // Check to see if file is empty
    //fseek (data, 0, SEEK_END);
    //int size = ftell(data);
    //if (size != 0) // If there is something
    //{
      //char* line = malloc(sizeof(char)*99);
      const char line[SIZE];
      //memset(line, '0', SIZE);

      //printf("line: %s\n", line);
      const char startBits[10] = "0000001";
      //int len = strlen(startBits);

      //for (int i = 0; i < 99; i++)
      //{
      //  line[i] = getc(data);
      //}

      //printf("strlen\n");
      /*int i=0;
      while(!feof(data))
      {
        fscanf(data, "%s", line[i]);
        i++;
      }*/
      fscanf(data, "%99c", &line);
      fclose(data);

      printf("line: %s\n", line);
      char * ret;
      ret = strstr(line, startBits);

      printf("strstr %s\n", ret);
      char cardNo [25];
      cardNo[24] = '\0';
      //strcpy(cardNo, ret);
      strncpy(cardNo, ret+19, 24);

      printf("strncpy\n");
      printf("Tag val: %s\n", cardNo);
      remove("data.txt");

      printf("read_125 finished\n");
      bcm2835_delay(1000);
      return cardNo;
    //}
    //else
      //return 0;
}
