/**
 * @file TablePCB.h
 * @brief 表PCB的声明
 * @author TMD
 * @date 2022-11-20
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
// 最大列数
#define MAXINT 2147483647
/**
 * @brief 对于表的一些TCB数据
 */
class TablePCB {
 public:
  // 文件
  _file file;
  // 指向文件结尾的文件指针
  POINTER endLineIndex;
  //行数
  int length;
  //索引
  int index;
  // 最少列(防止索引列为第4列却插入3列数据)
  int minCol;
  /**
   * @brief 从文件中读取
   */
  void readData();
  /**
   * @brief 写入文件
   */
  void writeData();
  /**
   * @brief 初始化
   */
  void init();

 public:
  /**
   * @brief 文件名
   *
   * @return  返回文件名
   */
  std::string returnName();
  /**
   * @brief 设置文件结束指针
   *
   * @param  POINTER fileIndex 文件指针值
   */
  void setEndLineIndex(POINTER fileIndex);

  /**
   * @brief 设置文件结束指针
   *
   * @param  Table table 表对象
   * @param  POINTER fileIndex 待设置的文件指针
   */
  void static setEndLineIndex(Table table, POINTER fileIndex);
  /**
   * @brief 设置索引
   *
   * @param  string tableName 表名
   * @param  INDEX fileIndex 索引
   */
  void static setIndex(std::string tableName, INDEX fileIndex);
  /**
   * @brief 设置索引
   *
   * @param  INDEX fileIndex 索引
   */
  void setIndex(INDEX fileIndex);
  /**
   * @brief 文件结束指针
   *
   * @return 文件结束指针的值
   */
  INDEX returnEndLineIndex() const;
  /**
   * @brief 文件大小
   *
   * @return  文件大小的值
   */
  std::string returnFileSize() const;
  /**
   * @brief 文件最小列数
   *
   * @return 最小列(以0开始)
   */
  int returnMinCol() const;
  /**
   * @brief 返回索引
   *
   * @return  索引
   */
  INDEX returnIndex() const;
  /**
   * @brief 构造函数
   *
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   */
  TablePCB(std::string DBID, std::string TBID);
  /**
   * @brief 构造函数
   *
   * @param  string DBIDAndTBID 数据库+表名
   */
  TablePCB(std::string DBIDAndTBID);
  /**
   * @brief 构造函数
   *
   * @param  Table& table 表对象
   */
  TablePCB(Table& table);
  /**
   * @brief 析构函数
   */
  ~TablePCB();
  /**
   * @brief 添加行数
   */
  void addLength();
  /**
   * @brief PCB文件初始化
   *
   * @param DBIDAndTBID 表相对地址
   */
  void static inputPCBInformation(std::string DBIDAndTBID);
  /**
   * @brief PCB文件初始化
   *
   * @param DBID 数据库名
   * @param TBID 表名
   */
  void static inputPCBInformation(std::string DBID, std::string TBID);
	/**
	 * @brief PCB文件初始化
	 * 
	 * @param pcbFile PCB文件
	 */
  void static inputPCBInformation(_file& pcbFile);
};
#endif
