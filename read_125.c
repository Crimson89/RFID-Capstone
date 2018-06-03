#include "../head.h"
#include <python2.7/Python.h>
// Compile with gcc run_py.c -lpython2.7
// Requires Python 2.7 libraries to be installed

int read_125()
{
  // This run the python code to read the incoming data on I2C
  Py_Initialize();
  PyObject* obj = PyFile_FromString("i2c.py", "r");
  PyRun_SimpleFileEx(PyFile_AsFile(obj), "i2c.py", 1);
  Py_Finalize();


  // Next we read the stored data from the python module
  char str[80];
  FILE* data;
  data = fopen("data.txt", "r");
  if (data == NULL)
  {
    printf("Could not open file\n");
    return 1;
  }

  // Data is stored into string
  fscanf(data, "%u", str);
  printf("%u\n", str);

  fclose(data);

  return 0; // Need to return relevant data back to top
}
