/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:04
 * @LastEditTime : 2022-12-22 10:24:20
 */
#ifndef _DIR_
#define _DIR_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <dirent.h>
#endif
#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_
#include <sys/stat.h>
#endif
#ifndef _UNISTD_H_
#define _UNISTD_H_
#include <unistd.h>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
/**
 * @brief 封装一些对目录操作的函数
 */
class _dir : public _super {
 public:
  /**
   * @brief 创建
   * @return 正常创建返回True，否则返回False
   */
  virtual bool create();
  /**
   * @brief 删除默认目录 dirPath,只能删除空数据库
   * @return 如果删除正常，则返回True，否则返回False
   */
  virtual bool remove();

  /**
   * @brief 强制删除 (适用于非空目录)
   */
  void forceremove();
  /**
   * @brief <static> 强制删除 (适用于非空目录)
   * @param  string name 目录名称
   */
  void static forceremove(std::string name);
  /**
   * @brief 判断文件是否存在
   * @return 存在则返回True，否则返回False
   */
  virtual bool isExist();

  /**
   * @brief 由_dir打开的文件夹
   * @return 个数
   */
  virtual int returnCount();

  /**
   * @brief 返回type
   * @return  类型
   */
  virtual type returnType();
  /**
   * @brief dir类中的构造函数，
   * @param string dirName 目录名字
   * @param type style 类型
   * @return
   */
  _dir(std::string dirName,type style);
  /**
   * @brief 拷贝构造函数
   * @param  _dir& copy 拷贝值
   * @return
   */
  _dir(_dir& copy);
  /**
   * @brief <static>创建目录
   * @param  string truePath 创建目录名
   * @return 正确创建则返回true，否则返回false
   */
  bool static create(std::string truePath);
  /**
   * @brief <static>删除目录
   * @param string truePath 删除目录的路径，只能删除空数据库
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool static remove(std::string truePath);
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @param string truePath 目录
   * @return 以vector的形式返回
   */
  vstring static openDirReturnFileName(std::string truePath);
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @return 以vector的形式返回
   */
  vstring openDirReturnFileName();

 private:
  // 记录由_dir打开的文件
  int static count;
  type style;
};
#endif