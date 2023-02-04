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
				 * @brief 加日志锁
				 */
				bool static addLog();
				/**
				 * @brief 解日志锁
				 */
				void static removeLog();
				/**
				 * @brief 加pd锁
				 */
				void static addPd();
				/**
				 * @brief 解pd锁
				 */
				void static removePd();
				void static addUser(std::string UserName);
				void static removeUser(std::string UserName);
				/**
				 * @brief 表锁
				 *
				 * @Param truePath 绝对路径
				 */
				void static addLock(std::string truePath);
				/**
				 * @brief 表锁
				 *
				 * @Param table 表对象
				 */
				void static addLock(Table& table);
				/**
				 * @brief 表锁
				 *
				 * @Param DBID 数据库名
				 * @Param TBID 表名
				 */
				void static addLock(std::string DBID, std::string TBID);
				/**
				 * @brief 解除表锁
				 *
				 * @Param table 表对象
				 */
				void static removeLock(Table& table);
				/**
				 * @brief 解除表锁
				 *
				 * @Param DBID 数据库名
				 * @Param TBID 表名
				 */
				void static removeLock(std::string DBID,std::string TBID);
				/**
				 * @brief 解除表锁
				 *
				 * @Param truePath 真实路径
				 */
				void static removeLock(std::string truePath);
				Lock();
				~Lock();
				Lock(const Lock& copy) = delete;
};
#endif
