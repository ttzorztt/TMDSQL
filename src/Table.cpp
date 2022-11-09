/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-09 17:26:28
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
int Table::count = 0;
Table::Table(string databaseName, string stableName)
    : _file("../data/" + databaseName + "/" + stableName, type::_TYPE_FILE) {
  this->style = type::_TYPE_FILE;
  ++Table::count;
}
Table::Table(DataBase database, string tableName)
    : _file(database.returnPath() + "/" + tableName, type::_TYPE_FILE) {
  this->style = type::_TYPE_FILE;
  ++Table::count;
}
Table::Table(DataBase database, _file tableName)
    : _file(database.returnPath() + "/" + tableName.returnName(),
            type::_TYPE_FILE) {
  this->style = type::_TYPE_FILE;
  ++Table::count;
}
Table::~Table() {
    --Table::count;
}

bool Table::create() {
    return _file::create(this->path,style);
}
bool Table::remove() {
    return _file::remove(this->path,style);
}
int Table::returnCount() {
  return Table::count;
}
bool Table::isExist() {
  return _super::isExist(this->path, style);
}