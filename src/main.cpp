#ifndef _IOSTREAM_
#define _IOSTREAM_
#include<iostream>
#endif
#ifndef _FILE_
#define _FILE_
#include "file.h"
#endif
#ifndef _DATEBASE_
#define _DATEBASE_
#include "DateBase.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
// #include <unistd.h>
using namespace std;
int main(int argc, char const *argv[])
{
  string path = "./";
  DateBase a(path);
  a.showDateBase();
  return 0;
}