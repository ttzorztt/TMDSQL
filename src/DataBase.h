/*
 * @Description  : DataBase类中的一些声明
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:33:23
 * @LastEditTime : 2022-11-07 14:30:40
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
/**
 * @brief 封装对数据库的操作，比如创建，删除。建立表等函数。
 */
class DataBase : public _dir {
 public:
 virtual std::string returnPath();
  /**
   * @brief 判断数据库是否存在
   * @return True为存在，False为不存在
   */
  virtual bool isExist();
  /**
   * @brief 判断指定数据库是否存在
   * @param  string DataBaseName 数据库名字
   * @return True为存在，False为不存在
   */
  bool static isExist(std::string DataBaseName);
  /**
   * @brief  构造创建数据库对象
   * @param string name 数据库路径
   * @return 
   */
  DataBase(std::string name);
  /**
   * @brief 拷贝构造函数
   * @param  DataBase& copy
   * @return 
   */
  DataBase(DataBase& copy);
  /**
   * @brief 创建数据库(底层就是创建文件夹)
   * @return 创建成功返回True，否则返回False
   */
  bool create();
  /**
   * @brief 显示数据库内表项
   * @return
   */
  void showDataBaseTable();
  /**
   * @brief 显示所有数据库
   * @return
   */
  void static showDataBase();
  /**
   * @brief 向数据库内插入表
   * @param string tableName 表名字
   * @param vector<string>& tableItem 表头项
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(std::string tableName, const std::vector<std::string>& tableItem);
  /**
   * @brief 向数据库内插入表
   * @param string tableName 表名字
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(std::string tableName);
  /**
   * @brief 删除数据库中tableName表项
   * @param string tableName 表名
   * @return 删除正常则返回True，否则返回False
   */
  bool deleteTable(std::string tableName);
  /**
   * @brief 删除默认数据库
   * @return  正常返回
   */
  bool removeDataBase();
  /**
   * @brief <static>删除指定数据库
   * @param string DataBaseName
   * @return 删除正常则返回True，否则返回False
   */
  bool static removeDataBase(std::string DataBaseName);
 private:
};