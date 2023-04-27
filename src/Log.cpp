/**
 * @file Log.cpp
 * @brief 日志管理的实现
 * @author TMD
 * @version 1.3
 * @date 2023-01-12
 */
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _TIME_
#define _TIME_
#include <time.h>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
std::unordered_map<TYPE_ERROR_CASE, std::string> Log::EC = {
	{顺利执行, "顺利执行"},
	{键入不存在的关键字, "键入不存在的关键字"},
	{键入违规字符, "键入违规字符"},
	{登录帐号错误, "登录帐号错误"},
	{登录密码错误, "登录密码错误"},
	{无法选择不存在的数据库, "无法选择不存在的数据库"},
	{未登录拒绝执行, "未登录拒绝执行"},
	{未选择数据库越级选择表, "未选择数据库越级选择表"},
	{已选择的数据库中不存在目标表, "已选择的数据库中不存在目标表"},
	{普通用户违规操作, "普通用户违规操作"},
	{第一个关键字错误, "第一个关键字错误"},
	{第二个关键字错误, "第二个关键字错误"},
	{SQL文件未找到, "SQL文件未找到"},
	{编译错误, "编译错误"},
	{创建已存在的用户, "创建已存在的用户"},
	{管理员违规操作, "管理员违规操作"},
	{创建已存在的管理员, "创建已存在的管理员"},
	{表已存在无法创建, "表已存在无法创建"},
	{数据库已存在无法创建, "数据库已存在无法创建"},
	{数据库不存在无法删除, "数据库不存在无法删除"},
	{目标用户不存在无法删除, "目标用户不存在无法删除"},
	{目标管理员不存在无法删除, "目标管理员不存在无法删除"},
	{表不存在无法查找数据, "表不存在无法查找数据"},
	{输入非确定指令取消, "输入非确定指令取消"},
	{数据库不存在无法插入数据, "数据库不存在无法插入数据"},
	{表不存在无法插入数据, "表不存在无法插入数据"},
	{数据库不存在无法查找数据, "数据库不存在无法查找数据"},
	{表不存在无法显示数据, "表不存在无法显示数据"},
	{数据库不存在无法显示数据, "数据库不存在无法显示数据"},
	{未选择表, "未选择表"}};
std::unordered_map<TYPE_POWER, std::string> Log::TP = {{NONE, "未登录"},
	{NORMAL, "普通用户"},
	{ROOT, "超级管理员"},
	{Manager, "管理员"}};
