/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:04
 * @LastEditTime : 2022-11-06 16:05:13
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
using namespace std;
class _dir {
 public:
  /**
   * @brief dir类中的构造函数，
   * @param string dirPath 目录路径
   * @return
   */
  _dir(string dirPath);
  /**
   * @brief <static> 返回目录中所有文件名字，即数据库中表名
   * @param string dirPath dir的路径
   * @return 以vector的形式返回
   */
  vector<string> static openDirReturnFileName(string dirPath);
  /**
   * @brief <static>创建目录
   * @param  string dirName 创建目录名
   * @return 正确创建则返回true，否则返回false
   */
  bool static createDir(string dirName);
  /**
   * @brief <static>删除目录
   * @param string Path 删除目录的路径
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool static deleteDir(string Path);
  /**
   * @brief 返回路径
   * @return 返回DirPath
   */
  string returnDirPath();
  /**
   * @brief <static> 判断指定文件是否存在
   * @param string name 文件路径
   * @return 若文件存在则返回True，否则返回False;
   */
  bool static isExist(string name);

  string dirPath;
  /**
   * @brief 删除默认目录 dirPath
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool deleteDir();
  /**
   * @brief 返回默认目录中所有文件名字，即数据库中表名
   * @return 以vector的形式返回
   */
  vector<string> openDirReturnFileName();
};