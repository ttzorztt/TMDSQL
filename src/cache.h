/**
 * @file cache.h
 * @brief 索引添加进缓存
 * @author TMD
 * @version 1.4
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
#define CACHEPOLL 5
class Cache{
	private:
		/* 文件包含 */
		static std::set<std::string> fileInclue;
		/* 缓存 */
		static std::vector<std::map<std::string,int>> cache;
		/* 文件名到chache下标的映射 */
		static std::map<std::string,int> fileToIndex;
		/* 下一个存储的位置 */
		static int stap;
		/* 使用最近最久未被使用的替换算法 */
		static std::vector<std::pair<int,std::string>> cacheCount;
		/**
		 * @brief cacheCount的自增,主要是进行替换算法。
		 *
		 * @Param fileName 文件名
		 *
		 * @Return 被替换的文件名(PS:如果不需要则返回"")
		 */
		std::string static cacheCountAdd(std::string& fileName);
	public:
		Cache();
		~Cache();
		/**
		 * @brief 添加一行内容。如果说这个文件没有在Cache中，则会添加，如果在的话，自然就是把新添加的部分添加到Cache中，emmm，同时也对硬盘写入。所以骚年，安心使用无脑Ctrl+C吧
		 *
		 * @Param fileName
		 * @Param std::pair
		 */
		void addLine(std::string fileName,std::pair<std::string, int>);
		Cache(const Cache& copy) = delete;
		/**
		 * @brief 入缓存
		 *
		 * @Param file 文件对象
		 */
		void static add(Table& file);
		/**
		 * @brief 查找，如果找不到则返回{}
		 *
		 * @Param file 表对象
		 * @Param index 索引
		 *
		 * @Return 查询结果
		 */
		vstring static find(Table file,std::string index);
		/**
		 * @brief 判断Cache中有无文件
		 *
		 * @Param file 表对象
		 *
		 * @Return 是返回True，否返回False
		 */
		bool static Count(Table& file);
};

#endif
