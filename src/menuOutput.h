/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:01
 * @LastEditTime : 2022-12-22 10:38:18
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif
class menuOutput {
  /**
   * @brief 输出权限提示符
   * @param  User& user 用户
   * @return  前缀占了多少字节
   */
  inline int static printPower(const User& user);
 public:
  menuOutput();
  ~menuOutput();
  /**
   * @brief  shell输入结束
   * @param  User& user 用户
   */
  void static printExit(const User& user);
};