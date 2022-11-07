/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:12:54
 * @LastEditTime : 2022-11-07 22:46:49
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class Lock : public _super {
 private:
  //当前打开的锁文件的数量
  static int count;
 public:
  /**
   * @brief 构造函数
   * @param  string Path 文件路径
   * @return  
   */
  Lock(std::string Path);
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
   * @brief 锁文件的数量
   * @return 返回当前锁的数量
   */
  virtual int returncount();
  /**
   * @brief 加锁
   * @return 加锁成功则返回True，并意味着当前没有读写冲突，
   * 加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool addLock();
  /**
   * @brief 删锁
   * @return 删锁成功则返回True，否则返回False。
   */
  bool removeLock();
};