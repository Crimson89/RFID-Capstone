#include "head.h"
#include <python2.7/Python.h>

#define SIZE 101
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
    printf("fopen\n");
    char line[SIZE];
    memset(line, '0', 101);
    int length = 0;
    printf("line: %s\n", line);
    char startBits[] = "000001";
    int len = strlen(startBits);

    printf("strlen\n");
    fscanf(data, "%200c", line);
    fclose(data);

    printf("fclose\n");
    char * ret;
    ret = strstr(line, startBits);
    if (ret == NULL)
      return 0;
    printf("strstr, %s\n", ret);
    char cardNo [25];
    //cardNo[25] = '\0';
    //strcpy(cardNo, ret);
    strncpy(cardNo, ret+19, 24);

    printf("strncpy\n");
    printf("Tag val: %s\n", cardNo);
    //remove("data.txt");

    printf("read_125 finished\n");
  return cardNo;
}
