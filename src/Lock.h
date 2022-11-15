/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:12:54
 * @LastEditTime : 2022-11-14 10:18:45
 */
#ifndef _LOCK_
#define _LOCK_
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
  static int tableCount;
  //当前打开数据库锁的数量
  static int databaseCount;
  //类型
  type style;

 public:
  /**
   * @brief 创建
   * @return  创建正常则返回True，否则返回False
   */
  virtual bool create();
  /**
   * @brief 删除
   * @return  删除正常则返回True，否则返回False
   */
  virtual bool remove();
  /**
   * @brief 返回static 的count
   * @return count
   */
  virtual int returnCount();
  /**
   * @brief 是否存在
   * @return  存在返回True，否则返回False
   */
  virtual bool isExist();
  /**
   * @brief <static> 是否存在
   * @param  string name 名字
   * @param  type style 类型
   * @return  存在则返回True，否则返回False
   */
  bool static isExist(std::string name, type style);
  /**
   * @brief 构造函数
   * @param  string name 名字
   * @param type style 类型
   * @return
   */
  Lock(std::string name, type style);
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
   * @brief 新建锁，增加count
   * @return
   */
  void newLockAddCount();
  /**
   * @brief 表锁的数量
   * @return 返回表锁的数量
   */
  int static returnTableCount();
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
  bool static add(std::string Path, type style);
  /**
   * @brief 删锁
   * @param string Path 文件路径
   * @param type style 文件类型
   * @return 删锁成功则返回True，否则返回False。
   */
  bool static remove(std::string Path, type style);
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
   * @return
   * 加锁成功则返回True，并意味着当前没有读写冲突，加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool static add(DataBase database);
  /**
   * @brief 删锁
   * @param  DataBase database 数据库
   * @return  删锁成功则返回True，否则返回False。
   */
  bool static remove(DataBase database);
};
#endif