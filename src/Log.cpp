/*
 * @Description  : 日志管理类的实现
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:15
 * @LastEditTime : 2023-01-12 11:48:23
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
Log::Log() : _file(_PathForLog + "Log") {
}
Log::~Log() {}
void Log::nowTime(revstring dataAndTime) {
  time_t nowTime = time(NULL);
  struct tm* t = localtime(&nowTime);
  vstring ret(6);
  ret[0] = std::to_string(t->tm_year + 1900);
  ret[1] = std::to_string(t->tm_mon + 1);
  ret[2] = std::to_string(t->tm_mday);
  ret[3] = std::to_string(t->tm_hour);
  ret[4] = std::to_string(t->tm_min);
  ret[5] = std::to_string(t->tm_sec);
}
