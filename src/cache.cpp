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
#include <queue>
#include <utility>
#include <vector>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _CSTDLIB_
#define _CSTDLIB_
#include <cstdlib>
#endif
#ifndef _ALGORITHM_
#define _ALGORITHM_
#include <algorithm>
#endif
std::set<std::string> Cache::fileInclue;
std::vector<std::map<std::string,int>> Cache::cache;
std::map<std::string,int> Cache::fileToIndex;
int Cache::stap = 0;
std::vector<std::pair<int,std::string>> Cache::cacheCount;
Cache::Cache(){
	cache.resize(CACHEPOLL);
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
	int seek = file.returnReadTell();
	file.setReadSeek(0);
	_file index(file.returnName(),type::_TYPE_INDEX_TABLE);
	while(index.readline(tmp)){
		/* cache[stap].insert(std::make_pair(tmp[0],std::atoi(tmp[1].c_str()))); */
		cache[stap][tmp[0]] = atoi(tmp[1].c_str());
	}
	stap = (stap + 1) % 5;
	file.setReadSeek(seek);
}
vstring Cache::find(Table& file, std::string index){
	std::string fileName = file.returnName();
	if(!fileInclue.count(fileName)){
		return {};
	}
	/* 获取文件指针 */
	int ptr = cache[fileToIndex[fileName]][index];
	return file.indexReadline(ptr);
}
bool Cache::Count(Table &file){
	return fileInclue.count(file.returnName());
}
std::string Cache::cacheCountAdd(std::string& fileName){
	for (auto& init: cacheCount){
		if(init.second == fileName){
			init.first = 0;
			continue;
		}
		++(init.first);
	}
	std::sort(cacheCount.begin(),cacheCount.end()); 
	if(cacheCount.size() < CACHEPOLL){
		return "";
	}else{
		return cacheCount[0].second;
	}
}
void Cache::addLine(std::string fileName, std::pair<std::string, int>){
	if(!fileInclue.count(fileName)){
		return;  
	}
	
}

