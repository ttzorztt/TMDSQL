/**
 * @file BackTracking.h
 * @brief 回溯类
 * @author TMD
 * @date 2023-04-29
 */
#ifndef _BACKTRACKING_
#define _BACKTRACKING_
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
class BackTracking {
 private:
  /**
   * @brief 写入文件
   *
   * @param value 回溯指令语句
   * @param ptr 回溯指令的字节数+所需的空格
   */
  void static add(std::string value, int ptr);
  /**
   * @brief 回溯文件的状态,不存在则创建文件
   */
  void static backTrackingFileState();
  /**
   * @brief 数据清理(将数据按照回溯结构分为四部分)
   *
   * @param data 待清理的数据
   * @param returnData 返回的vvstring
   *
   * @return 简单判断数据是否有问题
   */
  bool static dataClear(revstring data, vvstring& returnData);
	void static aidForExecute(int command,vstring executeData);
  /**
   * @brief 回溯文件指针(仅用来尾插)
   */
  static _file* backTrackingFile;

 public:
  /**
   * @brief 在创建的前提下初始化内容。
   */
  void static init();
  BackTracking();
  ~BackTracking();
  BackTracking(const BackTracking& copy) = delete;
  /**
   * @brief 重生之我要创建用户
   *
   * @param UserName 用户名
   * @param Password 密码
   */
  void static BackTrackingForCreateUser(std::string UserName,
                                        std::string Password);
  /**
   * @brief 重生之我要创建管理员
   *
   * @param UserName 用户名
   * @param Password 密码
   */
  void static BackTrackingForCreateManager(std::string UserName,
                                           std::string Password);
  /**
   * @brief 重生之我要创建数据库(非空)
   *
   * @param DBID 数据库
   */
  void static BackTrackingForRecoverDatabase(std::string DBID);
  /**
   * @brief 重生之我要创建数据库表(非空)
   *
   * @param DBID 数据库
   * @param TBID 表
   */
  void static BackTrackingForRecoverDatabaseTable(std::string DBID,
                                                  std::string TBID);
	/**
	 * @brief 重生之我要创建数据库(空)
	 *
	 * @param DBID 数据库
	 */
  void static BackTrackingForCreateDatabase(std::string DBID);
	/**
	 * @brief 重生之我要创建数据库表(空)
	 *
	 * @param DBID 数据库
	 * @param TBID 表
	 */
  void static BackTrackingForCreateDatabaseTable(std::string DBID,
                                                 std::string TBID);
  /**
   * @brief 重生之我要删除数据库
   *
   * @param DBID 数据库
   */
  void static BackTrackingForDeleteDatabase(std::string DBID);
  /**
   * @brief 重生之我要删除数据库表
   *
   * @param DBID 数据库
   * @param TBID 表
   */
  void static BackTrackingForDeleteDatabaseTable(std::string DBID,
                                                 std::string TBID);
  /**
   * @brief 重生之我要删除用户
   *
   * @param UserName 用户名
   */
  void static BackTrackingForDeleteUser(std::string UserName);
  /**
   * @brief 重生之我要删除管理员
   *
   * @param UserName 用户名
   */
  void static BackTrackingForDeleteManager(std::string UserName);
  /**
   * @brief 重生之我要插入列数据库表
   *
   * @param DBID 数据库
   * @param TBID 表
   * @param ColData 列
   */
  void static BackTrackingForInsertColDatabaseTable(std::string DBID,
                                                    std::string TBID,
                                                    vstring ColData);
  /**
   * @brief 重生之我要删除行数据库表
   *
   * @param DBID 数据库
   * @param TBID 表
   * @param Row 行
   */
  void static BackTrackingForDeleteRowDatabaseTable(std::string DBID,
                                                    std::string TBID,
                                                    std::string Row);
  /**
   * @brief 重生之我要插入数据库表
   *
   * @param DBID 数据库
   * @param TBID 表
   * @param insertData vector for 插入数据
   */
  void static BackTrackingForInsertDatabaseTable(std::string DBID,
                                                 std::string TBID,
                                                 vstring insertData);
  /**
   * @brief 重生之我要设置数据库的视图
   *
   * @param DBID 数据库名
   * @param TBID 表名
   * @param User 用户
   * @param viewData vector for 视图数据
   */
  void static BackTrackingForSetViewDatabaseTable(std::string DBID,
                                                  std::string TBID,
                                                  std::string User,
                                                  vstring viewData);
  /**
   * @brief 重生之我要设置数据库表
   *
   * @param DBID 数据库
   * @param TBID 表
   * @param index 索引
   */
  void static BackTrackingForSetIndexDatabaseTable(std::string DBID,
                                                   std::string TBID,
                                                   std::string index);
  /**
   * @brief 重生之王妃清理回溯文件
   */
  void static Clear();
	/**
	 * @brief 重生之我要显示回溯文件
	 * 
	 * @param data 日期
	 */
	void static BackTrackingForShow(std::string data);
	/**
	 * @brief 重生之执行技能
	 *
	 * @param data 日期
	 * @param backTrackingPoint 回溯点
	 */
	void static BackTrackingForExecute(std::string data,int backTrackingPoint);
};
#endif
