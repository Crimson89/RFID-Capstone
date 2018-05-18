#include "../head.h"
#include <python2.7/Python.h>
// Compile with gcc run_py.c -lpython2.7
// Requires Python 2.7 libraries to be installed

int main()
{
  Py_Initialize();

  PyObject* obj = PyFile_FromString("read_i2c.py", "r");
  PyRun_SimpleFileEx(PyFile_AsFile(obj), "read_i2c.py", 1);
  Py_Finalize();

  char str[8];
  FILE* data;
  data = fopen("data.txt", "r");
  if (data == NULL)
  {
    printf("Could not open file\n");
    return 1;
  }

  fscanf(data, "%s", str);
  printf("%s\n", str);

  fclose(data);

  return 0;
}
