/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2023-01-14 11:26:55
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
  shell();
  ~shell();
  /**
   * @brief 读入数据
   * @param  string data 数据
   * @return 输入退出则返回False，否则返回True
   */
  bool read(std::string data);
  /**
   * @brief 读入数据
   * @param  revstring data string数组
   * @return  输入退出则返回False，否则返回True
   */
  bool read(revstring data);
 private:
  // 当前工作路径
  vstring pwd;
  // 用户输入指令
  vCID command;
  // 用户输入数据
  vstring data;
  // 用户输入的指令计数
  int commandCount;
  // 是否需要显示提示符
  bool need;
   /**
  * @brief 判断是否输入"确认"
  * @return  如果输入返回True，否则返回False
  */
 bool inputACK();
  /**
   * @brief 执行指令
   * @return 输入退出则返回False，否则返回True
   */
  bool read();

  /**
   * @brief 语法检查以及指令与数据分类存储
   * @param  string _str 待检查字符串
   * @return 指令不存在问题的话，返回True，存在问题则返回false
   */
  bool check(std::string _str);
  /**
   * @brief 语法检查以及指令与数据分类存储
   * @param  revstring value string 数组
   * @return 指令的语法检查
   */
  bool check(revstring value);
  /** 
   * @brief 语法检查是否含有'/'，'!'等违规字符
   * @param  string _str 待检查字符
   * @return 没有问题的话，返回true，否则返回false;
   */
  bool aidCheckData(std::string _str);
  /**
   * @brief 执行脚本
   * @return
   */
  void toExecute();
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
   * @brief 输入插入默认表后的操作
   * @return  
   */
  void toInsertDefaultTable();
  /**
   * @brief 输入插入表后的操作
   * @return  
   */
  void toInsertTable();
  /**
   * @brief 输入插入数据库表后的操作
   * @return  
   */
  void toInsertDatabaseTable();

  /**
   * @brief 输入查询后的操作
   * @return
   */
  void toFind();
  /**
   * @brief 输入查询表后的操作
   * @return  
   */
  void toFindTable();
  /**
   * @brief 输入查询数据库表后的操作
   * @return  
   */
  void toFindDatabaseTable();
  /**
   * @brief 输入显示后的操作
   * @return
   */
  void toShow();
  /**
   * @brief 输入显示数据库后的操作
   * @return  
   */
  void toShowDatabase();
  /**
   * @brief 输入显示数据库表后的操作
   * @return  
   */
  void toShowDatabaseTable();
  /**
   * @brief 输入显示表后的操作
   * @return  
   */
  void toShowTable();
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
   * @brief 输入删除数据库表后的操作
   * @return  
   */
  void toDeleteDatabaseTable();
  /**
   * @brief 输入删除用户后的操作
   * @return  
   */
  void toDeleteUser();
  /**
   * @brief 输入删除用户后的操作
   * @return  
   */
  void toDeleteManager();
};
#endif