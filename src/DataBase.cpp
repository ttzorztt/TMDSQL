/*
 * @Description  : 实现DataBase类中的一些操作
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:27:53
 * @LastEditTime : 2022-11-30 21:12:14
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
DataBase::DataBase(std::string name) : _dir(name, type::_TYPE_DATABASE) {}
DataBase::DataBase(DataBase& databse)
    : _dir(databse.returnName(), type::_TYPE_DATABASE) {
  ++this->count;
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
         _dir::create(
             _super::returnTruePath(name, type::_TYPE_CREATE_PCB_DATABASE));
}
bool DataBase::remove(std::string name) {
  return _dir::remove(_super::returnTruePath(name, type::_TYPE_DATABASE)) &&
         _dir::remove(
             _super::returnTruePath(name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::remove(
             _super::returnTruePath(name, type::_TYPE_CREATE_PCB_DATABASE));
}
DataBase::~DataBase() {
  --DataBase::count;
}
bool DataBase::insertTable(std::string tableName) {
  // std::string Path = _super::returnTruePath(this->returnName() + "/" +
  // tableName,type::_TYPE_TABLE);
  return _file::create(this->returnName() + "/" + tableName, type::_TYPE_TABLE);
}

bool DataBase::insertTable(std::string tableName,
                           const std::vector<std::string>& tableItem) {
  std::string Path = returnName() + "/" + tableName;
  if (!_super::isExist(Path, type::_TYPE_TABLE)) {
    _file::create(Path, type::_TYPE_TABLE);
    _file::create(Path, type::_TYPE_INDEX_TABLE);
  }
  std::cout << Table::append(Path, tableItem);
  return true;
}
int DataBase::returnCount() {
  return DataBase::count;
}

void DataBase::showDataBaseTable() {
  std::string tmpPath =
      _super::returnTruePath(this->name, type::_TYPE_DATABASE);
  if (!_super::isExist(tmpPath)) {
    std::cout << "数据库不存在!" << std::endl;
    return;
  }
  std::vector<std::string> ans = _super::openDirReturnFileName(
      _super::returnTruePath(this->name, type::_TYPE_DATABASE));
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "这个数据库是空的!" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  maxtablename += 2;
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "|";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "|";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
}

void DataBase::showDataBase() {
  std::vector<std::string> ans =
      _super::openDirReturnFileName("../data/database/");
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "暂时还没有建立数据库" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  maxtablename += 2;
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "?";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "?";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
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

bool DataBase::removeDataBase(std::string DataBaseName) {
  return _dir::remove("../data/database/" + DataBaseName);
}

bool DataBase::remove() {
  return DataBase::remove(this->name);
}