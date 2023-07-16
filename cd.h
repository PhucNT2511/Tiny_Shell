#include <errno.h>
#include <stdlib.h>
using namespace std;

const string rootDir(_getcwd(NULL, 0));

void curDir()
{
  char *buffer;
  if ((buffer = _getcwd(NULL, 0)) == NULL)
    cout << "_getcwd error";
  system("dir");
  free(buffer);
}

void parentDir()
{
  char *buffer;
  if ((buffer = _getcwd(NULL, 0)) == NULL)
    cout << "_getcwd error";
  string dir(buffer);
  string parentDir = dir.substr(0, dir.find_last_of("\\"));
  /* if (_chdir(parentDir.c_str())) */
  if(chdir(parentDir.c_str()))
  {
    switch (errno)
    {
    case ENOENT:
      printf("No such file or directory.\n");
      break;
    case EINVAL:
      printf("Invalid buffer.\n");
      break;
    default:
      printf("Unknown error.\n");
      break;
    }
  }
  // else
   // system("dir");
  free(buffer);
}

void changeDir(string path)
{
  if (chdir(path.c_str()))
  {
    switch (errno)
    {
    case ENOENT:
      printf("No such file or directory.\n");
      break;
    case EINVAL:
      printf("Invalid buffer.\n");
      break;
    default:
      printf("Unknown error.\n");
      break;
    }
  }
  //else
   // system("dir");
}



