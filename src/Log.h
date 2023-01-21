/*
 * @Description  : 日志管理
 * @Autor        : TMD
 * @Date         : 2023-01-12 11:00:01
 * @LastEditTime : 2023-01-21 21:03:29
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
   * @return  返回日期和时间
   */
  void static inputNowTime(TYPE_ERROR_CASE& errorCase);
  std::unordered_map<TYPE_ERROR_CASE, std::string> static EC;
  std::unordered_map<TYPE_POWER, std::string> static TP;

 public:
  /**
   * @brief 获取时间和日期
   * @return  时间和日期
   */
  std::string static nowDataTime();
  /**
   * @brief 获取当前的日期
   * @return  日期
   */
  std::string static nowData();
  /**
   * @brief 系统开启记录
   * @return
   */
  void static open();
  /**
   * @brief 系统关闭记录
   * @return
   */
  void static close();
  Log();
  Log& operator=(const Log& tmp) = delete;
  Log(const Log& tmp) = delete;
  ~Log();
  /**
   * @brief 执行SQL
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string SQLPath SQL路径
   * @param  TYPE_ERROR_CASE errorCase 错误类型
   * @return
   */
  void static LogForExecuteSQL(std::string UserName,
                               TYPE_POWER op,
                               std::string SQLPath,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string _data 执行指令
   * @param TYPE_ERROR_CASE errorCase 错误类型
   * @return
   */
  void static LogForCompileError(std::string UserName,
                                 TYPE_POWER op,
                                 std::string _data,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param vCID command 指令
   * @param revstring data 数据
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForError(std::string UserName,
                          TYPE_POWER op,
                          vCID command,
                          revstring data,
                          TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 编译报错
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  revstring commandAndData 指令+数据
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForCompileError(std::string UserName,
                                 TYPE_POWER op,
                                 revstring commandAndData,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);

  /**
   * @brief 选择_数据库_DBID
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   */
  void static LogForSelectDatabase(std::string UserName,
                                   TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);

  /**
   * @brief 选择_数据库_表_DBID_TBID
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForSelectDatabaseTable(std::string UserName,
                                        TYPE_POWER op,
                                        std::string DBID,
                                        std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForShow(std::string UserName,
                         TYPE_POWER op,
                         TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示所有数据库
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForShowAllDatabase(std::string UserName,
                                    TYPE_POWER op,
                                    TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示_数据库_DBID
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForShowDatabase(std::string UserName,
                                 TYPE_POWER op,
                                 std::string DBID,
                                 TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 显示_数据库_表
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param string DBID 数据库名
   * @param string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForShowDatabaseTable(std::string UserName,
                                      TYPE_POWER op,
                                      std::string DBID,
                                      std::string TBID,
                                      TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 退出
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param TYPE_ERROR_CASE errorcase 失败原因
   * @return
   */
  void static LogForExit(std::string UserName,
                         TYPE_POWER op,
                         TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 登录
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string LoginID 登录ID
   * @param  string LoginPassword 登录密码
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForLogin(std::string UserName,
                          TYPE_POWER op,
                          std::string LoginID,
                          std::string LoginPassword,
                          TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_用户
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string ID 创建ID
   * @param  string Pd 创建密码
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForCreateUser(std::string UserName,
                               TYPE_POWER op,
                               std::string ID,
                               std::string Pd,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_管理员
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string ID 创建ID
   * @param  string Pd 创建密码
   * @param  TYPE_ERROR_CASE erorCase 失败原因
   * @return
   */
  void static LogForCreateManager(std::string UserName,
                                  TYPE_POWER op,
                                  std::string ID,
                                  std::string Pd,
                                  TYPE_ERROR_CASE erorCase = 顺利执行);
  /**
   * @brief 创建_数据库
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForCreateDatabase(std::string UserName,
                                   TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 创建_数据库_表
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForCreateDatabaseTable(std::string UserName,
                                        TYPE_POWER op,
                                        std::string DBID,
                                        std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_数据库
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForDeleteDatabase(std::string UserName,
                                   TYPE_POWER op,
                                   std::string DBID,
                                   TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_数据库_表
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForDeleteDatabaseTable(std::string UserName,
                                        TYPE_POWER op,
                                        std::string DBID,
                                        std::string TBID,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_用户
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string UID 删除用户名
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForDeleteUser(std::string UserName,
                               TYPE_POWER op,
                               std::string UID,
                               TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 删除_管理员
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string MID 删除管理员ID
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForDeleteManager(std::string UserName,
                                  TYPE_POWER op,
                                  std::string MID,
                                  TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 插入_数据库_表
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  revstring data 插入数据
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForInsertDatabaseTable(std::string UserName,
                                        TYPE_POWER op,
                                        std::string DBID,
                                        std::string TBID,
                                        revstring data,
                                        TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 查询_数据库_表
   * @param  string UserName 用户名
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库名
   * @param  string TBID 表名
   * @param  string Index 索引
   * @param  TYPE_ERROR_CASE errorCase 失败原因
   * @return
   */
  void static LogForFindDatabaseTable(std::string UserName,
                                      TYPE_POWER op,
                                      std::string DBID,
                                      std::string TBID,
                                      std::string Index,
                                      TYPE_ERROR_CASE errorCase = 顺利执行);
  /**
   * @brief 设置_索引_数据库_表
   * @param  string UserName 使用者
   * @param  TYPE_POWER op 权限
   * @param  string DBID 数据库
   * @param  string TBID 表
   * @param  std::string index 索引
   * @param  TYPE_ERROR_CASE errorCase 错误原因
   * @return
   */
  void static LogForSetIndexDatabaseTable(std::string UserName,
                                          TYPE_POWER op,
                                          std::string DBID,
                                          std::string TBID,
                                          std::string index,
                                          TYPE_ERROR_CASE errorCase = 顺利执行);
};

#endif