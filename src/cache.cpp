/**
 * @file cache.cpp
 * @brief 索引添加进缓存
 * @author TMD
 * @version 1.4
 * @date 2023-02-24
 */

#ifndef _CACHE_H_
#define _CACHE_H_
#include "cache.h"
#endif
#ifndef _CSTDLIB_
#define _CSTDLIB_
#include <cstdlib>
#endif
std::set<std::string> Cache::fileInclue;
std::vector<std::map<std::string,int>> Cache::cache;
std::map<std::string,int> Cache::fileToIndex;
int Cache::stap = 0;
Cache::Cache(){
	/* 存储5个文件的cache */
	cache.resize(5);
}
Cache::~Cache(){
}
void Cache::add(Table& file){
	std::string filename = file.returnName();
	if(fileInclue.count(filename)){
		return;
	}
	fileInclue.insert(filename);
	cache[stap].clear();
	fileToIndex[filename] = stap;
	vstring tmp;
	while(file.readline(tmp)){
		cache[stap][tmp[0]] = atoi(tmp[1].c_str());
	}	
	stap = (stap + 1) % 5;
}
vstring Cache::find(Table &file, std::string index){

}
