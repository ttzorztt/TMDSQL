/*
 * @Description  : 日志管理
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:01
 * @LastEditTime : 2023-01-12 11:44:31
 */
#ifndef _LOG_
#define _LOG_

#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
class Log : public _file {
 private:
  void nowTime(revstring dataAndTime);
 public:
  Log();
  Log& operator=(const Log& tmp) = delete;
  Log(const Log& tmp) = delete;
  ~Log();
  //   void readChoose(std::string commandAndInputData);
};

#endif