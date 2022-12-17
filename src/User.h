/*
 * @Description  : 用户数据类
 * @Autor        : TMD
 * @Date         : 2022-12-17 11:00:49
 * @LastEditTime : 2022-12-17 11:10:04
 */

#ifndef _STRING_
#define _STRING_
#include <string>
#endif
class User {
 private:
  // 用户名
  std::string UserName;
  // 用户密码
  std::string UserPassword;
  //登录状态
  bool loginStatus;

 public:
  User();
  /**
   * @brief 构造函数
   * @param  string UserName 用户名
   * @return
   */
  User(std::string UserName);
  /**
   * @brief 判断是否登录
   * @param  string UserPassword 用户密码
   * @return 正常登录True，登录错误False
   */
  bool login(std::string UserPassword);
  ~User();
};
