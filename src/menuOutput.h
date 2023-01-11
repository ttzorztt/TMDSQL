/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:01
 * @LastEditTime : 2023-01-11 20:40:47
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class menuOutput {
 private:
 public:
  menuOutput();
  ~menuOutput();
  /**
   * @brief 输出用户不存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要输出提示符
   * @return
   */
  void static printUserNotExists(TYPE_POWER power, bool need = true);
   /**
   * @brief 输出管理员不存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要输出提示符
   * @return
   */
  void static printManagerNotExists(TYPE_POWER power, bool need = true);
  /**
   * @brief  shell输入结束
   * @param TYPE_POWER power 权限
   * @param bool need 是否需要提示符
   */
  void static printExit(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出指令取消执行
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printCommandBackout(TYPE_POWER power,bool need = true);
  /**
   * @brief 输出表不为空
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printTableNotEmptyAndDeleteTip(TYPE_POWER power,bool need = true);
    /**
   * @brief 输出数据库不为空
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printDatabaseNotEmptyAndDeleteTip(TYPE_POWER power,bool need = true);
    /**
     * @brief 输出插入指令中没有待插入的数据
     * @param  TYPE_POWER power 权限
     * @param  bool need 是否需要提示符
     * @return  
     */
    void static printInsertNoValue(TYPE_POWER power,bool need = true);

    /**
     * @brief 显示查询到的内容。
     * @param  TYPE_POWER power 权限
     * @param  vstring data 待输出的内容 
     * @param  bool need 是否需要提示符
     * @return  
     */
    void static printShowFindTable(TYPE_POWER power,vstring data,bool need = true);
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
   * @brief 对创建成功的ACK
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   */
  void static printCreateACK(TYPE_POWER power,bool need = true);
  /**
   * @brief 对删除成功的ACK
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printDeleteACK(TYPE_POWER power,bool need= true);
  /**
   * @brief 插入成功的ACK
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符号
   * @return  
   */
  void static printInsertACK(TYPE_POWER power,bool need = true);
  /**
   * @brief 用户已存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printUserExists(TYPE_POWER power,bool need = true);
    /**
   * @brief 管理员已存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return  
   */
  void static printManagerExists(TYPE_POWER power,bool need = true);
  /**
   * @brief 输出登录成功，或登录失败
   * @param  bool login 登录成功或失败]
   * @param TYPE_POWER power 权限
   * @param TYPE_ERROR  typeError 失败类型
   * @param  string ID 帐号
   * @param bool need 是否需要提示符
   * @return
   */
  void static printLoginOrNot(bool login,
                              TYPE_LOGIN_ERROR tpyeError,
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
   * @brief 输出不存在该表
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return
   */
  void static printNotExistsTable(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出表已存在
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要提示符
   * @return
   */
  void static printTableIsExists(TYPE_POWER power, bool need = true);
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
   * @brief 输出系统中存在的DBID数据库中的表
   * @param  TYPE_POWER power 权限
   * @param Database& database 数据库
   * @param  bool need 是否需要输出提示符
   * @return
   */
  void static printShowDatabase(TYPE_POWER power,
                                DataBase& database,
                                bool need = true);
  /**
   * @brief 输出系统中存在的数据库
   * @param  TYPE_POWER power 权限
   * @param  bool need 是否需要输出提示符
   * @return
   */
  void static printShowDatabase(TYPE_POWER power, bool need = true);
  /**
   * @brief 输出制定数据库中的表内容
   * @param  TYPE_POWER power 权限
   * @param Table& table 表
   * @param int number 默认输出5行
   * @param  bool need 是否需要输出提示符
   * @return
   */
  void static printShowTable(TYPE_POWER power,
                             Table& table,
                             int number = 5,
                             bool need = true);
};