/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:04
 * @LastEditTime : 2022-11-07 15:17:03
 */
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
class _dir: public _super {
 public:
  /**
   * @brief 返回路径
   * @return <string> 返回DirPath
   */
  virtual std::string returnPath();
  /**
   * @brief 返回名字
   * @return <string> 返回DirName
   */
  virtual std::string returnName();
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
  bool static createDir(std::string dirName);
  /**
   * @brief <static>删除目录
   * @param string Path 删除目录的路径
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool static deleteDir(std::string Path);

  /**
   * @brief <static> 判断指定文件是否存在
   * @param string name 文件路径
   * @return 若文件存在则返回True，否则返回False;
   */
  bool static isExist(std::string name);
  std::string dirPath;// dir的路径
  std::string dirName; // dir的名字
  /**
   * @brief 删除默认目录 dirPath
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool deleteDir();
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @return 以vector的形式返回
   */
  std::vector<std::string> openDirReturnFileName();
};