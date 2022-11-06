/*
 * @Description  : 主函数的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 22:24:29
 * @LastEditTime : 2022-11-06 21:00:49
 */
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _DATEBASE_H_
#define _DATEBASE_H_
#include "DataBase.h"
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

/**
 * @brief 准备工作，创建所需目录
 * @return
 */
void init() {
  if (!access("../data", F_OK)) {
    mkdir("../data", 777);
  }
  if (!access("../data/database", F_OK)) {
    mkdir("../data/database", 777);
  }
  if (!access("../data/lock", F_OK)) {
    mkdir("../data/lock", 777);
  }
  if (!access("../view", F_OK)) {
    mkdir("../view", 777);
  }
}
int main(int argc, char const* argv[]) {
  init();
  _file test("../data/database/testbase/CPS1985.csv");
  vector<string> ans;
  while(test.readline(ans)){
    cout << ans.size() << endl;
  for (string& str : ans) {
    cout << str;
  }
  cout << endl;
  }

}