_file Log::file(nowData(), type::_TYPE_LOG);
void Log::LogForCompileError(std::string UserName,
		TYPE_POWER op,
		std::string _data,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "}" + " => " + _data,
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForError(std::string UserName,
		TYPE_POWER op,
		vCID command,
		revstring data,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	std::string tmp;
	if (command.size() != 0) {
		for (auto& CI : command) {
			tmp += HashMapCIDToString[CI] + " ";
		}
		for (std::string& str : data) {
			tmp += str + " ";
		}
	}
	file.write(TP[op] + "{" + UserName + "}" + " => " + tmp,
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCompileError(std::string UserName,
		TYPE_POWER op,
		revstring commandAndData,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	std::string tmp;
	for (std::string& str : commandAndData) {
		tmp += str + " ";
	}
	file.write(TP[op] + "{" + UserName + "}" + " => " + tmp,
			type_mode::WRITEBUFF_MODE_APP);
}

Log::Log() {}
Log::~Log() {}
std::string Log::nowData() {
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	return (std::to_string(t->tm_year + 1900) + "." +
			std::to_string(t->tm_mon + 1) + "." + std::to_string(t->tm_mday));
}
std::string Log::nowDataTime() {
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	std::string FileName = nowData();
	_file nowfile(FileName, type::_TYPE_LOG);
	if (!nowfile.isExist() || nowfile.truePath != file.truePath) {
		file.resetPath(FileName, type::_TYPE_LOG);
	}
	return "[" + FileName + "] (" + std::to_string(t->tm_hour) + ":" +
		std::to_string(t->tm_min) + ":" + std::to_string(t->tm_sec) + ")";
}
void Log::open() {
	file.write(nowDataTime() + " 登录系统", type_mode::WRITEBUFF_MODE_APP);
}
void Log::close() {
	file.write("", type_mode::WRITEBUFF_MODE_APP);
	file.write(nowDataTime() + " 登出系统", type_mode::WRITEBUFF_MODE_APP);
	file.write("", type_mode::WRITEBUFF_MODE_APP);
}
void Log::inputNowTime(TYPE_ERROR_CASE& errorCase) {
	std::string DataTime = nowDataTime();
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	std::string tmp;
	if (!errorCase) {
		tmp = "< V >";
	} else {
		tmp = "< X >";
	}
	file.write("", type_mode::WRITEBUFF_MODE_APP);
	file.write(tmp + " " + DataTime, type_mode::WRITEBUFF_MODE_APP);
	file.write(EC[errorCase], type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSelectDatabase(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "}" + " => 选择 数据库\"" + DBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForExecuteSQL(std::string UserName,
		TYPE_POWER op,
		std::string SQLPath,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "}" + " => 执行 \"" + SQLPath + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSelectDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 选择 数据库\"" + DBID + "\" 表\"" +
			TBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShow(std::string UserName,
		TYPE_POWER op,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 显示",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowAllDatabase(std::string UserName,
		TYPE_POWER op,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 显示 数据库",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowDatabase(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 显示 数据库\"" + DBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 显示 数据库\"" + DBID + "\" 表\"" +
			TBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForExit(std::string UserName,
		TYPE_POWER op,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 退出",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForLogin(std::string UserName,
		TYPE_POWER op,
		std::string LoginID,
		std::string LoginPassword,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 登录 用户\"" + LoginID +
			"\" 密码\"" + LoginPassword + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateUser(std::string UserName,
		TYPE_POWER op,
		std::string ID,
		std::string Pd,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 创建 普通用户\"" + ID +
			"\" 密码\"" + Pd + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateManager(std::string UserName,
		TYPE_POWER op,
		std::string ID,
		std::string Pd,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 创建 管理员\"" + ID + "\" 密码\"" +
			Pd + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateDatabase(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 创建 数据库\"" + DBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 创建 数据库\"" + DBID + "\" 表\"" +
			TBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteRowDatabaseTable(std::string UserName, TYPE_POWER op,
                                       std::string DBID, std::string TBID,
                                       std::string Row,
                                       TYPE_ERROR_CASE errorCase) {
  file.write(TP[op] + "{" + UserName + "} => 删除 行\"" + Row + "\" 数据库\"" +
                 DBID + "\" 表\"" + TBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteColDatabaseTable(std::string UserName, TYPE_POWER op,
                                       std::string DBID, std::string TBID,
                                       std::string Cow,
                                       TYPE_ERROR_CASE errorCase) {
  file.write(TP[op] + "{" + UserName + "} => 删除 列\"" + Cow + "\" 数据库\"" +
                 DBID + "\" 表\"" + TBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteDatabase(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 删除 数据库\"" + DBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 删除 数据库\"" + DBID + "表\"" +
			TBID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteUser(std::string UserName,
		TYPE_POWER op,
		std::string UID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 删除 普通用户\"" + UID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForDeleteManager(std::string UserName,
		TYPE_POWER op,
		std::string MID,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 删除 管理员\"" + MID + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForInsertDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		revstring data,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	std::string tmp = data[0];
	int size = data.size();
	for (int a = 1; a < size; ++a) {
		tmp += " " + data[a];
	}
	file.write(TP[op] + "{" + UserName + "} => 插入 数据库\"" + DBID + "\" 表\"" +
			TBID + "\"" + tmp + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForFindDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		std::string Index,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 查询 数据库\"" + DBID + "\" 表\"" +
			TBID + "\" " + Index,
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSetIndexDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		std::string index,
		TYPE_ERROR_CASE errorCase) {
	inputNowTime(errorCase);
	file.write(TP[op] + "{" + UserName + "} => 设置 索引 数据库\"" + DBID +
			"\" 表\"" + TBID + "\" 索引\"" + index + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSetViewDatabaseTable(std::string UserName,
		TYPE_POWER op,
		std::string DBID,
		std::string TBID,
		std::string operatorUserName,
		vstring viewData,
		TYPE_ERROR_CASE errorCase  ) {
	inputNowTime(errorCase);
	std::string tmp = viewData[0];
	int size = viewData.size();
	for (int a = 1; a < size; ++a) {
		tmp += " " + viewData[a];
	}
	file.write(TP[op] + "{" + UserName + "} => 设置 视图 数据库\"" + DBID +
			"\" 表\"" + TBID + "\" 用户\"" + operatorUserName +
			"\" 视图列: \"" + tmp + "\"",
			type_mode::WRITEBUFF_MODE_APP);
}
