/**
 * @file Lock.h
 * @brief 封装锁操作
 * @author TMD
 * @version 1.3
 * @date 2022-11-07
 */
#ifndef _LOCK_
#define _LOCK_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class Lock {
	private:
	public:
		/**
		 * @brief add Log lock
		 *
		 * @return is or not access
		 */
		bool static addLogLock();
		/**
		 * @brief remove log lock
		 */
		void static removeLogLock();
		/**
		 * @brief add pd Read lock
		 *
		 * @return is or not access
		 */
		bool static addReadPdLock();
		/**
		 * @brief add pd write lock
		 *
		 * @Return is or not access
		 */
		bool static addWritePdLock();
		/**
		 * @brief remove pd read lock
		 */
		void static removeReadPdLock();
		/**
		 * @brief remove pd write lock
		 */
		void static removeWritePdLock();
		/**
		 * @brief add User Read lock
		 *
		 * @Param UserName User name 
		 *
		 * @return is or not access
		 */
		bool static addReadUser(std::string UserName);
		/**
		 * @brief add User Write lock
		 *
		 * @Param UserName User name
		 *
		 * @Return is or not access
		 */
		bool static addWriteUserLock(std::string UserName);
		/**
		 * @brief remove User Read lock
		 *
		 * @Param UserName User name
		 */
		void static removeReadUser(std::string UserName);
		/**
		 * @brief remove User write Lock
		 *
		 * @Param UserName User name
		 */
		void static removeWriteLock(std::string UserName);
		/**
		 * @brief add read lock
		 *
		 * @param truePath the full path
		 *
		 * @return is or not access
		 */
		bool static addReadLock(std::string truePath);
		/**
		 * @brief add write lock
		 *
		 * @Param truePath the full path
		 *
		 * @Return is or not accesss
		 */
		bool static addWriteLock(std::string truePath);
		/**
		 * @brief add Read lock
		 *
		 * @Param table the table who need add lock
		 *
		 * @return is or not access
		 */
		bool static addReadLock(Table& table);
		/**
		 * @brief add Write lock
		 *
		 * @Param table the table who need add lock
		 *
		 * @Return is or not access
		 */
		bool static addWriteLock(Table& table);
		/**
		 * @brief add Read lock
		 *
		 * @Param file the file who need add lock
		 *
		 * @return is or not access
		 */
		bool static addReadLock(_file& file);
		/**
		 * @brief add Wirte lock
		 *
		 * @Param file the table who need add lock
		 *
		 * @Return is or not access
		 */
		bool static addWriteLock(_file& file);
		/**
		 * @brief remove Read lock
		 *
		 * @Param file the file who need remove read lock
		 */
		void static removeReadLock(_file& file);
		/**
		 * @brief remove Wriete lock
		 *
		 * @Param file the file who need remove write lock
		 */
		void static removeWriteLock(_file& file);
		/**
		 * @brief add Read Lock
		 *
		 * @Param DBID Database name
		 * @Param TBID Table name
		 *
		 * @return is or not access
		 */
		bool static addReadLock(std::string DBID, std::string TBID);
		/**
		 * @brief add Write Lock
		 *
		 * @Param DBID Database name
		 * @Param TBID Table name
		 *
		 * @Return is or not access
		 */
		bool static addWriteLock(std::string DBID,std::string TBID);
		/**
		 * @brief remove Read Lock
		 *
		 * @Param table The Table object who need rmove read lock
		 */
		void static removeReadLock(Table& table);
		/**
		 * @brief remove write lock
		 *
		 * @Param table The Table object who need remove write lock
		 */
		void static removeWriteLock(Table& table);
		/**
		 * @brief remove Read Lock
		 *
		 * @Param DBID Database Name
		 * @Param TBID Table name
		 */
		void static removeReadLock(std::string DBID, std::string TBID);
		/**
		 * @brief remove Write Lock
		 *
		 * @Param DBID Database name
		 * @Param TBID Table name
		 */
		void static removeWriteLock(std::string DBID,std::string TBID);
		/**
		 * @brief remove Read Lock
		 *
		 * @Param truePath the full path
		 */
		void static removeReadLock(std::string truePath);
		/**
		 * @brief remove write lock
		 *
		 * @Param truePath the full path
		 */
		void static removerWriteLock(std::string truePath);
		Lock();
		~Lock();
		Lock(const Lock& copy) = delete;
};
#endif
