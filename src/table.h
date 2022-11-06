/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:12:10
 * @LastEditTime : 2022-11-06 18:55:26
 */
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
class _table : protected _file {
 private:
 public:
  /**
   * @brief 构造函数
   * @param string databaseName 数据库名
   * @param  string stableName 表名
   * @return
   */
  _table(string datablaseName, string stableName);
  /**
   * @brief 构造函数
   * @param  DataBase database 数据库对象
   * @param  string stableName 表名
   * @return
   */
  _table(DataBase database, string stableName);
  /**
   * @brief 构造函数
   * @param  DataBase database 数据库对象
   * @param  _file tableName 表文件对象
   * @return
   */
  _table(DataBase database, _file tableName);
  ~_table();
};