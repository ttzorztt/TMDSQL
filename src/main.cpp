/*
 * @Description: 主函数的实现
 * @Autor: TMD
 * @Date: 2022-11-01 22:24:29
 * @LastEditTime: 2022-11-05 17:52:05
 */
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