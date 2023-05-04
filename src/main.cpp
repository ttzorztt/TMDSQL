/**
 * @file main.cpp
 * @brief 主函数的实现
 * @author TMD
 * @date 2022-11-01
 */
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <unistd.h>

#include <cstddef>
#include <iostream>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
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
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_
#include "BackTracking.h"
#endif
using namespace std;

/**
 * @brief init database
 * @return
 */
void init() {
  if (access("./data", F_OK)) {
    _super::createDir("./data");
  }
  if (access("./data/database", F_OK)) {
    _super::createDir("./data/database");
  }
  if (access("./data/index", F_OK)) {
    _super::createDir("./data/index");
  }
  if (access("./data/PCB", F_OK)) {
    _super::createDir("./data/PCB");
  }
  if (access("./data/view", F_OK)) {
    _super::createDir("./data/view");
  }
  if (access("./data/SQL", F_OK)) {
    _super::createDir("./data/SQL");
  }
  if (access("./data/SQL/init", F_OK)) {
    _file table("./data/SQL/init");
    table.create();
    table.write({"登录", "@root", "root"}, type_mode::WRITEBUFF_MODE_APP);
    table.write({"创建", "数据库", "@DB1"}, type_mode::WRITEBUFF_MODE_APP);
    table.write({"创建", "数据库", "表,@DB1", "TB1"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "序号", "姓名", "性别",
                 "学历", "爱好", "住址", "联系方式"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "0", "张三", "男",
                 "本科", "钓鱼", "北京", "110"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "1", "李四", "男",
                 "研究生", "吃饭", "西安", "120"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "2", "王五", "女",
                 "博士", "吃鱼", "天津", "119"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "3", "赵六", "女",
                 "博士后", "跳绳", "四川", "122"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "4", "刘七", "男",
                 "初中", "跳大绳", "深圳", "114"},
                type_mode::WRITEBUFF_MODE_APP);
    table.write({"插入", "数据库", "表", "@DB1", "TB1", "5", "雷八", "女",
                 "高中", "跳小绳", "安徽", "911"},
                type_mode::WRITEBUFF_MODE_APP);
  }
  if (access("./data/User", F_OK)) {
    _super::createDir("./data/User");
  }
  if (access("./data/User/pd", F_OK)) {
    _file table("./data/User/pd", true, "root,root,0");
  }
  if (access("./data/Log", F_OK)) {
    _super::createDir("./data/Log");
  }
  if (access(_super::returnTruePath(Log::nowData(), type::_TYPE_LOG).c_str(),
             F_OK)) {
    _file(Log::nowData(), type::_TYPE_LOG, true);
  }
  if (access("./data/Back", F_OK)) {
    _super::createDir("./data/Back");
  }
  if (access(_super::returnTruePath(Log::nowData(), type::_TYPE_BACK).c_str(),
             F_OK)) {
    _file(Log::nowData(), type::_TYPE_BACK, true);
    BackTracking::init();
  }
}
int main1(int argc, char const* argv[]) {
  init();
  shell x;
  string tmp = "执行 @s";
  Log::open();
  while (1) {
    getline(cin, tmp);
    if (!x.read(tmp)) {
      break;
    }
  }
  Log::close();
  return 0;
}
int main(int argc, char const* argv[]) {
  init();
  shell x;
  string tmp = "执行 @init";
  x.read(tmp);
  /* tmp = "回溯 显示"; */
  /* x.read(tmp); */
	tmp = "回溯 显示 @" + Log::nowData();
	x.read(tmp);
	tmp = "回溯 @" + Log::nowData() + " 10";
	x.read(tmp);
	/* tmp = "回溯 清理"; */
	/* x.read(tmp); */
	return 0;
  Log::open();
	tmp = "创建 数据库 表 @DB1 TB";
	x.read(tmp);
	tmp = "创建 数据库 表 @DB1 TT";
	x.read(tmp);
	tmp = "插入 数据库 表 @DB1 TB 1 2 3 4 5 6 7";
	x.read(tmp);
	tmp = "插入 数据库 表 @DB1 TT 2 3 4 5 6 7";
	x.read(tmp);
  BackTracking::BackTrackingForShow(Log::nowData());
	return 0;
  BackTracking::BackTrackingForRecoverDatabase("DB1");
	BackTracking::BackTrackingForCreateDatabase("DDD1");
	BackTracking::BackTrackingForCreateDatabaseTable("DDD1","TTT");
  /* BackTracking::BackTrackingForCreateUser("TMD", "TT"); */
  /* BackTracking::BackTrackingForCreateManager("ddd", "rr"); */
  BackTracking::BackTrackingForRecoverDatabaseTable("DB1", "TB1");
  /* BackTracking::BackTrackingForDeleteDatabase("DBID"); */
  /* BackTracking::BackTrackingForDeleteDatabaseTable("DBID", "TBID"); */
  /* BackTracking::BackTrackingForDeleteDatabaseTable("DBID", "TBID"); */
  /* BackTracking::BackTrackingForDeleteUser("UserName"); */
  /* BackTracking::BackTrackingForDeleteManager("UserName"); */
  /* BackTracking::BackTrackingForInsertColDatabaseTable("DBID", "TBID", */
  /*                                                     {"1", "2", "4"}); */
  /* BackTracking::BackTrackingForDeleteRowDatabaseTable("DBID", "TBID", "2"); */
  /* BackTracking::BackTrackingForInsertDatabaseTable("DBID", "TBID", */
  /*                                                  {"1", "3", "4"}); */
  /* BackTracking::BackTrackingForSetViewDatabaseTable("DBID", "TBID", "TMD", */
  /*                                                   {"1", "2", "4", "5"}); */
  /* BackTracking::BackTrackingForSetIndexDatabaseTable("DBID", "TBID", "2"); */
  /* BackTracking::BackTrackingForSetIndexDatabaseTable("DBID", "TBID", "2"); */
  /* BackTracking::BackTrackingForShow(); */
  return 0;
  tmp = "登录 @root root";
  x.read(tmp);
  Log::close();
  return 0;
  tmp = "创建 用户 @t t";
  x.read(tmp);
  tmp = "设置 视图 数据库 表 @DB1 TB1 t 1 2 3 4";
  x.read(tmp);
  tmp = "删除 列 数据库 表 @DB1 TB1 2";
  x.read(tmp);
  return 0;
  tmp = "删除 行 数据库 表 @DB1 TB1 2";
  x.read(tmp);
  tmp = "选择 数据库 @DB1";
  x.read(tmp);
  tmp = "删除 行 表 @TB1 4";
  x.read(tmp);
  tmp = "选择 表 @TB1";
  x.read(tmp);
  tmp = "删除 行 @5";
  x.read(tmp);
  tmp = "显示 数据库 表 @DB1 TB1 12";
  x.read(tmp);
  return 0;
}
