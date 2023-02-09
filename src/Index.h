/**
 * @file Index.h
 * @brief 封装索引操作
 * @author TMD
 * @version 1.3
 * @date 2023-11-07
 */
#ifndef _INDEX_
#define _INDEX_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class Index {
 public:
  /**
   * @brief 构造函数
   */
  Index();
  /**
   * @brief 析构函数
   */
  ~Index();
  /**
   * @brief <static> 更新索引
	 *
   * @param  string tableName 表名
   */
  void static update(std::string tableName);
  /**
   * @brief <static> 新文件创建索引文件
	 *
   * @param  Table table 表对象
   */
  void static create(Table table);
  /**
   * @brief <static> 新文件创建索引文件
	 *
   * @param  string tableName 表名
   */
  void static create(std::string tableName);
  /**
   * @brief <static> 新文件创建索引文件
	 *
   * @param  _file file
   */
  void static create(_file file);
};
#endif
