/*
 * @Description  : 用户数据类
 * @Autor        : TMD
 * @Date         : 2022-12-17 11:00:49
 * @LastEditTime : 2022-12-20 10:52:09
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
// 权限
enum TYPE_POWER {
  ROOT,     // 超级管理员
  CONTROL,  // 管理员
  NORMAL    // 普通用户
};
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
  // readline的buff
  static std::vector<std::string> buff;
  // 登录名buff，创建或添加用户的时候对比
  static std::set<std::string> nameBuff;
  /**
   * @brief 读入所有用户名，以供创建用户的时候对比ID，并填充nameBuff
   * @return  
   */
  void readAllNameDate();
  /**
   * @brief 判断是否登录
   * @return 正常登录True，登录错误False
   */
  bool login();

 public:
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
   * @brief 退出
   * @return
   */
  void quit();
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
