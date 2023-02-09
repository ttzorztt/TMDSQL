/**
 * @file Index.cpp
 * @brief 封装索引操作
 * @author TMD
 * @version 1.3
 * @date 2023-11-07
 */
#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef TABLEPCB_H_
#define TABLEPCB_H_
#include "TablePCB.h"
#endif
#include <iostream>
Index::Index() {}
Index::~Index() {}
void Index::update(std::string name) {
  _file oldIndex(name, type::_TYPE_INDEX_TABLE);
  Table table(name, type::_TYPE_TABLE);
  if (!oldIndex.isExist() || !table.isExist()) {
    return;
  }
  INDEX indexcol = TablePCB(name).returnIndex();
  vstring tablebuff;
  vstring vectorbuff;
  oldIndex.readline(vectorbuff);
  table.readline(tablebuff);
  int size = tablebuff.size();
  for (int a = 0; a < size; ++a) {
    if (tablebuff[a] == vectorbuff[0]) {
      if (a == indexcol) {  // 不需要更新
        return;
      } else {
        break;
      }
    }
  }
  _file newIndex( name + "_tmp" , type::_TYPE_INDEX_TABLE);
  if (newIndex.isExist()) {
    newIndex.remove();
  }else{
    newIndex.create();
  }
  vectorbuff[0] = tablebuff[indexcol];
  newIndex.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
  while (oldIndex.readline(vectorbuff) && table.readline(tablebuff)) {
    vectorbuff[0] = tablebuff[indexcol];
    newIndex.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
  }
  rename(_super::returnTruePath(newIndex.returnName(), type::_TYPE_INDEX_TABLE)
             .c_str(),
         _super::returnTruePath(oldIndex.returnName(), type::_TYPE_INDEX_TABLE)
             .c_str());
}
void Index::create(Table table) {
  Index::create(table.returnName());
}

void Index::create(_file file) {
  Index::create(file.returnName());
}
void Index::create(std::string tableName) {
  _file indexFile(tableName, type::_TYPE_INDEX_TABLE);
  _file dataFile(tableName, type::_TYPE_TABLE);
  if (indexFile.isExist()) {
    indexFile.remove();
  }
  indexFile.create();
  if (!indexFile.isExist() || !dataFile.isExist()) {
    return;
  }
  vstring value;
  int size = 0;
  while (dataFile.readline(value)) {
    for (std::string& str : value) {
      size += str.size();
    }
    indexFile.write({value[0], std::to_string(size)},
                    type_mode::WRITEBUFF_MODE_APP);
  }
}
