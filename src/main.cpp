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

using namespace std;
int main(int argc, char const *argv[])
{
  string Path = "tmd.txt";
  _file file(Path);
  DateBase data("tmd");
  // data.create();
  vector<string> tm;
  for(int a = 0; a < 10; ++a){
    tm.push_back(to_string(a));
  }
  data.insertTable("tt3t",tm);
  return 0;
}