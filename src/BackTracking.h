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
	 void static add(std::string value,int ptr);
	 /**
		* @brief 回溯文件的状态,不存在则创建文件
		*/
	 void static backTrackingFileState();
	 /**
		* @brief 数据清理(将数据按照回溯结构分为三部分)
		*
		* @param data 待清理的数据
		* @param returnData 返回的vvstring
		*
		* @return 简单判断数据是否有问题
		*/
	 bool static dataClear(revstring data,vvstring& returnData);
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
	 * @brief 
	 *
	 * @param UserName
	 * @param Password
	 */
  void static BackTrackingForCreateUser(std::string UserName, std::string Password);
  void static BackTrackingForCreateManager(std::string UserName, std::string Password);
  void static BackTrackingForCreateDatabase(std::string DBID);
  void static BackTrackingForCreateDatabaseTable(std::string DBID, std::string TBID);
  void static BackTrackingForDeleteDatabase(std::string DBID);
  void static BackTrackingForDeleteDatabaseTable(std::string DBID, std::string TBID);
  void static BackTrackingForDeleteUser(std::string UserName);
  void static BackTrackingForDeleteManager(std::string UserName);
  void static BackTrackingForDeleteColDatabaseTable(std::string DBID, std::string TBID,
                                     int Col, revstring ColData);
  void static BackTrackingForDeleteRowDatabaseTable(std::string DBID, std::string TBID,
                                     int Row, revstring RowData);
  void static BackTrackingForInsertDatabaseTable(std::string DBID, std::string TBID,
                                  revstring insertData);
  void static BackTrackingForSetViewDatabaseTable(std::string DBID, std::string TBID,
                                   revstring viewData);
  void static BackTrackingForSetIndexDatabaseTable(std::string DBID, std::string TBID,
                                    int index);
	/**
	 * @brief 测试逻辑
	 */
	void static test_Read();
};
#endif
