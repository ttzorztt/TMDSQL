/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:08
 * @LastEditTime : 2022-11-07 22:19:36
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
 public:
  virtual bool create();
  virtual bool remove();
  virtual int returnCount();
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
   * @brief 拷贝构造函数
   * @param  super& copy 拷贝值
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   * @return
   */
  _super(_super& copy);
  /**
   * @brief 构造函数
   * @param  string name 名字
   * @param  string path 路径
   * @return
   */
  _super(std::string name, std::string path);
  ~_super();
  /**
   * @brief <static> 返回目录中所有文件名字，即数据库中表名
   * @param string dirPath dir的路径
   * @return 以vector的形式返回
   */
  std::vector<std::string> static openDirReturnFileName(std::string dirPath);
  /**
   * @brief <static> 以App的方式写入字符串
   * @param string Path 路径
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(std::string Path, const std::string& str);
  /**
   * @brief <static> 删除指定文件
   * @param string Path 删除文件所在路径
   * @return 如果正常删除，则返回True，否则返回False
   */
  bool static deleteFile(std::string Path);
  /**
   * @brief <static> 计算Path中的文件名，并返回
   * @param  string Path 待计算路径
   * @return  文件名
   */
  std::string static computeName(std::string Path);
  /**
   * @brief <static> 判断指定文件或目录是否存在
   * @param string Path 路径
   * @param type style 类型
   * @return 若存在则返回True，否则返回False;
   */
  bool static isExist(std::string Path,type style);
};