/*
 * @Description  : 用户数据类
 * @Autor        : TMD
 * @Date         : 2022-12-17 11:00:49
 * @LastEditTime : 2022-12-27 22:02:48
 */

#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif

class User {
 private:
  // 用户名
  std::string UserName;
  // 用户密码
  std::string UserPassword;
  //登录状态
  bool loginStatus;
  // 权限
  TYPE_POWER power;
  // 当前用户个数
  static int count;
  // UserData文件
  static _file pd;
  // 登录名buff，创建或添加用户的时候对比
  static std::set<std::string> nameBuff;
  // 当前登录的用户
  static std::set<std::string> nowLoginId;
  // 修改位
  bool reset;
  /**
   * @brief 读入所有用户名，以供创建用户的时候对比ID，并填充nameBuff
   * @return  
   */
  void readAllNameDate();
  /**
   * @brief 判断是否登录,并设置赋值帐号密码，登录状态，以及权限
   * @return 正常登录True，登录错误False
   */
  bool login();
  /**
   * @brief 添加用户
   * @param  string UserName 帐号
   * @param  string UserPassword 密码
   * @param TYPE_POWER power 权限
   * @return  
   */
  void addUser(std::string UserName,std::string UserPassword,TYPE_POWER power);
 public:
  /**
   * @brief 数据库中有没有表
   * @param string DatabaseName 数据库名
   * @param  string tableName 表名
   * @return  true表示有，false表示没有
   */
  bool DatabaseHaveTable(std::string DatabaseName,std::string tableName);
  /**
   * @brief 有没有该数据库
   * @param  string DatabaseName 数据库名
   * @return true表示有，false表示没有
   */
  bool HaveDatabase(std::string DatabaseName);
 /**
  * @brief 返回登录状态
  * @return  True表示登录正常，False表示登录错误
  */
 bool ReturnLoginStatus() const;
 /**
  * @brief 返回权限
  * @return  0为Root权限，1为管理员权限，2为普通用户权限
  */
TYPE_POWER ReturnPower() const;

/**
 * @brief 返回用户帐号
 * @return 帐号
 */
std::string ReturnUserName() const;
 /**
  * @brief 添加普通用户 (管理员或超级管理员)
  * @param  string UserName 用户名
  * @param  string UserPassword 用户密码
  * @return  权限不够的话返回False，正常添加返回True
  */
 bool addNormalUser(std::string UserName,std::string UserPassword);
 /**
  * @brief 添加管理员用户 (超级管理员)
  * @param  string UserName 用户名
  * @param  string UserPassword 用户密码
  * @return  权限不够的话返回False，正常添加返回True
  */
 bool addManagerUser(std::string UserName,std::string UserPassword);
 User();
  User(const User& copy) = delete;
  /**
   * @brief 尝试
   * @param  string UserName 帐号
   * @param  string Password 密码
   * @return 登录则返回True，否则返回False
   */
  bool login(std::string UserName, std::string Password);

  /**
   * @brief 构造函数
   * @param  string UserName 用户名
   * @param  string UserPasswd 密码
   * @return
   */
  User(std::string UserName, std::string UserPasswd);

  /**
   * @brief 修改密码
   * @param  string Userpasswd 密码
   */
  void resetPassword(std::string Userpassword);
  /**
   * @brief 添加用户，
   * @param  TYPE_POWER op 当前User的权限
   * @param  string UserName 需要创建用户的名称
   * @param  string UserPassword 需要创建用户的名字
   * @return
   */
  void addUser(TYPE_POWER op, std::string UserName, std::string UserPassword);
  ~User();
};
