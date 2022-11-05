/*
 * @Description: DateBase类中的一些声明
 * @Autor: TMD
 * @Date: 2022-11-01 17:33:23
 * @LastEditTime: 2022-11-05 19:07:31
 */
#ifndef _FILE_
#define _FILE_
#include "file.h"
#endif
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _MAP_
#define _MAP_
#include <map>
#endif
using namespace std;
/**
 * @brief 封装对数据库的操作，比如创建，删除。建立表等函数。
*/
class DateBase : public _file {
 public:
  /**
   * @brief:  构造创建数据库对象
   * @param {string} name 数据库路径
   */
  DateBase(string name);
  /**
   * @brief: 创建数据库(底层就是创建文件夹)
   * @return {*} 创建成功返回True，否则返回False
   */
  bool create();
  /**
   * @brief: 显示数据库内表项
   * @return {*}
   */
  void showDateBase();
  /**
   * @brief 向数据库内插入表
   * @param {string} tableName 表名字
   * @param {vector<string>&} tableItem 表头项
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(string tableName, const vector<string>& tableItem);
  /**
   * @brief 向数据库内插入表
   * @param {string} tableName 表名字
   * @return 插入正常则返回True,否则返回False
   */
  bool insertTable(string tableName);
  /**
   * @brief 删除数据库中tableName表项
   * @param tableName 表名
   * @return 删除正常则返回True，否则返回False
   */
  bool deleteTable(string tableName);

 private:
  // status = 1为正常状态
  // status = 0为非正常状态
  int status;
};