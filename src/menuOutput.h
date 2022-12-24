/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:01
 * @LastEditTime : 2022-12-24 10:27:22
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
 public:
  menuOutput(TYPE_POWER power = TYPE_POWER::NONE);
  void setPower(TYPE_POWER newPower);
  ~menuOutput();
  /**
   * @brief  shell输入结束
   */
  void  printExit();
  /**
   * @brief 输出权限不足
   */
  void  printPowerNoEnough();
  private:
    /**
   * @brief 输出权限提示符
   * @return
   */
  inline void  printPower();
  //权限等级
  TYPE_POWER power;
};