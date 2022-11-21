/*
 * @Description  : 表的PCB申明
 * @Autor        : TMD
 * @Date         : 2022-11-20 23:12:46
 * @LastEditTime : 2022-11-21 07:27:11
 */
#ifndef _TABLEPCB_
#define _TABLEPCB_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
// 文件指针
#define POINTER int
/**
 * @brief 对于表的一些TCB数据
 */
class TablePCB : public _super {
 private:
  // 指向文件结尾的文件指针
  POINTER endLineIndex;
  // 文件总字节数
  std::string size;
  // 是否打开
  bool open;
  /**
   * @brief 将数据写回文件
   */
  void writeDate();
  /**
   * @brief 将数据读入文件
   */
  void readData();
 public:
  /**
   * @brief 文件名
   * @return  返回文件名
   */
  std::string returnName();
  /**
   * @brief 设置文件结束指针
   * @param  POINTER fileIndex 文件指针值
   */
  void setEndLineIndex(POINTER fileIndex);
  /**
   * @brief 文件结束指针
   * @return 文件结束指针的值
   */
  POINTER returnEndLineIndex();
  /**
   * @brief 文件大小
   * @return  文件大小的值
   */
  std::string returnFileSize();
  /**
   * @brief 文件是否打开
   * @return 打开则返回True，否则返回False；
   */
  bool isOpen();
  /**
   * @brief 构造函数
   * @param  string TableName 表名
   */
  TablePCB(std::string TableName);
  /**
   * @brief 构造函数
   * @param  Table table 表对象
   */
  TablePCB(Table table);
  /**
   * @brief 析构函数
   */
  ~TablePCB();
};
#endif