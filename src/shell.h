/**
 * @file shell.h
 * @brief TMDSQL语言的设计与实现
 * @author TMD
 * @version 1.3
 * @date 2022-11-01
 */
#ifndef _SHELL_
#define _SHELL_
#ifndef _SET_
#define _SET_
#include <set>
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
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
class shell : public User {
	public:
		shell();
		~shell();
		/**
		 * @brief 读入数据
		 *
		 * @param  string data 数据
		 *
		 * @return 输入退出则返回False，否则返回True
		 */
		bool read(std::string data);
		/**
		 * @brief 读入数据
		 *
		 * @param  revstring data string数组
		 *
		 * @return  输入退出则返回False，否则返回True
		 */
		bool read(revstring data);
		/**
		 * @brief 记录所有执行过的指令
		 *
		 * @param str 指令字符串
		 */
		void addHistory(std::string& str);
		/**
		 * @brief 返回历史记录的上一条
		 *
		 * @return 执行字符串
		 */
		std::string prevHistory();
		/**
		 * @brief 返回历史记录的下一条
		 *
		 * @return 执行字符串
		 */
		std::string nextHistory();
		/**
		 * @brief 是否有历史
		 *
		 * @return 返回是否存在历史值
		 */
		bool hasHistory();
	private:
		// 当前工作路径
		vstring pwd;
		// 用户输入指令
		vCID command;
		// 用户输入数据
		vstring data;
		// 用户输入的指令计数
		int commandCount;
		// 是否需要显示提示符
		bool need;
		// 执行历史
		std::vector<std::string> history;
		// 历史的指针
		long unsigned historyIndex;
		/**
		 * @brief 判断是否输入"确认"
		 *
		 * @return  如果输入返回True，否则返回False
		 */
		bool inputACK();
		/**
		 * @brief 执行指令
		 *
		 * @return 输入退出则返回False，否则返回True
		 */
		bool read();
		/**
		 * @brief 语法检查以及指令与数据分类存储
		 *
		 * @param  string _str 待检查字符串
		 *
		 * @return 指令不存在问题的话，返回True，存在问题则返回false
		 */
		bool check(std::string _str);
		/**
		 * @brief 语法检查以及指令与数据分类存储
		 *
		 * @param  revstring value string 数组
		 *
		 * @return 指令的语法检查
		 */
		bool check(revstring value);
		/**
		 * @brief 语法检查是否含有'/'，'!'等违规字符
		 *
		 * @param  string _str 待检查字符
		 *
		 * @return 没有问题的话，返回true，否则返回false;
		 */
		bool aidCheckData(std::string _str);
		/**
		 * @brief 执行脚本
		 */
		void toExecute();
		/**
		 * @brief 输出选择后的操作
		 */
		void toChoose();
		/**
		 * @brief 输出选择表后的操作
		 */
		void toChooseTable();
		/**
		 * @brief 输入选择数据库后的操作
		 */
		void toChooseDatabase();
		/**
		 * @brief 输入选择数据库表后的操作
		 */
		void toChooseDatabaseTable();
		/**
		 * @brief 输入插入后的操作
		 */
		void toInsert();
		/**
		 * @brief 输入插入默认表后的操作
		 */
		void toInsertDefaultTable();
		/**
		 * @brief 输入插入表后的操作
		 */
		void toInsertTable();
		/**
		 * @brief 输入插入数据库表后的操作
		 */
		void toInsertDatabaseTable();
		/**
		 * @brief 登录操作
		 */
		void toLogin();
		/**
		 * @brief 输入查询后的操作
		 */
		void toFind();
		/**
		 * @brief 输入查询表后的操作
		 */
		void toFindTable();
		/**
		 * @brief 输入查询默认表的操作
		 */
		void toFindDefalutTable();
		/**
		 * @brief 输入查询数据库表后的操作
		 */
		void toFindDatabaseTable();
		/**
		 * @brief 输入设置后的操作
		 */
		void toSet();
		/**
		 * @brief 输入设置视图后的操作
		 */
		void toSetView();
		/**
		 * @brief 输入设置视图数据库表后的操作
		 */
		void toSetViewDatabaseTable();
		/**
		 * @brief 输入设置视图表后的操作
		 */
		void toSetViewTable();
		/**
		 * @brief 输入设置视图后的操作(默认表)
		 */
		void toSetViewDefault();
		/**
		 * @brief 输入设置索引后的操作
		 */
		void toSetIndex();
		/**
		 * @brief 输入设置索引(默认表)后的操作
		 */
		void toSetIndexDefault();
		/**
		 * @brief 输入设置索引数据库表后的操作
		 */
		void toSetIndexDatabaseTable();
		/**
		 * @brief 输入设置索引表后的操作
		 */
		void toSetIndexTable();
		/**
		 * @brief 输入显示后的操作
		 */
		void toShow();
		/**
		 * @brief 输入显示数据库后的操作
		 */
		void toShowDatabase();
		/**
		 * @brief 输入显示数据库表后的操作
		 */
		void toShowDatabaseTable();
		/**
		 * @brief 输入显示表后的操作
		 */
		void toShowTable();
		/**
		 * @brief 输入创建后的操作
		 */
		void toCreate();
		/**
		 * @brief 输入创建，表后的操作
		 */
		void toCreateTable();
		/**
		 * @brief 输入创建，数据库后的操作
		 */
		void toCreateDatabase();
		/**
		 * @brief 输入创建 数据库 表后的操作
		 */
		void toCreateDatabaseTable();
		/**
		 * @brief 输入删除后的操作
		 */
		void toDelete();
		/**
		 * @brief 输入删除表后的操作
		 */
		void toDeleteTable();
		/**
		 * @brief 输入删除数据库后的操作
		 */
		void toDeleteDatabase();
		/**
		 * @brief 输入删除数据库表后的操作
		 */
		void toDeleteDatabaseTable();
		/**
		 * @brief 输入删除行数据库表后的操作
		 */
		void toDeleteRowDatabaseTable();
		/**
		 * @brief 输入删除行表后的操作
		 */
		void toDeleteRowTable();
		/**
		 * @brief 输入删除行后的操作
		 */
		void toDeleteRow();
		/**
		 * @brief 输入删除列数据库表后的操作
		 */
		void toDeleteColDatabaseTable();
		/**
		 * @brief 输出删除列表后的操作
		 */
		void toDeleteColTable();
		/**
		 * @brief 输出删除列后的操作
		 */
		void toDeleteCol();
		/**
		 * @brief 输入删除用户后的操作
		 */
		void toDeleteUser();
		/**
		 * @brief 输入删除用户后的操作
		 */
		void toDeleteManager();
};
#endif
