#include<iostream>
#include "file.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
  system("mkdir ttt"); // 使用进程执行
  
  string Path = "tmd.txt";
  _file file(Path);
  file.addLock();
  file.removeLock();
  return 0;
}