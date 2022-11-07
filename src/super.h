/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:08
 * @LastEditTime : 2022-11-07 11:40:17
 */
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <dirent.h>
#endif
#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_
#include <sys/types.h>
#endif
#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_
#include <sys/stat.h>
#endif
#ifndef _UNISTD_H_
#define _UNISTD_H_
#include <unistd.h>
#endif
// 封装一些文件或目录类型
enum type {
  _TYPE_FILE,   //普通文件，即表
  _TYPE_DIR,    //目录，即数据库
  _TYPE_INDEX,  // 索引文件
  _TYPE_LOCK,   // 锁文件
};
/**
 * @brief 维护一些基础静态函数
 */
class _super {
 protected:
  std::string name;  //名字
  std::string path;  //相对路径
  type style;        //类型
 public:
  virtual bool isExist();
  virtual bool create();
  /**
   * @brief 返回名字
   * @return 返回名字
   */
  std::string returnName();
  /**
   * @brief 返回路径
   * @return 返回路径
   */
  std::string returnPath();
  /**
   * @brief 返回类型
   * @return 返回类型
   */
  type returnType();

  /**
   * @brief 构造函数
   * @param string Path 文件相对路径
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   * @return
   */
  _super(std::string Path, type style);
  /**
   * @brief 构造函数
   * @param  string& Path 文件相对路径
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   * @return
   */
  _super(std::string& Path, type style);
  /**
   * @brief 拷贝构造函数
   * @param  super& copy 拷贝值
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   * @return
   */
  _super(_super& copy);
  
  ~_super();
};