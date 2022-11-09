/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:04
 * @LastEditTime : 2022-11-09 19:03:19
 */
#ifndef _DIR_
#define _DIR_
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
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
   * @brief 删除默认目录 dirPath
   * @return 如果删除正常，则返回True，否则返回False
   */
  virtual bool remove();

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
   * @brief dir类中的构造函数，
   * @param string dirPath 目录路径
   * @return
   */
  _dir(std::string dirPath);
  /**
   * @brief 拷贝构造函数
   * @param  _dir& copy 拷贝值
   * @return
   */
  _dir(_dir& copy);
  /**
   * @brief <static>创建目录
   * @param  string dirName 创建目录名
   * @return 正确创建则返回true，否则返回false
   */
  bool static create(std::string dirName);
  /**
   * @brief <static>删除目录
   * @param string Path 删除目录的路径
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool static remove(std::string Path);
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @param string Path 表对象
   * @return 以vector的形式返回
   */
  std::vector<std::string> static openDirReturnFileName(std::string Path);
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @return 以vector的形式返回
   */
  std::vector<std::string> openDirReturnFileName();
  private:
  // 记录由_dir打开的文件
  int static count;
};
#endif