/*
 * @Description  : 日志管理类的实现
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:15
 * @LastEditTime : 2023-01-12 23:02:09
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
_file Log::file(_PathForLog + "Log");
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
void Log::LogForSelectDatabase(std::string& UserName,
                               TYPE_POWER& op,
                               std::string DBID,
                               TYPE_ERROR_CASE errorCase) {
  std::string Time = nowTime();
  if(errorCase == 无){
    file.write("[V]   " + Time,type_mode::WRITEBUFF_MODE_APP);
    file.write(UserName + "-> 选择 数据库 " + DBID,type_mode::WRITEBUFF_MODE_APP);
  }else{
    file.write("[X]   " + Time,type_mode::WRITEBUFF_MODE_APP);
    file.write(UserName + "-> 选择 数据库 " + DBID,type_mode::WRITEBUFF_MODE_APP);
    // file.write()
  }
}
