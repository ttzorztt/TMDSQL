/**
 * @file Log.h
 * @brief 日志管理
 * @author TMD
 * @date 2023-01-12
 */
#ifndef _LOG_
#define _LOG_
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
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
class Log {
 private:
  static _file file;
  /**
   * @brief 获取当前的日期和时间，并进行日志时间输入
   *
   * @return  返回日期和时间
   */
  void static inputNowTime(TYPE_ERROR_CASE& errorCase);
  std::unordered_map<TYPE_ERROR_CASE, std::string> static EC;
  std::unordered_map<TYPE_POWER, std::string> static TP;

 public:
  /**
   * @brief 获取时间和日期
   *
   * @return  时间和日期
   */
  std::string static nowDataTime();
  /**
   * @brief 获取当前的日期
   *
   * @return  日期
   */
  std::string static nowData();
  /**
   * @brief 系统开启记录
   */
  void static open();
  /**
   * @brief 系统关闭记录
   */
  void static close();
  Log();
  Log& operator=(const Log& tmp) = delete;
  Log(const Log& tmp) = delete;
  ~Log();
  /**
   * @brief 执行SQL
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string SQLPath SQL路径
   * @param  TYPE_ERROR_CASE errorCase 错误类型
   */
  void static LogForExecuteSQL(std::string UserName, TYPE_POWER op,
                               std::string SQLPath,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string _data 执行指令
   * @param TYPE_ERROR_CASE errorCase 错误类型
   */
  void static LogForCompileError(std::string UserName, TYPE_POWER op,
                                 std::string _data,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param vCID command 指令
   * @param revstring data 数据
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForError(std::string UserName, TYPE_POWER op, vCID command,
                          revstring data, TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  revstring commandAndData 指令+数据
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForCompileError(std::string UserName, TYPE_POWER op,
                                 revstring commandAndData,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);

  /**
   * @brief 选择_数据库_DBID
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForSelectDatabase(std::string UserName, TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);

  /**
   * @brief 选择_数据库_表_DBID_TBID
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForSelectDatabaseTable(std::string UserName, TYPE_POWER op,
                                        std::string DBID, std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForShow(std::string UserName, TYPE_POWER op,
                         TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示所有数据库
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForShowAllDatabase(std::string UserName, TYPE_POWER op,
                                    TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示_数据库_DBID
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForShowDatabase(std::string UserName, TYPE_POWER op,
                                 std::string DBID,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示_数据库_表
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param string DBID 数据库名
   * @param string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForShowDatabaseTable(std::string UserName, TYPE_POWER op,
                                      std::string DBID, std::string TBID,
                                      TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 退出
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param TYPE_ERROR_CASE errorcase 失败原因
   */
  void static LogForExit(std::string UserName, TYPE_POWER op,
                         TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 登录
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string LoginID 登录ID
   * @param  string LoginPassword 登录密码
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForLogin(std::string UserName, TYPE_POWER op,
                          std::string LoginID, std::string LoginPassword,
                          TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_用户
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string ID 创建ID
   * @param  string Pd 创建密码
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForCreateUser(std::string UserName, TYPE_POWER op,
                               std::string ID, std::string Pd,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_管理员
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string ID 创建ID
   * @param  string Pd 创建密码
   * @param  TYPE_ERROR_CASE erorCase 失败原因
   */
  void static LogForCreateManager(std::string UserName, TYPE_POWER op,
                                  std::string ID, std::string Pd,
                                  TYPE_ERROR_CASE erorCase = 顺利执行);
  /**
   * @brief 创建_数据库
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForCreateDatabase(std::string UserName, TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_数据库_表
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForCreateDatabaseTable(std::string UserName, TYPE_POWER op,
                                        std::string DBID, std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_列_数据库_表
   *
   * @param UserName 用户名
   * @param op 权限
   * @param DBID 数据库名
   * @param TBID 表名
   * @param Col 列
   * @param errorCase 失败原因
   */
  void static LogForDeleteColDatabaseTable(
      std::string UserName, TYPE_POWER op, std::string DBID, std::string TBID,
      std::string Col, TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_行_数据库_表
   *
   * @param UserName 用户名
   * @param op 权限
   * @param DBID 数据库名
   * @param TBID 表名
   * @param Row 行
   * @param errorCase 失败原因
   */
  void static LogForDeleteRowDatabaseTable(
      std::string UserName, TYPE_POWER op, std::string DBID, std::string TBID,
      std::string Row, TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_数据库
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForDeleteDatabase(std::string UserName, TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_数据库_表
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForDeleteDatabaseTable(std::string UserName, TYPE_POWER op,
                                        std::string DBID, std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_用户
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string UID 删除用户名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForDeleteUser(std::string UserName, TYPE_POWER op,
                               std::string UID,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_管理员
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string MID 删除管理员ID
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForDeleteManager(std::string UserName, TYPE_POWER op,
                                  std::string MID,
                                  TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 插入_数据库_表
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  revstring data 插入数据
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForInsertDatabaseTable(std::string UserName, TYPE_POWER op,
                                        std::string DBID, std::string TBID,
                                        revstring data,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 查询_数据库_表
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  string Index 索引
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   */
  void static LogForFindDatabaseTable(std::string UserName, TYPE_POWER op,
                                      std::string DBID, std::string TBID,
                                      std::string Index,
                                      TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 设置_索引_数据库_表
   *
   * @param  string UserName 使用者
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库
   * @param  string TBID 表
   * @param  std::string index 索引
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForSetIndexDatabaseTable(std::string UserName, TYPE_POWER op,
                                          std::string DBID, std::string TBID,
                                          std::string index,
                                          TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 设置_视图_数据库_表_
   *
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库
   * @param  string TBID 表
   * @param  string operatorUserName 操作用户
   * @param  vstring viewData 视图
   * @param  TYPE_ERROR_CASE errorCase 报错类型
   */
  void static LogForSetViewDatabaseTable(std::string UserName, TYPE_POWER op,
                                         std::string DBID, std::string TBID,
                                         std::string operatorUserName,
                                         vstring viewData,
                                         TYPE_ERROR_CASE errorCase = 顺利执行);
};
#endif
