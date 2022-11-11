/*
 * @Description  : 文件操作类_file的声明
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:03:15
 * @LastEditTime : 2022-11-11 21:58:15
 */
#ifndef _FILE_
#define _FILE_
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _FSTREAM_
#define _FSTREAM_
#include <fstream>
#endif
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
/**
 * @brief
 * 封装一些对于文件的函数的类。包括创建删除文件。文件的读写。以及读写锁的实现
 */
class _file : public _super {
 protected:
  /**
   * @brief 以App的方式写入字符串
   * @param vector<string>& array 数据写入数据库
   * @return True写入正确,False 写入失败
   */
  bool write(const std::vector<std::string>& array);
  /**
   * @brief
   * 判断文件是否存在打开,若没打开或者希望关闭则返回False，若文件打开则判断writebuff是否打开,若没有打开则打开，若已经打开，则啥也不干
   * @param bool need 希望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
   */
  bool writeBuffOpen(bool need);
  /**
   * @brief
   * 判断文件是否存在打开,若没打开或者希望关闭则返回False，若文件打开则判断readbuff是否打开,若没有打开则打开，若已经打开，则啥也不干
   * @param bool need 期望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
   */
  bool readBuffOpen(bool need);

 public:
   /**
   * @brief 真实路径
   * @return {std::string} 返回真实路径
   */
  std::string returnTruePath();
  /**
   * @brief 创建_file默认的文件
   * @return True表示文件创造成功，False表示文件创造失败
   */
  virtual bool create();
  /**
   * @brief 删除_file中的默认文件
   * @return 如果删除正常，则返回True，否则返回False
   */
  virtual bool remove();
  /**
   * @brief 判断是否存在
   * @return 存在则返回True，否则返回False
   */
  virtual bool isExist();
  /**
   * @brief 打开的数量
   * @return  数量
   */
  virtual int returnCount();
  /**
   * @brief 删除文件
   * @param  string Name 文件名
   * @param type style 类型
   * @return 正常删除返回True，否则返回False
   */
  bool static remove(std::string Name, type style);
  /**
   * @brief 返回类中默认的writeFileBuff，用来操作
   * @return <const ofstream&> 返回writeFileBuff
   */
  const std::ofstream& returnWriteFileBuff();
  /**
   * @brief 返回类中默认的readFileBuff，用来操作
   * @return <const ifstream&> 返回readFileBuff
   */
  const std::ifstream& returnReadFileBuff();
  /**
   * @brief 以App的方式写入字符串
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool write(const std::string& str);
  /**
   * @brief 以行的形势读出数据
   * @param vector<string>& ret 保存的方式
   * @return 读完或文件不存在返回False，否则返回True
   */
  bool readline(std::vector<std::string>& ret);

  /**
   * @brief 构造函数
   * @param string Name 名
   * @param type style 类型
   */
  _file(std::string Name, type style);

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
   * @param string Name 名字
   * @param vector<string>& array 数据写入数据库
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(std::string Name,
                        const std::vector<std::string>& array);

  /**
   * @brief <static> 以App的方式写入字符串
   * @param  string Name 名字
   * @param  string& str 单个字符串
   * @return  True写入正常，False写入失败
   */
  bool static writeFile(std::string Name, const std::string& str);
  /**
   * @brief <static> 创建
   * @param string Name 需要创建的名字
   * @param type stype 需要创建的类型
   * @return True表示文件创造成功，False表示文件创造失败
   */
  bool static create(std::string Name, type style);

 private:
  // writeFileBuff是写文件buff指针
  std::ofstream writeFileBuff;
  // readFileBuff是读文件buff指针
  std::ifstream readFileBuff;
  //文件类型
  type style;
  //当前打开的文件数总数
  static int count;
  std::string truePath;
};
#endif