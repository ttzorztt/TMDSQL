/**
 * @file DataBase.cpp
 * @brief 实现DataBase类中的一些操作
 * @author TMD
 * @version 1.3
 * @date 2023-11-01
 */
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
// 打开的数据库的个数
int DataBase::count = 0;
DataBase::DataBase(std::string name) : _dir(name, type::_TYPE_DATABASE) {
  ++this->count;
  vstring buff;
  _dir::openDirReturnFileName(returnTruePath(), buff);
  for (std::string& str : buff) {
    SetOfTable.insert(str);
  }
}
DataBase::DataBase(DataBase& databse)
    : _dir(databse.returnName(), type::_TYPE_DATABASE) {
  ++this->count;
  vstring buff;
  _dir::openDirReturnFileName(returnTruePath(), buff);
  for (std::string& str : buff) {
    SetOfTable.insert(str);
  }
}
type DataBase::returnType() {
  return type::_TYPE_DATABASE;
}
bool DataBase::create() {
  return DataBase::create(this->name);
}
bool DataBase::create(std::string name) {
  return _dir::create(_super::returnTruePath(name, type::_TYPE_DATABASE)) &&
         _dir::create(
             _super::returnTruePath(name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::create(_super::returnTruePath(name, type::_TYPE_VIEW)) &&
         _dir::create(
             _super::returnTruePath(name, type::_TYPE_CREATE_PCB_DATABASE));
}
bool DataBase::remove(std::string name) {
  return _dir::remove(_super::returnTruePath(name, type::_TYPE_DATABASE)) &&
         _dir::remove(
             _super::returnTruePath(name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::remove(_super::returnTruePath(name, type::_TYPE_VIEW)) &&
         _dir::remove(
             _super::returnTruePath(name, type::_TYPE_CREATE_PCB_DATABASE));
}
DataBase::~DataBase() {
  --DataBase::count;
}
bool DataBase::insertTable(std::string tableName) {
  bool tmp =
      _file::create(this->returnName() + "/" + tableName, type::_TYPE_TABLE);
  if (tmp) {
    SetOfTable.insert(tableName);
    return true;
  }
  return false;
}
bool DataBase::insertTable(std::string tableName,revstring tableItem) {
  Table::append(returnName() + "/" + tableName, tableItem);
  SetOfTable.insert(tableName);
  return true;
}
int DataBase::returnCount() {
  return DataBase::count;
}
void DataBase::forceremove() {
  vstring vectorbuff;
  this->openDirReturnFileName(vectorbuff);
  for (std::string& str : vectorbuff) {
    Table(name + "/" + str, type::_TYPE_TABLE).remove();
  }
  this->remove();
}
bool DataBase::isExist() {
  return access(
             _super::returnTruePath(this->name, type::_TYPE_DATABASE).c_str(),
             F_OK) != -1;
}
bool DataBase::isExist(std::string DataBaseName) {
  if (access(DataBaseName.c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}

bool DataBase::removeTable(std::string tableName) {
  return _file::remove(this->returnName() + "/" + tableName, type::_TYPE_TABLE);
}
bool DataBase::isExistsTable(std::string DataBaseName, std::string tableName) {
  vstring buff;
  _dir::openDirReturnFileName(
      _super::returnTruePath(DataBaseName, type::_TYPE_DATABASE), buff);
  for (std::string& str : buff) {
    if (str == tableName) {
      return true;
    }
  }
  return false;
}

bool DataBase::remove() {
  return DataBase::remove(this->name);
}
