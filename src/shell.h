/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2022-12-27 11:42:22
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
  static std::unordered_map<std::string, int> HashMapCID;
  // 指令
  vint command;
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
   * @param  revstring value string数组
   * @return  
   */
  void toChoose(revstring value);
  /**
   * @brief 输出选择表后的操作
   * @param  revstring value string数组
   * @return  
   */
  void toChooseTable(revstring value);
  /**
   * @brief 输入选择数据库后的操作
   * @param  revstring value string数组
   * @return  
   */
  void toChooseDatabase(revstring value);
  /**
   * @brief 输入选择数据库表后的操作
   * @param  revstring value string数组
   * @return  
   */
  void toChooseDatabaseTable(revstring value);
  /**
   * @brief 输入插入后的操作
   * @param  revstring value string数组
   * @return
   */
  void toInsert(revstring value);
  /**
   * @brief 输入查询后的操作
   * @param  revstring value string数组
   * @return
   */
  void toFind(revstring value);
  /**
   * @brief 输入显示后的操作
   * @param  revstring value string数组
   * @return
   */
  void toShow(revstring value);
  /**
   * @brief 输入创建后的操作
   * @param  revstring value string的数组
   * @return
   */
  void toCreate(revstring value);
  /**
   * @brief 输入创建，表后的操作
   * @param  revstring value string数组
   * @return
   */
  void toCreateTable(revstring value);
  /**
   * @brief 输入创建，数据库后的操作
   * @param  revstring value string数组
   * @return
   */
  void toCreateDatabase(revstring value);
  /**
   * @brief 输入删除后的操作
   * @param  revstring value value<string>数组
   * @return
   */
  void toDelete(revstring value);
  /**
   * @brief
   * @param  revstring value
   * @return
   */
  void toDeleteTable(revstring value);
  /**
   * @brief
   * @param  revstring value
   * @return
   */
  void toDeleteDatabase(revstring value);
  /**
   * @brief 输入重命名后的操作
   * @param  revstring value value[string]数组
   * @return
   */
  void toRename(revstring value);
  /**
   * @brief 输出重命名表后的操作
   * @param  revstring value string数组
   * @return
   */
  void toRenameTable(revstring value);
  /**
   * @brief 输入重命名数据库后的操作
   * @param  revstring value string数组
   * @return
   */
  void toRenameDatabase(revstring value);
};
#endif