/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:01
 * @LastEditTime : 2022-12-27 11:05:41
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
class menuOutput {
 public:
  menuOutput();
  ~menuOutput();
  /**
   * @brief  shell输入结束
   * @param TYPE_POWER power 权限
   */
  void static printExit(TYPE_POWER power);
  /**
   * @brief 输出权限不足
   * @param TYPE_POWER power 权限
   */
  void static printPowerNoEnough(TYPE_POWER power);
  /**
   * @brief 输出没有登录
   * @return
   */
  void static printNotLogin();
  /**
   * @brief 输出没有选择数据库
   * @param  TYPE_POWER power 权限
   * @return  
   */
  void static printNotChooseDatabase(TYPE_POWER power);
  /**
   * @brief 输出指令错误
   * @param  TYPE_POWER power 权限
   * @return
   */
  void static printCommandError(TYPE_POWER power);
  /**
   * @brief 输出登录成功，或登录失败
   * @param  bool login 登录成功或失败]
   * @param TYPE_POWER power 权限
   * @param  string ID 帐号
   * @return
   */
  void static printLoginOrNot(bool login, TYPE_POWER power = TYPE_POWER::NONE, std::string ID = "");
  /**
   * @brief 输出不存在该数据库
   * @param  TYPE_POWER power 权限
   * @return  
   */
  void static printNotExistsDatabase(TYPE_POWER power);
 private:
  /**
   * @brief 输出权限提示符
   * @param TYPE_POWER power 权限
   * @return
   */
  inline void static printPower(TYPE_POWER power = TYPE_POWER::NONE);
  /**
 * @brief 换行输出
 * @param  string _str 输出字段
 * @return
 */
inline void static printl(std::string _str);
/**
 * @brief 输出(不换行)
 * @param  string _str 输出字段
 * @return
 */
inline void static print(std::string _str);
};