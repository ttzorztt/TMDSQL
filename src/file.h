/*
 * @Description  : 文件操作类_file的声明
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:03:15
 * @LastEditTime : 2023-01-19 08:34:53
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

// 文件指针
/**
 * @brief
 * 封装一些对于文件的函数的类。包括创建删除文件。文件的读写。以及读写锁的实现
 */
class _file : public _super {
 public:
  /**
   * @brief 判断是否打开双buff
   * @param MODE mode 文件打开模式
   */
  void setOpenBuff(MODE mode);
  /**
   * @brief 输入PCB
   * @return
   */
  void inputPCBInformation();
  /**
   * @brief 以App的方式写入字符串
   * @param vstring array 数据写入数据库
   * @param mode type_mode 模式
   * @return True写入正确,False 写入失败
   */
  bool write(vstring array, type_mode mode);
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
   * @brief 删除文件
   * @param  string truePath 真实路径
   * @return 正常删除则返回True，否则返回False
   */
  bool static remove(std::string truePath);
  /**
   * @brief 返回类中默认的writeFileBuff，用来操作
   * @return <const ofstream&> 返回writeFileBuff
   */
  std::ofstream& returnWriteFileBuff();
  /**
   * @brief 返回类中默认的readFileBuff，用来操作
   * @return <const ifstream&> 返回readFileBuff
   */
  std::ifstream& returnReadFileBuff();
  /**
   * @brief 以App的方式写入字符串
   * @param string& str 写入的字符串
   * @param type_mode mode 写入方式
   * @return True写入正确,False 写入失败
   */
  bool write(const std::string str, type_mode mode);
  /**
   * @brief 以行的形势读出数据
   * @param revstring ret 保存的方式
   * @return 读完或文件不存在返回False，否则返回True
   */
  bool readline(revstring ret);

  /**
   * @brief 构造函数
   * @param string Name 名
   * @param type style 类型
   */
  _file(std::string Name, type style);

  /**
   * @brief 构造函数
   * @param  string TruePath 真实路径
   * @return
   */
  _file(std::string TruePath);
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
   * @brief 删除一行
   * @param  string index 索引
   * @return bool 是否删除
   */
  bool deleteLine(std::string index);

  /**
   * @brief <static> 以App的方式写入字符串
   * @param string Name 名字
   * @param vstring array 数据写入数据库
   * @param type_mode mode 写入方式
   * @return True写入正确,False 写入失败
   */
  bool static write(std::string Name,
                    type style,
                    const vstring array,
                    type_mode mode);
  /**
   * @brief 设置读buff的seek
   * @param  POINTER fileIndex 文件指针
   * @return
   */
  void setReadSeek(POINTER fileIndex);
  /**
   * @brief 设置写buff的seel
   * @param  POINTER fileIndex 文件指针
   * @return
   */
  void setWriteSeek(POINTER fileIndex);
  /**
   * @brief 文件指针
   * @return 返回文件指针
   */
  POINTER returnReadTell();
  /**
   * @brief 文件指针
   * @return  返回文件指针
   */
  POINTER returnWriteTell();
  /**
   * @brief 重新设置指向文件
   * @param  string Name 文件名
   * @param  type style 类型
   * @return  
   */
  void resetPath(std::string Name, type style);
  /**
   * @brief <static> 以App的方式写入字符串
   * @param  string Name 名字
   * @param  string& str 单个字符串
   * @param type_mode mode 写入方式
   * @return  True写入正常，False写入失败
   */
  bool static write(std::string Name,
                    type style,
                    const std::string& str,
                    type_mode mode);
  /**
   * @brief <static> 创建
   * @param string Name 需要创建的名字
   * @param type stype 需要创建的类型
   * @return True表示文件创造成功，False表示文件创造失败
   */
  bool static create(std::string Name, type style);

  /**
   * @brief 创建文件
   * @param  string TruePath 真实路径
   * @return  True表示文件创造成功，False表示文件创造失败
   */
  bool static create(std::string TruePath);
  /**
   * @brief 返回type
   * @return  类型
   */
  virtual type returnType();
  // writeFileBuff是写文件buff指针
  std::ofstream writeFileBuff;
  // readFileBuff是读文件buff指针
  std::ifstream readFileBuff;
  //文件类型
  type style;
  //当前打开的文件数总数
  static int count;
  // 真实路径
  std::string truePath;
  // 当前的OpenMode
  type_mode nowMode;
};
#endif