/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:12:10
 * @LastEditTime : 2022-11-21 06:51:21
 */
#ifndef _TABLE_
#define _TABLE_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
// 文件指针
#define POINTER int

/**
 * @brief 封装表操作
 */
class Table : public _file{
 private:
 public:
   /**
    * @brief 创建
    * @return  正常创建则返回True，否则返回false
    */
   virtual bool create();
  /**
   * @brief 删除
   * @return  正常删除则返回True，否则返回False
   */
  virtual bool remove();
  /**
   * @brief 获取数量
   * @return  返回数量
   */
  virtual int returnCount();
  /**
   * @brief 判断是否存在
   * @return 存在则返回True,否则返回false
   */
  virtual bool isExist();
  Table(Table& table);
  /**
   * @brief 构造函数
   * @param  string databaseAndTableName 数据库名+表名
   * @param type style 类型
   * @return
   */
  Table(std::string databaseAndTableName,type style);
  /**
   * @brief 构造函数
   * @param  DataBase database 数据库对象
   * @param  string tableName 表名
   * @param type style 类型
   * @return
   */
  Table(DataBase database, std::string tableName, type style);
  /**
   * @brief app 的方式写入index
   * @param  string index 索引
   * @param  POINTER fileIndex 文件指针
   * @return  正常操作则返回True，否则返回False
   */
  bool appInsertIndex(std::string index,POINTER fileIndex);
  /**
   * @brief <static> app的方式写入
   * @param  string tableName 表名
   * @param  string index 索引
   * @param  POINTER fileIndex 文件指针
   * @return   正常操作则返回True，否则返回False
   */
  bool static appInsertIndex(std::string tableName,std::string index,POINTER fileIndex);
  /**
   * @brief <static> app的方式写入
   * @param  Table table 表
   * @param  string index 索引
   * @param  POINTER fileIndex 文件指针
   * @return   正常操作则返回True，否则返回False
   */
  bool static appInsertIndex(Table table,std::string index,POINTER fileIndex);

  /**
   * @brief 写入
   * @param  vector<std::string> value 数组
   * @return   正常操作则返回True，否则返回False
   */
  bool append(std::vector<std::string> value);
  /**
   * @brief <static> 写入
   * @param  Table table 表
   * @param  vector<std::string> value 数组
   * @return   正常操作则返回True，否则返回False
   */
  bool static append(Table table,std::vector<std::string> value);
  /**
   * @brief <static> 写入
   * @param  string tableName 表名
   * @param  vector<std::string> value 数组
   * @return   正常操作则返回True，否则返回False
   */
  bool static append(std::string tableName,std::vector<std::string> value);

  /**
   * @brief  返回指针所指向的一行
   * @param  POINTER fileIndex 指针
   * @return vecotr<string> 
   */
  std::vector<std::string> indexReadline(POINTER fileIndex);
  /**
   * @brief <static> 返回指针所指向的一行
   * @param  string tableName 表名
   * @param  POINTER fileIndex 指针
   * @return  vector<string>
   */
  std::vector<std::string> static indexReadline(std::string tableName,POINTER fileIndex);
  /**
   * @brief <static> 返回指针所指向的一行
   * @param  Table table 表
   * @param  POINTER fileIndex 指针
   * @return  vector<string>
   */
  std::vector<std::string> static indexReadline(Table table,POINTER fileIndex);
  /**
   * @brief 更新索引
   */
  void updateIndex();
  /**
   * @brief 析构函数
   */
  ~Table();
  /**
   * @brief 寻找索引为index的数据，(默认第一个每列第一个数据是索引)
   * @param  string index 索引值
   * @return vector<string> 这一行的数据
   */
  std::vector<std::string> find(std::string index);
  
private:
type style;
//记录打开表的个数
 int static count;
};

#endif