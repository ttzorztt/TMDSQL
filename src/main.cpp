/**
 * @file main.cpp
 * @brief 主函数的实现
 * @author TMD
 * @version 1.3
 * @date 2022-11-01
 */
#ifndef _IOSTREAM_
#define _IOSTREAM_
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
		_file table("./data/SQL/init");
		table.create();
		vvstring tmpdata = {		
			{"登录","@root","root"},
			{"创建","数据库","@DB1"},
			{"创建","数据库","表,@DB1","TB1"},
			{"创建","数据库","表,@DB1","TB2"},
			{"创建","数据库","表,@DB1","TB3"},
			{"创建","数据库","表,@DB1","TB4"},
			{"插入","数据库","表","@DB1","TB1","1","2","3","4","5","6","7","8"},
			{"插入","数据库","表","@DB1","TB1","9","10","11","12","13","14","15"},
			{"插入","数据库","表","@DB1","TB1","16","17","18","19","20","21","22"},
			{"插入","数据库","表","@DB1","TB1","23","24","25","26","27","28","29"},
			{"插入","数据库","表","@DB1","TB2","1","2","3","4","5","6","7","8"},
			{"插入","数据库","表","@DB1","TB2","9","10","11","12","13","14","15"},
			{"插入","数据库","表","@DB1","TB2","16","17","18","19","20","21","22"},
			{"插入","数据库","表","@DB1","TB2","23","24","25","26","27","28","29"},
			{"插入","数据库","表","@DB1","TB3","1","2","3","4","5","6","7","8"},
			{"插入","数据库","表","@DB1","TB3","9","10","11","12","13","14","15"},
			{"插入","数据库","表","@DB1","TB3","16","17","18","19","20","21","22"},
			{"插入","数据库","表","@DB1","TB3","23","24","25","26","27","28","29"},
			{"插入","数据库","表","@DB1","TB4","1","2","3","4","5","6","7","8"},
			{"插入","数据库","表","@DB1","TB4","9","10","11","12","13","14","15"},
			{"插入","数据库","表","@DB1","TB4","16","17","18","19","20","21","22"},
			{"插入","数据库","表","@DB1","TB4","23","24","25","26","27","28","29"},
			{"查询","数据库","表","@DB1","TB1","3"},
			{"查询","数据库","表","@DB1","TB1","2"},
		};
		table.writeAnyLine(tmpdata,type_mode::WRITEBUFF_MODE_TRUNC);
	}
	if (access("./data/User", F_OK)) {
		_super::createDir("./data/User");
		_file table("./data/User/pd");
		table.create();
		table.write({"root", "root", "0"}, type_mode::WRITEBUFF_MODE_APP);
	}
	if (access("./data/Log", F_OK)) {
		_super::createDir("./data/Log");
	}
}
int main1(int argc, char const* argv[]) {
	init();
	shell x;
	string tmp = "执行 @s";
	Log::open();
	char ch;
	while(1){
		getline(cin, tmp);
		if(ch == '\n'){
			menuOutput::printPower(x.ReturnPower());
			break;
		}
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
return 0;
	tmp = "查询 数据库 表 @DB TB 1";
	x.read(tmp);

	tmp = "查询 数据库 表 @DB TB 2";
	x.read(tmp);
	tmp = "查询 数据库 表 @DB TB 3";
	x.read(tmp);
	tmp = "查询 数据库 表 @DB TB 4";
	x.read(tmp);
	return 0;
	tmp = "选择 数据库 @DB1";
	x.read(tmp);

	tmp = "插入 表 @TB1 姓名 性别 年龄";
	x.read(tmp);

	tmp = "插入 表 @TB1 张三 男 11";
	x.read(tmp);

	tmp = "插入 表 @TB1 王五 男 10";
	x.read(tmp);
	tmp = "插入 表 @TB1 李四 女 100";

	x.read(tmp);

	tmp = "显示 表 @TB1 3";

	x.read(tmp);
	tmp = "设置 视图 表 @TB1 root 0 2";

	x.read(tmp);
	tmp = "显示 表 @TB1 3";

	x.read(tmp);

	return 0;
}
