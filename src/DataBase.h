/*
 * @Description  : DataBase类中的一些声明
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:33:23
 * @LastEditTime : 2022-11-15 16:02:19
 */
#ifndef _DATABSE_
#define _DATABSE_

#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif  
/**
 * @brief 封装对数据库的操作，比如创建，删除。建立表等函数。
 */
class DataBase : public _dir {
 public:
 /**
  * @brief 析构函数
  * @return  
  */
 ~DataBase();
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
   * @brief 判断数据库是否存在
   * @return True为存在，False为不存在
   */
  virtual bool isExist();
  /**
   * @brief 类型
   * @return type 类型
   * 
  */
  virtual type returnType();
  /**
   * @brief 创建数据库(底层就是创建文件夹)
   * @return 创建成功返回True，否则返回False
   */
  virtual bool create();
  /**
   * @return 返回表数量
   */
  virtual int returnCount();
  /**
   * @brief 删除默认数据库
   * @return  正常返回
   */
  virtual bool remove();
  /**
   * @brief 删除数据库
   * @param  string name 待删除的数据库名
   * @return  正常删除则返回True,否则返回False
   */
  bool static remove(std::string name);
  /**
   * @brief 显示数据库内表项
   * @return
   */
  void showDataBaseTable();
  /**
   * @brief 创建数据库
   * @param  string name 数据库名
   * @return 创建正常则返回True,否则返回False
   */
  bool static create(std::string name);

  /**
   * @brief 显示所有数据库
   * @return
   */
  void static showDataBase();
    /**
   * @brief 判断指定数据库是否存在
   * @param  string DataBaseName 数据库名字
   * @return True为存在，False为不存在
   */
  bool static isExist(std::string DataBaseName);
  /**
   * @brief 向数据库内插入表
   * @param string tableName 表名字
   * @param vector<string>& tableItem 表项
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(std::string tableName,
                   const std::vector<std::string>& tableItem);
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
  bool removeTable(std::string tableName);

  /**
   * @brief <static>删除指定数据库
   * @param string DataBaseName
   * @return 删除正常则返回True，否则返回False
   */
  bool static removeDataBase(std::string DataBaseName);
  // 打开的数据库的个数
  int static count;
};
#endif