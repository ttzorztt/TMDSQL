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
#ifndef _KEYBOARDINPUT_H_
#define _KEYBOARDINPUT_H_
#include "KeyboardInput.h"
#endif
using namespace std;

/**
 * @brief init database,
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
int main(int argc, char const* argv[]) {
	init();
	shell x;
	Log::open();
	KeyboardInput::read(x);
	return 0;
	while (1) {
#ifdef __WIN32__
		while(1){
			if(ch == '\n'){
				menuOutput::printPower(x.ReturnPower());
				break;
			}
			if(ch == '\b'){

			}
		}
#endif
#ifdef __linux__
		while(1){
		}
#endif
			/* getline(cin, tmp); */
			/* if (tmp == "") { */
			/*	menuOutput::printPower(x.ReturnPower()); */
			/*	continue; */
			/* } */
			/* if(tmp == "\b"){ */
			/*	std::cout << "2" << std::endl; */
			/* } */

		}
		Log::close();
		return 0;
	}

	int main1(int argc, char const* argv[]) {
		return 0;
		init();
		shell x;
		string tmp = "登录 @root root";
		x.read(tmp);

		tmp = "创建 数据库 @DB1";
		x.read(tmp);

		tmp = "创建 数据库 表 @DB1 TB1";
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
