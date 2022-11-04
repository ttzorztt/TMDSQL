#include<iostream>
#include "file.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
  string Path = "tmd.txt";
  _file file(Path);
  file.writeFile("sdfsda");
  return 0;
}