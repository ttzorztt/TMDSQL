/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:12:10
 * @LastEditTime : 2022-11-09 21:09:17
 */
#ifndef _TABLE_
#define _TABLE_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
using namespace std;
/**
 * @brief 封装表操作
 */
class Table : public _file {
 private:
 public:
   virtual bool create();
  virtual bool remove();
  virtual int returnCount();
  virtual bool isExist();
  /**
   * @brief 构造函数
   * @param  string stableName 表名
   * @return
   */
  Table(string stableName);
  /**
   * @brief 构造函数
   * @param  DataBase database 数据库对象
   * @param  string stableName 表名
   * @return
   */
  Table(DataBase database, string stableName);
  void createIndex();
  ~Table();
private:
type style;
//记录打开表的个数
 int static count;
};

#endif