/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2023-01-22 21:11:35
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
int Table::count = 0;

Table::Table(std::string databaseAndTableName, type style)
    : _file(databaseAndTableName, style) {
  this->style = style;
  ++Table::count;
}
Table::Table(DataBase database, std::string tableName, type style)
    : _file(database.returnName() + "/" + tableName, style) {
  this->style = style;
  ++Table::count;
}
Table::Table(std::string _truePath) : _file(_truePath) {
  this->style = _TYPE_NONE;
  ++Table::count;
}
Table::~Table() {
  --Table::count;
}

bool Table::create() {
  switch (style) {
    case type::_TYPE_PCB:
      return _file::create(this->returnName(), type::_TYPE_PCB);
      break;
    case type::_TYPE_INDEX_TABLE:
      return _file::create(this->returnName(), type::_TYPE_INDEX_TABLE);
      break;
    case type::_TYPE_TABLE:
      return _file::create(this->returnName(), type::_TYPE_TABLE) &&
             _file::create(this->returnName(), type::_TYPE_INDEX_TABLE) &&
             _file::create(this->returnName(), type::_TYPE_PCB) &&
             _file::create(this->returnName(), type::_TYPE_VIEW);
      break;
    case type::_TYPE_VIEW:
      return _file::create(this->returnName(), type::_TYPE_VIEW);
    default:
      break;
  }
  return false;
}
bool Table::remove() {
  switch (style) {
    case type::_TYPE_PCB:
      return _file::remove(this->returnName(), type::_TYPE_PCB);
    case type::_TYPE_VIEW:
      return _file::remove(this->returnName(), type::_TYPE_VIEW);
    case type::_TYPE_INDEX_TABLE:
      return _file::remove(this->returnName(), type::_TYPE_INDEX_TABLE);
    case type::_TYPE_TABLE:
      return _file::remove(this->returnName(), type::_TYPE_INDEX_TABLE) &&
             _file::remove(this->returnName(), type::_TYPE_TABLE) &&
             _file::remove(this->returnName(), type::_TYPE_PCB) &&
             _file::remove(this->returnName(), type::_TYPE_VIEW);
    default:
      break;
  }
  return false;
}
int Table::returnCount() {
  return Table::count;
}
bool Table::isExist() {
  return _super::isExist(this->returnName(), style);
}

void Table::updateIndex() {}

vstring Table::find(std::string index) {
  vstring value;
  INDEX indexcol = TablePCB(this->returnName()).returnIndex();
  Table indexFile(this->returnName(), type::_TYPE_INDEX_TABLE);
  while (indexFile.readline(value)) {
    if (value[indexcol] == index) {
      int x = atoi(value[1].c_str());
      return this->indexReadline(x);
    }
  }
  return {};
}

bool Table::append(vstring value) {
  TablePCB pcb(this->returnName());
  int fileIndex = pcb.returnEndLineIndex();
  int index = pcb.returnIndex();
  if (value.size() <= 0) {
    return false;
  }
  this->write(value, type_mode::WRITEBUFF_MODE_APP);
  if (fileIndex == 0) {
    this->appInsertIndex(value[index], 0);
  } else {
    this->appInsertIndex(value[index], fileIndex);
  }
  fileIndex += value.size();
  for (std::string& str : value) {
    fileIndex += str.size();
  }
  pcb.addLength();
  pcb.setEndLineIndex(fileIndex);
  return true;
}

Table::Table(Table& table) : _file(table.name, table.style) {
  this->style = table.style;
  ++this->count;
}
bool Table::append(Table table, vstring value) {
  return table.append(value);
}
bool Table::append(std::string tableName, vstring value) {
  Table tmp(tableName, type::_TYPE_TABLE);
  return tmp.append(value);
}
bool Table::appInsertIndex(std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(this->returnName(), index, fileIndex);
}
bool Table::appInsertIndex(std::string tableName,
                           std::string index,
                           POINTER fileIndex) {
  return _file::write(tableName, type::_TYPE_INDEX_TABLE,
                      {index, std::to_string(fileIndex)},
                      type_mode::WRITEBUFF_MODE_APP);
}
bool Table::appInsertIndex(Table table, std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(table.returnName(), index, fileIndex);
}

vstring Table::indexReadline(POINTER fileIndex) {
  POINTER oldIndex = this->returnReadTell();
  this->setOpenBuff(type_mode::READBUFF_MODE);
  this->setReadSeek(fileIndex);
  vstring value;
  this->readline(value);
  this->setReadSeek(oldIndex);
  return value;
}

vstring Table::indexReadline(std::string tableName, POINTER fileIndex) {
  Table _table(tableName, type::_TYPE_TABLE);
  return _table.indexReadline(fileIndex);
}

vstring Table::indexReadline(Table table, POINTER fileIndex) {
  return table.indexReadline(fileIndex);
}