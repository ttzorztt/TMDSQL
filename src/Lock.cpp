/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-11 22:06:32
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
#include <iostream>

//当前打开的锁的总数的数量
int Lock::count = 0;
//当前打开的文件锁的数量
int Lock::fileCount = 0;
//当前打开数据库锁的数量
int Lock::databaseCount = 0;
Lock::Lock(Lock& copy) {}

Lock::~Lock() {}
int Lock::returncount() {
  return count;
}
int Lock::returnFileCount() {
  return fileCount;
}
int Lock::returnDatabaseCount() {
  return databaseCount;
}
//不需要每个类实现静态remove，super一个就够了
bool Lock::remove(std::string Name, type style) {
  std::string truePath = _super::returnTruePath(Name, style);
  switch (_super::isExist(truePath)) {
    case true: {
      return !std::remove(truePath.c_str());
    }
    case false: {
      return false;
      break;
    }
  }
}

bool Lock::add(std::string Name, type style) {
  if (_super::isExist(Name, style)) {
    
    return false;
  }
  std::cout << _super::returnTruePath(Name, style) << std::endl;
  return _file::create(Name, style);
}

bool Lock::add(Table table) {
  return Lock::add(
      table.returnName(),
      type::_TYPE_TABLE_LOCK);
}

bool Lock::remove(Table table) {
  return Lock::remove(
      _super::returnTruePath(table.returnName(), type::_TYPE_TABLE_LOCK),
      type::_TYPE_TABLE_LOCK);
}

bool Lock::add(DataBase database) {
  return Lock::add(
      _super::returnTruePath(database.returnName(), type::_TYPE_TADABLASE_LOCK),
      type::_TYPE_TADABLASE_LOCK);
}
bool Lock::remove(DataBase database) {
  return Lock::remove(
      _super::returnTruePath(database.returnName(), type::_TYPE_TADABLASE_LOCK),
      type::_TYPE_TADABLASE_LOCK);
}