/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:51
 * @LastEditTime : 2022-11-19 20:26:47
 */

#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#include <iostream>
Index::Index() {}

Index::~Index() {}

void Index::update(std::string name) {
  _file oldIndex(name, type::_TYPE_INDEX_TABLE);
  if (!oldIndex.isExist()) {
    Index::create(oldIndex);
    return;
  }
  _file newIndex(name + ".", type::_TYPE_INDEX_TABLE);
  if (newIndex.isExist()) {
    newIndex.remove();
  }
  newIndex.create();
  std::vector<std::string> value;
  oldIndex.readline(value);
  int tmpcount = std::atoi(value[value.size() - 1].c_str());

  newIndex.write(value);
  while (oldIndex.readline(value)) {
    int size = std::atoi(value[value.size() - 1].c_str());
    tmpcount += size;
    value[value.size() - 1] = std::to_string(tmpcount);
    newIndex.write(value);
  }
  oldIndex.remove();
  rename(_super::returnTruePath(newIndex.returnName(), type::_TYPE_INDEX_TABLE)
             .c_str(),
         _super::returnTruePath(oldIndex.returnName(), type::_TYPE_INDEX_TABLE)
             .c_str());
}
void Index::update(Table table) {
  Index::update(table.returnName());
}

void Index::create(Table table) {
  Index::create(table.returnName());
}

void Index::create(_file file) {
  Index::create(file.returnName());
}
void Index::create(std::string tableName) {
  _file indexFile(tableName,type::_TYPE_INDEX_TABLE);
  _file dataFile(tableName,type::_TYPE_TABLE);
  if(indexFile.isExist()){
    indexFile.remove();
  }
  indexFile.create();
if(!indexFile.isExist() || !dataFile.isExist()){
    return;
  }
  std::vector<std::string> value;
  int size = 0;
  while(dataFile.readline(value)){
    for(std::string& str: value){
      size += str.size();
    }
    indexFile.write({value[0],std::to_string(size)});
  }
  
}