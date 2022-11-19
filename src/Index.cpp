/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:51
 * @LastEditTime : 2022-11-19 15:02:20
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
int Index::count = 0;
Index::Index() {
  ++Index::count;
}

Index::~Index() {}

int Index::returnCount() {
  return Index::count;
}

void Index::update(std::string name) {
  _file oldIndex(name, type::_TYPE_INDEX_TABLE);
  _file newIndex(name + ".", type::_TYPE_INDEX_TABLE);

  // rename(truePath.c_str(), oldPath.c_str());

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
}
void Index::update(Table table) {
  Index::update(table.returnName());
}