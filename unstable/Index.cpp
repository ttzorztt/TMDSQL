/**
 * @file Index.cpp
 * @brief 封装索引操作
 * @author TMD
 * @date 2023-11-07
 */
#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"

#include <typeinfo>

#include "super.h"
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
  if (TablePCB(name).returnEndLineIndex() == 0) {  // 表不存在则无法执行
    return;
  }
  Table table(name, type::_TYPE_TABLE);
  _file oldIndex(name, type::_TYPE_INDEX_TABLE);
  if (!oldIndex.isExist() || !table.isExist()) {
    return;
  }
  vstring tablebuff;
  vstring vectorbuff;
  Table* tmp = new Table(name + "tmp", type::_TYPE_TABLE);
  if (tmp->isExist()) {
    tmp->remove();
  }
  tmp->create();
  vstring tmpbuff;
  INDEX indexcol = TablePCB(name).returnIndex();
	TablePCB * tmpPCB = new TablePCB(*tmp);
	tmpPCB->setIndex(indexcol);
	delete tmpPCB;
  while (table.readline(tmpbuff)) {
    tmp->append(tmpbuff);
  }
  _file(name + "tmp", type::_TYPE_PCB).remove();
  _file(name + "tmp", type::_TYPE_TABLE).remove();
  _file(name + "tmp", type::_TYPE_VIEW).remove();
  _file::rename(name + "tmp", name, type::_TYPE_INDEX_TABLE);
  delete tmp;
}
void Index::create(Table table) { Index::create(table.returnName()); }

void Index::create(_file file) { Index::create(file.returnName()); }
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
