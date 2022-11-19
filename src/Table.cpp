/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-19 22:14:01
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif

int Table::count = 0;
Table::Table(std::string databaseAndTableName, type style)
    : _file(databaseAndTableName, style) {
  this->style = type::_TYPE_TABLE;
  ++Table::count;
}
Table::Table(DataBase database, std::string tableName, type style)
    : _file(database.returnName() + "/" + tableName, style) {
  this->style = type::_TYPE_TABLE;
  ++Table::count;
}

Table::~Table() {
  --Table::count;
}

bool Table::create() {
  return _file::create(this->name, type::_TYPE_INDEX_TABLE) &&
         _file::create(this->name, type::_TYPE_TABLE);
}
bool Table::remove() {
  return _file::remove(this->name, type::_TYPE_INDEX_TABLE) &&
         _file::remove(this->name, type::_TYPE_TABLE);
}
int Table::returnCount() {
  return Table::count;
}
bool Table::isExist() {
  return _super::isExist(this->name, style);
}

void Table::updateIndex() {}
std::vector<std::string> Table::find(std::string index) {
  std::vector<std::string> value;
  Table indexFile(this->name, type::_TYPE_INDEX_TABLE);
  while (indexFile.readline(value)) {
    if (value[0] == index) {
      int x = atoi(value[1].c_str());
    }
  }
  return {};
}

bool Table::append(std::vector<std::string> value) {
  return Table::append(this->name, value);
}
bool Table::append(Table table, std::vector<std::string> value) {
  return Table::append(table.returnName(), value);
}
bool Table::append(std::string tableName, std::vector<std::string> value) {
  int fileIndex = 0;
  if (value.size() <= 0) {
    return false;
  }
  for (std::string& str : value) {
    fileIndex += str.size();
  }
  if (!_file::write(tableName, type::_TYPE_TABLE, value)) {
    return false;
  }
  return Table::appInsertIndex(tableName, value[0], fileIndex + 1);
}
bool Table::appInsertIndex(std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(this->name, index, fileIndex);
}
bool Table::appInsertIndex(std::string tableName,
                           std::string index,
                           POINTER fileIndex) {
  return _file::write(tableName, type::_TYPE_INDEX_TABLE,
                      {index, std::to_string(fileIndex)});
}
bool Table::appInsertIndex(Table table, std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(table.returnName(), index, fileIndex);
}

std::vector<std::string> Table::indexReadline(POINTER fileIndex) {
  POINTER oldIndex = returnReadTell();
  setReadSeek(fileIndex);
  std::vector<std::string> value;
  this->readline(value);
  setReadSeek(oldIndex);
  return value;
}

std::vector<std::string> Table::indexReadline(std::string tableName,
                                              POINTER fileIndex) {
  Table _table(tableName, type::_TYPE_TABLE);
  return _table.indexReadline(fileIndex);
}

std::vector<std::string> Table::indexReadline(Table table, POINTER fileIndex) {
  return table.indexReadline(fileIndex);
}