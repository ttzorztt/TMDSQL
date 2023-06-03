/**
 * @file view.h
 * @brief 视图层的实现
 * @author TMD
 * @date 2023-02-09
 */
#ifndef _VIEW_
#define _VIEW_
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class View {
	private:
		/**
		 * @brief 辅助辅助返回视图
		 *
		 * @param  string& UserName 用户名
		 * @param  _file& file 视图文件
		 *
		 * @return  用户视图
		 */
		std::set<int> static returnAllowColumn(std::string& UserName, _file& file);

	public:
		View();
		View(const View& copy) = delete;
		~View();
		/**
		 * @brief 设置视图
		 *
		 * @param  string UserName 操作对象
		 * @param  vector<std::string> allowColumn 允许的列
		 * @param  string DBID 数据库名
		 * @param  string TBID 表名
		 */
		void static setAllowShowColumn(std::string UserName,
				std::vector<std::string> allowColumn,
				std::string DBID,
				std::string TBID);
		/**
		 * @brief  返回用户的视图
		 *
		 * @param  string UserName 用户名
		 * @param  string DBID 数据库名
		 * @param  string TBID 表名
		 *
		 * @return 用户的视图(Set)
		 */
		std::set<int> static returnAllowColumn(std::string UserName,
				std::string DBID,
				std::string TBID);
		/**
		 * @brief 返回用户的视图
		 *
		 * @param  string UserName 用户名
		 * @param  string DatabaseAndTableName 数据库名 + "/" + 表名
		 *
		 * @return 用户的视图(Set)
		 */
		std::set<int> static returnAllowColumn(std::string UserName,
				std::string DatabaseAndTableName);
		void static deleteColUpdate(std::string DatabaseAndTableName,std::string colnumber);
};
#endif
