/*
 * @Description  : 主函数的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 22:24:29
 * @LastEditTime : 2022-12-02 07:24:01
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
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
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

int main(int argc, char const *argv[])
{
  _file file("testdatabase2/TMD",type::_TYPE_PCB);

  ofstream filewrite(file.returnTruePath(),ios::out | ios::trunc);
  filewrite << "xxx" << endl;
  // cout << file.isExist() << endl;
  // file.write("T",type_mode::MODE_TRUNC);
  return 0;
}

int main1(int argc, char const* argv[]) {
  init();
  string tablePath = "testdatabase2/TMD";
   _file file(tablePath, type::_TYPE_TABLE);
  Table table(tablePath,type::_TYPE_TABLE);

  // vector<string> value = table.find("王五");
  // cout << value.size() << endl;
  // cout << value[0] << ' ' << value[1] << " " << value[2] << endl;
  
  // cout << table.isExist() << endl;

  // Table table(databasePath + "/" + "TMD");
 
  DataBase database("testdatabase2");
  if (database.isExist()) {
    cout << "存在" << endl;
  } else {
    database.create();
  }
  if(table.isExist()){
  
    table.remove();
  }
  if(!table.isExist()){
    table.create();
     }
    vector<string> value;
  value.push_back("姓名");
  value.push_back("年龄");
  value.push_back("性别");
// return 0;
  database.insertTable("TMD",value);
   value.clear();
  value.push_back("张三");
  value.push_back("14");
  value.push_back("男");
// database.insertTable("TMD",value);
value.clear();
   value.push_back("王五");
  value.push_back("17");
  value.push_back("女");
  // database.insertTable("TMD",value);
 
//   Index::update(table);
  // database.remove();
//   vector<string> value;
//   value.push_back("姓名");
//   value.push_back("年龄");
//   value.push_back("性别");

//   database.insertTable("TMD",value);
//   // table.append(value);
//   value.clear();
//   value.push_back("张三");
//   value.push_back("14");
//   value.push_back("男");
// database.insertTable("TMD",value);
// //   // table.append(value);
//   value.clear();
//   value.push_back("王五");
//   value.push_back("17");
//   value.push_back("女");
// //   // table.append(value);
//   database.insertTable("TMD",value);
}