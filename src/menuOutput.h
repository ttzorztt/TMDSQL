/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:01
 * @LastEditTime : 2023-01-01 17:01:21
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
 private:
 public:
  menuOutput();
  ~menuOutput();
  /**
   * @brief  shell输入结束
   * @param TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   */
  void static printExit(TYPE_POWER power, bool need = true);

  /**
   * @brief 输出权限不足
   * @param TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   */
  void static printPowerNoEnough(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出没有登录
   * @param bool need 是否需要提示符
   * @return
   */
  void static printNotLogin(bool need = true);
  /**
   * @brief 输出没有选择数据库
   * @param  TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   * @return
   */
  void static printNotChooseDatabase(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出指令错误
   * @param  TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   * @return
   */
  void static printCommandError(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出pwd
   * @param  vstring & pwd pwd
   * @param  TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   * @return
   */
  void static printPWD(vstring& pwd, TYPE_POWER power, bool need = true);
  /**
   * @brief 输出数据库不存在该表
   * @param  TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   * @return
   */
  void static printDatabaseNotHaveTable(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出登录成功，或登录失败
   * @param  bool login 登录成功或失败]
   * @param TYPE_POWER power 权限
   * @param  string ID 帐号
   * @param bool need 是否需要提示符
   * @return
   */
  void static printLoginOrNot(bool login,
                              TYPE_POWER power = TYPE_POWER::NONE,
                              std::string ID = "",
                              bool need = true);
  /**
   * @brief 输出不存在该数据库
   * @param  TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   * @return
   */
  void static printNotExistsDatabase(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出表已存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printTableIsExists(TYPE_POWER power,bool need = true);
  /**
   * @brief 输出数据库存在，无法添加
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printDatabaseIsExists(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出权限提示符
   * @param bool need 是否需要提示符
   * @param TYPE_POWER power 权限
   * @return
   */
  void static printPower(TYPE_POWER power = TYPE_POWER::NONE, bool need = true);
  /**
   * @brief 输出找不到SQL文件
   * @param  bool need 是否需要提示符
   * @param bool need 是否需要提示符
   * @return
   */
  void static printNotFindSQL(TYPE_POWER power, bool need = true);
  /**
   * @brief 换行输出
   * @param  string _str 输出字段
   * @param bool need 是否需要提示符
   * @return
   */
   void static printl(std::string _str);
  /**
   * @brief 输出(不换行)
   * @param  string _str 输出字段
   * @param bool need 是否需要提示符
   * @return
   */
   void static print(std::string _str);

};