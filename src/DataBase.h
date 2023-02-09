/**
 * @file DataBase.h
 * @brief DataBase类的一些声明
 * @author TMD
 * @version 1.3
 * @date 2023-11-01
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
#ifndef _UNORDERED_SET_
#define _UNORDERED_SET_
#include <unordered_set>
#endif
/**
 * @brief 封装对数据库的操作，比如创建，删除。建立表等函数。
 */
class DataBase : public _dir {
  private:
   // 数据库中的表
  std::unordered_set<std::string> SetOfTable;
 public:
 /**
  * @brief 析构函数
  */
 ~DataBase();
  /**
   * @brief  构造创建数据库对象
	 *
   * @param string name 数据库路径
   */
  DataBase(std::string name);
  /**
   * @brief 拷贝构造函数
	 *
   * @param  DataBase& copy
   */
  DataBase(DataBase& copy);
  /**
   * @brief 判断数据库是否存在
	 *
   * @return True为存在，False为不存在
   */
  virtual bool isExist();
  /**
   * @brief 类型
	 *
   * @return type 类型
   * 
  */
  virtual type returnType();
  /**
   * @brief 创建数据库(底层就是创建文件夹)
	 *
   * @return 创建成功返回True，否则返回False
   */
  virtual bool create();
	/**
	 * @brief 返回数量
	 *
	 * @Return 数量 
	 */
  virtual int returnCount();
  /**
   * @brief 删除默认数据库
	 *
   * @return  正常返回
   */
  virtual bool remove();
  /**
   * @brief 强制删除(非空集合)
   */
  void forceremove();
  /**
   * @brief 删除数据库
	 *
   * @param  string name 待删除的数据库名
	 *
   * @return  正常删除则返回True,否则返回False
   */
  bool static remove(std::string name);
  /**
   * @brief 创建数据库
	 *
   * @param  string name 数据库名
	 *
   * @return 创建正常则返回True,否则返回False
   */
  bool static create(std::string name);
    /**
   * @brief 判断指定数据库是否存在
	 *
   * @param  string DataBaseName 数据库名字
	 *
   * @return True为存在，False为不存在
   */
  bool static isExist(std::string DataBaseName);
  /**
   * @brief 向数据库内插入表
	 *
   * @param string tableName 表名字
   * @param revstring tableItem 表项
	 *
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(std::string tableName,
                  revstring tableItem);
  /**
   * @brief 向数据库内插入表
	 *
   * @param string tableName 表名字
	 *
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(std::string tableName);
  /**
   * @brief 删除数据库中tableName表项
	 *
   * @param string tableName 表名
	 *
   * @return 删除正常则返回True，否则返回False
   */
  bool removeTable(std::string tableName);
  
  /**
   * @brief 判断数据库中有没有表
	 *
   * @param  string DataBaseName 数据库名
   * @param  string tableName 表名
	 *
   * @return  存在返回true，不存在返回false
   */
  bool static isExistsTable(std::string DataBaseName,std::string tableName);
  // 打开的数据库的个数
  int static count;
};
#endif
