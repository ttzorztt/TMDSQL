/**
 * @file cache.h
 * @brief 索引添加进缓存
 * @author TMD
 * @version 1.4
 * @date 2023-02-24
 */
#ifndef _CACHE_
#define _CACHE_
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
		/* 缓存 */
		static std::vector<std::map<std::string,int>> cache;
		/* 文件名到chache下标的映射 */
		static std::map<std::string,int> fileToIndex;
		/* 下一个存储的位置 */
		static int stap;
	public:
		Cache();
		~Cache();
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
		vstring static find(Table& file,std::string index);
};

#endif
