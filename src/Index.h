/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:43
 * @LastEditTime : 2023-01-23 16:11:40
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
   * @return
   */
  Index();
  /**
   * @brief 析构函数
   * @return
   */
  ~Index();
  /**
   * @brief <static> 更新索引
   * @param  string tableName 表名
   * @return
   */
  void static update(std::string tableName);
  /**
   * @brief <static> 新文件创建索引文件
   * @param  Table table 表对象
   * @return
   */
  void static create(Table table);
  /**
   * @brief <static> 新文件创建索引文件
   * @param  string tableName 表名
   * @return
   */
  void static create(std::string tableName);
  /**
   * @brief <static> 新文件创建索引文件
   * @param  _file file
   * @return
   */
  void static create(_file file);
};
#endif