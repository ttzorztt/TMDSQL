/*
 * @Description  : 文件操作类_file的声明
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:03:15
 * @LastEditTime : 2022-11-06 19:52:24
 */
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _FSTREAM_
#define _FSTREAM_
#include <fstream>
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
/**
 * @brief
 * 封装一些对于文件的函数的类。包括创建删除文件。文件的读写。以及读写锁的实现
 */
class _file {
 protected:
  /**
   * @brief 以App的方式写入字符串
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool writeFile(const string& str);

  /**
   * @brief 以App的方式写入字符串
   * @param vector<string>& array vector<string>的类型数据写入数据库
   * @return True写入正确,False 写入失败
   */
  bool writeFile(const vector<string>& array);
  /**
   * @brief 以行的形势读出数据
   * @return 将一行数据以空格的形式分开，并存储在vector中，然后返回。
   */
  vector<string> readline();

  /**
   * @brief 创建_file默认的文件
   * @return True表示文件创造成功，False表示文件创造失败
   */
  bool createFile();
  /**
   * @brief 删除_filezh中的默认文件
   * @return 如果删除正常，则返回True，否则返回False
   */
  bool deleteFile();
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
  /**
   * @brief
   * 判断文件是否存在并打开writebuff,若没有打开则打开，若已经打开，则啥也不干
   * @param bool need 希望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
   */
  bool writeBuffOpen(bool need);
  /**
   * @brief
   * 判断文件是否存在打开readbuff,若没有打开则打开，若已经打开，则啥也不干
   * @param bool need 期望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
   */
  bool readBuffOpen(bool need);

  // filePath是_file超类的文件路径
  string name;
  // path 是_file的文件路径
  string path;
  // writeFileBuff是写文件buff指针
  ofstream writeFileBuff;
  // readFileBuff是读文件buff指针
  ifstream readFileBuff;
  // lockPath是加锁文件
  string lockPath;

 public:
  /**
   * @brief 判断_file默认文件是否存在
   * @return 若文件存在则返回True，否则返回False;
   */
  virtual bool isExist();
  /**
   * @brief <static> 删除指定文件
   * @param string Path 删除文件所在路径
   * @return 如果正常删除，则返回True，否则返回False
   */
  bool static deleteFile(string Path);

  /**
   * @brief 构造函数，传入文件路径
   * @param string name 文件路径
   */
  _file(string name);

  /**
   * @brief 拷贝构造函数
   * @param  _file& _copy 拷贝数据
   * @return
   */
  _file(_file& _copy);
  /**
   * @brief 析构函数，释放并关闭文件
   */
  ~_file();
  /**
   * @brief <static> 以App的方式写入字符串
   * @param string Path 路径
   * @param vector<string>& array 数据写入数据库
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(string Path, const vector<string>& array);
  /**
   * @brief <static> 以App的方式写入字符串
   * @param string Path 路径
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(string Path, const string& str);
  /**
   * @brief <static> 判断指定文件是否存在
   * @param string name 文件路径
   * @return 若文件存在则返回True，否则返回False;
   */
  bool static isExist(string name);
  /**
   * @brief <static> 创建指定文件
   * @param string path 需要创建的文件名字
   * @return True表示文件创造成功，False表示文件创造失败
   */
  bool static createFile(string name);
  /**
   * @brief 返回文件的相对路径
   * @return 返回文件的相对路径
   */
  inline string returnFilePath();
  /**
   * @brief 返回文件的名字
   * @return  返回文件的名字
   */
  inline string returnFileName();
};