/*
 * @Description  : 日志管理
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:01
 * @LastEditTime : 2023-01-12 22:53:57
 */
#ifndef _LOG_
#define _LOG_

#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
class Log {
 private:
  static _file file;
  /**
   * @brief 获取当前的日期和时间
   * @return  返回日期和时间
   */
  std::string static nowTime();
 public:
  Log();
  Log& operator=(const Log& tmp) = delete;
  Log(const Log& tmp) = delete;
  ~Log();
  /**
   * @brief 选择_数据库_@DBID
   * @param  string& UserName 用户名
   * @param  TYPE_POWER& op 权限
   * @param  string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForSelectDatabase(std::string& UserName,
                            TYPE_POWER& op,
                            std::string DBID,
                            TYPE_ERROR_CASE errorCase = 无);
};

#endif