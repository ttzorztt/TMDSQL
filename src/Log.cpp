/*
 * @Description  : 日志管理类的实现
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:15
 * @LastEditTime : 2023-01-13 17:41:22
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
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
_file Log::file(_PathForLog + "Log");
std::unordered_map<TYPE_ERROR_CASE, std::string> Log::EC = {
    {顺利执行, "顺利执行"},
    {登录帐号错误, "登录帐号错误"},
    {登录帐号已存在, "登录帐号已存在"},
    {登录密码错误, "登录密码错误"},
    {无法选择不存在的数据库, "无法选择不存在的数据库"},
    {无法选择不存在的表, "无法选择不存在的表"}};
std::unordered_map<TYPE_POWER, std::string> Log::TP = {{NONE, "未登录"},
                                                       {NORMAL, "普通用户"},
                                                       {ROOT, "超级管理员"},
                                                       {Manager, "管理员"}};
Log::Log() {}
Log::~Log() {}
std::string Log::nowTime() {
  time_t now = time(NULL);
  struct tm* t = localtime(&now);
  return "[" + std::to_string(t->tm_year + 1900) + "." +
         std::to_string(t->tm_mon + 1) + "." + std::to_string(t->tm_mday) +
         "] (" + std::to_string(t->tm_hour) + ":" + std::to_string(t->tm_min) +
         ":" + std::to_string(t->tm_sec) + ")";
}
void Log::open() {
  file.write(nowTime() + " 登录系统", type_mode::WRITEBUFF_MODE_APP);
}
void Log::close() {
  file.write("", type_mode::WRITEBUFF_MODE_APP);
  file.write(nowTime() + " 登出系统", type_mode::WRITEBUFF_MODE_APP);
  file.write("", type_mode::WRITEBUFF_MODE_APP);
}
void Log::inputNowTime(TYPE_ERROR_CASE& errorCase) {
  time_t now = time(NULL);
  struct tm* t = localtime(&now);
  std::string tmp;
  if (!errorCase) {
    tmp = "< V >";
  } else {
    tmp = "< X >";
  }
  file.write("", type_mode::WRITEBUFF_MODE_APP);
  file.write(tmp + " " + nowTime(), type_mode::WRITEBUFF_MODE_APP);
  file.write(EC[errorCase], type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSelectDatabase(std::string& UserName,
                               TYPE_POWER& op,
                               std::string& DBID,
                               TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "}" + " => 选择 数据库\"" + DBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForSelectDatabaseTable(std::string& UserName,
                                    TYPE_POWER& op,
                                    std::string& DBID,
                                    std::string& TBID,
                                    TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 选择 数据库\"" + DBID + "\" 表\"" +
                 TBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShow(std::string& UserName,
                     TYPE_POWER& op,
                     TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 显示",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowAllDatabase(std::string& UserName,
                                TYPE_POWER& op,
                                TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 显示 数据库",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowDatabase(std::string& UserName,
                             TYPE_POWER& op,
                             std::string& DBID,
                             TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 显示 数据库\"" + DBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForShowDatabaseTable(std::string& UserName,
                                  TYPE_POWER& op,
                                  std::string& DBID,
                                  std::string& TBID,
                                  TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 显示 数据库\"" + DBID + "\" 表\"" +
                 TBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForExit(std::string& UserName,
                     TYPE_POWER& op,
                     TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 退出",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForLogin(std::string& UserName,
                      TYPE_POWER& op,
                      std::string& LoginID,
                      std::string& LoginPassword,
                      TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 登录 用户\"" + LoginID +
                 "\" 密码\"" + LoginPassword + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateUser(std::string& UserName,
                           TYPE_POWER& op,
                           std::string& ID,
                           std::string& Pd,
                           TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 创建 普通用户\"" + ID +
                 "\" 密码\"" + Pd + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateManager(std::string& UserName,
                              TYPE_POWER& op,
                              std::string& ID,
                              std::string& Pd,
                              TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 创建 管理员\"" + ID + "\" 密码\"" +
                 Pd + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}
void Log::LogForCreateDatabase(std::string& UserName,
                               TYPE_POWER& op,
                               std::string& DBID,
                               TYPE_ERROR_CASE errorCase) {
  inputNowTime(errorCase);
  file.write(TP[op] + "{" + UserName + "} => 创建 数据库\"" + DBID + "\"",
             type_mode::WRITEBUFF_MODE_APP);
}