/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2022-12-30 19:06:15
 */
#ifndef _SHELL_
#define _SHELL_
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _UNORDERED_MAP_
#define _UNORDERED_MAP_
#include <unordered_map>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif

class shell : public User {
 public:
  /**
   * @brief 登录
   * @param  string ID 帐号
   * @param  string password 密码
   * @return
   */
  bool logn(std::string ID, std::string password);
  shell();
  ~shell();
  /**
   * @brief 读入数据
   * @param  string data 数据
   * @return 符合语法返回True，否则返回False
   */
  bool read(std::string data);
 private:
  // 当前工作路径
  vstring pwd;
  // CID
  static std::unordered_map<std::string, TYPE_CID> HashMapCID;
  // 指令
  vCID command;
  // 用户输入数据
  vstring data;
  /**
   * @brief 语法检查以及指令与数据分类存储
   * @param  string _str 待检查字符串
   * @return 指令不存在问题的话，返回True，存在问题则返回false
   */
  bool check(std::string _str);
  /**
   * @brief 语法检查是否含有'/'，'!'等违规字符
   * @param  string _str 待检查字符
   * @return 没有问题的话，返回true，否则返回false;
   */
  bool aidCheckData(std::string _str);
  
  /**
   * @brief 输出选择后的操作
   * @return  
   */
  void toChoose();
  /**
   * @brief 输出选择表后的操作
   * @return  
   */
  void toChooseTable();
  /**
   * @brief 输入选择数据库后的操作
   * @return  
   */
  void toChooseDatabase();
  /**
   * @brief 输入选择数据库表后的操作
   * @return  
   */
  void toChooseDatabaseTable();
  /**
   * @brief 输入插入后的操作
   * @return
   */
  void toInsert();
  /**
   * @brief 输入查询后的操作
   * @return
   */
  void toFind();
  /**
   * @brief 输入显示后的操作
   * @return
   */
  void toShow();
  /**
   * @brief 输入创建后的操作
   * @return
   */
  void toCreate();
  /**
   * @brief 输入创建，表后的操作
   * @return
   */
  void toCreateTable();
  /**
   * @brief 输入创建，数据库后的操作
   * @return
   */
  void toCreateDatabase();
  /**
   * @brief 输入删除后的操作
   * @return
   */
  void toDelete();
  /**
   * @brief 输入删除表后的操作
   * @return
   */
  void toDeleteTable();
  /**
   * @brief 输入删除数据库后的操作
   * @return
   */
  void toDeleteDatabase();
  /**
   * @brief 输入重命名后的操作
   * @return
   */
  void toRename();
  /**
   * @brief 输出重命名表后的操作
   * @return
   */
  void toRenameTable();
  /**
   * @brief 输入重命名数据库后的操作
   * @return
   */
  void toRenameDatabase();
};
#endif