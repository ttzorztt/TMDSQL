/*
 * @Description  : 主函数的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 22:24:29
 * @LastEditTime : 2023-01-08 11:49:17
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
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
using namespace std;

/**
 * @brief 准备工作，创建所需目录
 * @return
 */
void init() {
  if (access("../data", F_OK)) {
    _super::createDir("../data");
  }
  if (access("../data/database", F_OK)) {
    _super::createDir("../data/database");
  }
  if (access("../data/index", F_OK)) {
    _super::createDir("../data/index");
  }
  if (access("../data/log", F_OK)) {
    _super::createDir("../data/log");
  }
  if (access("../data/PCB", F_OK)) {
    _super::createDir("../data/PCB");
  }
  if (access("../view", F_OK)) {
    _super::createDir("../view");
  }
}
int main(int argc, char const* argv[]) {
  // Table table("DB1/TTT", type::_TYPE_TABLE);
  // table.create();
  init();
  shell x;
  string tmp = "执行 @SQL";
  x.read(tmp);
  // while (1) {
  //   getline(cin, tmp);
  //   if (tmp == "") {
  //     menuOutput::printPower(x.ReturnPower());
  //   }else  {
  //     x.read(tmp);
  //   }
  // }
  // vstring v;
  // v.push_back("1");
  // v.push_back("2");
  // cout << v.size() << endl;
  // v.clear();

  // cout << v.size() << endl;

  return 0;
}

int main1(int argc, char const* argv[]) {
  init();
  string tablePath = "testdatabase2/TMD";
  Table table(tablePath, type::_TYPE_TABLE);
  DataBase database("testdatabase2");
  _file(tablePath, type::_TYPE_TABLE).remove();
  _file(tablePath, type::_TYPE_INDEX_TABLE).remove();
  _file(tablePath, type::_TYPE_PCB).remove();
  if (database.isExist()) {
    cout << "存在" << endl;
  } else {
    database.create();
  }
  if (table.isExist()) {
    table.remove();
  }
  if (!table.isExist()) {
    table.create();
  }
  vstring ve;
  vstring value;
  value.push_back("姓名");
  value.push_back("年龄");
  value.push_back("性别");
  value.push_back("爱好");
  database.insertTable("TMD", value);
  value.clear();
  value.push_back("张三");
  value.push_back("14");
  value.push_back("男");
  value.push_back("打球");
  database.insertTable("TMD", value);
  value.clear();
  value.push_back("王五");
  value.push_back("17");
  value.push_back("女");
  value.push_back("打乒乓球");
  database.insertTable("TMD", value);
  ve.clear();
  ve = table.find("张三");
  std::cout << ve.size();
  cout << ve[0] << ve[1] << ve[2] << ve[3] << endl;
  ve.clear();
  ve = table.find("张三");
  std::cout << ve.size();
  cout << ve[0] << endl;
  // ve.clear();
  //   Index::update(table);
  // database.remove();
  //   vstring value;
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
  return 0;
}