/*
 * @Description  : 主函数的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 22:24:29
 * @LastEditTime : 2022-11-09 22:00:40
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
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
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
  string tablePath = "../data/database/testdatabase1/table1";
  string databasePath = "testdatabase2";
  DataBase database(databasePath);
  // cout << database.returnName() << " " << database.returnType() << endl;
  database.showDataBaseTable();
  database.create();
  DataBase::showDataBase();
  database.remove();
  // super::returnTruePath(Path,style);
  //     return access(Path.c_str(), F_OK) != -1;
  // _super test("../data/database/testdatabase1",type::_TYPE_DIR);
  // cout <<  test.isExist() << endl;
  // cout << test.remove() << endl;
  // vector<string> ans;
  // while(test.readline(ans)){
  // for (string& str : ans) {
  //   // cout << str;
  // } 
  // ans.clear();
  // cout << endl << endl;
  } 