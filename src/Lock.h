/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:12:54
 * @LastEditTime : 2022-11-08 16:08:29
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class Lock : public _super {
 private:
  //当前打开的锁的总数的数量
  static int count;
  //当前打开的文件锁的数量
  static int fileCount; 
  //当前打开数据库锁的数量
  static int databaseCount;
  //类型
  type style;
 public:
 virtual type returnType();
  /**
   * @brief 构造函数
   * @param  Table table 表
   * @return
   */
  Lock(Table table);
  /**
   * @brief 构造函数
   * @param  DataBase database 数据库
   * @return 
   */
  Lock(DataBase database);
  /**
   * @brief 拷贝构造
   * @param  Lock& copy 拷贝值
   * @return
   */
  Lock(Lock& copy);
  /**
   * @brief 析构函数
   * @return
   */
  ~Lock();
  /**
   * @brief 锁的数量
   * @return 返回当前锁的数量
   */
  virtual int returncount();
  /**
   * @brief 文件锁的数量
   * @return 返回文件锁的数量
   */
  int static returnFileCount();
  /**
   * @brief 数据库锁的数量
   * @return 返回数据库锁的数量
   */
  int static returnDatabaseCount();
  /**
   * @brief 加锁
   * @param string Path 文件路径
   * @param type style 文件类型
   * @return 加锁成功则返回True，并意味着当前没有读写冲突，
   * 加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool static add(std::string Path,type style);
  /**
   * @brief 删锁
   * @param string Path 文件路径
   * @param type style 文件类型
   * @return 删锁成功则返回True，否则返回False。
   */
  bool static remove(std::string Path,type style);
  /**
   * @brief 加锁
   * @return
   * 加锁成功则返回True，并意味着当前没有读写冲突，加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool add();
  /**
   * @brief 删锁
   * @return 删锁成功则返回True，否则返回False。
   */
  bool remove();
  /**
   * @brief 加锁
   * @param  Table table
   * @return
   * 加锁成功则返回True，并意味着当前没有读写冲突，加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool static add(Table table);
  /**
   * @brief 删锁
   * @param  Table table
   * @return 删锁成功则返回True，否则返回False。
   */
  bool static remove(Table table);
  /**
   * @brief 加锁
   * @param  DataBase database 数据库
   * @return  加锁成功则返回True，并意味着当前没有读写冲突，加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool static add(DataBase database);
  /**
   * @brief 删锁
   * @param  DataBase database 数据库
   * @return  删锁成功则返回True，否则返回False。
   */
  bool static remove(DataBase database);
};