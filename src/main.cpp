#include<iostream>
#include "file.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
  string Path = "./tmd.txt";
  _file file(Path);
  file.writeFile("ttt");
  cout << "tmd" << endl;
  vector<string> tmd;
  for(int a = 0; a < 100; ++a){
    tmd.push_back(to_string(a));
  }
  file.writeFile(tmd);
  return 0;
}
