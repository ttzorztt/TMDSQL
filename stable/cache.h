/**
 * @file cache.h
 * @brief 索引添加进缓存
 * @author TMD
 * @date 2023-02-24
 */
#ifndef _CACHE_
#define _CACHE_
#include <utility>
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _MAP_
#define _MAP_
#include <map>
#endif
class Cache{
	private:
		/* 文件包含 */
		static std::set<std::string> fileInclue;
		/* 缓存,只记录索引 */
		static std::vector<std::map<std::string,int>> cache;
		/* 文件名到chache下标的映射 */
		static std::map<std::string,int> fileToIndex;
		/* 下一个存储的位置 */
		static int stap;
		/* 使用最近最久未被使用的替换算法 */
		static std::vector<std::pair<int,std::string>> cacheCount;
		/**
		 * @brief 新进入的文件，首先查看cache中是否有该文件，如果当前内存不够poll的话，就返回""。 (时刻运行)
		 *
		 * @param fileName 新文件名
		 *
		 * @return 被替换的文件名(PS:如果不需要则返回"")
		 */
		std::string static update(std::string fileName);
	public:
		Cache();
		~Cache();
		/**
		 * @brief 往内存中添加数据
		 *
		 * @param TableName 表名
		 * @param addIndex 添加的数据索引
		 * @param fileIndex 文件索引
		 */
		void static addTableItem(std::string TableName,std::string addIndex,int fileIndex);
		/**
		 * @brief 往内存中添加数据
		 *
		 * @param table 表名
		 * @param addIndex 添加数据索引
		 * @param fileIndex 文件索引
		 */
		void static addTableItem(Table& table,std::string addIndex,int fileIndex);
		/**
		 * @brief 内存中删除数据
		 *
		 * @param TableName 表名
		 * @param deleteIndex 删除数据索引
		 */
		void static deleteTableItem(std::string TableName,std::string deleteIndex);
		/**
		 * @brief 删除数据
		 *
		 * @param table 表名
		 * @param deleteIndex 删除数据行索引
		 */
		void static deleteTableItem(Table& table,std::string deleteIndex);
		Cache(const Cache& copy) = delete;
		/**
		 * @brief 入缓存
		 *
		 * @param file 文件对象
		 */
		void static add(Table file);
		/**
		 * @brief 查找，如果找不到则返回{}
		 *
		 * @param file 表对象
		 * @param index 索引
		 *
		 * @return 查询结果
		 */
		vstring static find(Table file,std::string index);
		/**
		 * @brief 判断Cache中有无文件
		 *
		 * @param file 表对象
		 *
		 * @return 是返回True，否返回False
		 */
		bool static Count(Table& file);
		/**
		 * @brief 测试输出(DEBUG)
		 */
		void static test_show();
};

#endif
