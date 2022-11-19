/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-19 15:15:30
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
#include <iostream>

//当前打开的锁的总数的数量
int Lock::count = 0;
//当前打开的文件锁的数量
int Lock::tableCount = 0;
//当前打开数据库锁的数量
int Lock::databaseCount = 0;

Lock::Lock(Lock& copy) : _super(copy.returnName()) {
  this->style = copy.returnType();
  newLockAddCount();
}
Lock::Lock(std::string name, type style) : _super(name) {
  this->style = style;
  newLockAddCount();
}
Lock::Lock(Table table) : _super(table.returnName()) {
  this->style = type::_TYPE_TABLE;
  ++tableCount;
  ++count;
}
Lock::Lock(DataBase database) : _super(database.returnName()) {
  this->style = type::_TYPE_TADABLASE_LOCK;
  ++databaseCount;
  ++count;
}
Lock::~Lock() {
  switch (style)
  {
  case type::_TYPE_TABLE_LOCK :
    --tableCount;
    break;
  case type:: _TYPE_TADABLASE_LOCK:
    --databaseCount;
    break;
  default:
    break;
  }
  --count;
}
   bool Lock::create(){
    return Lock::add(this->name,style);
   }
   bool Lock::remove(){
    return Lock::remove(this->name,style);
   }
   int Lock::returnCount(){
    return count;
   }
   bool Lock::isExist(){
    return _super::isExist(this->name,style);
  }
  bool Lock::isExist(std::string name,type style){
    return _super::isExist(name,style);
  }
void Lock::newLockAddCount() {
  switch (this->style) {
    case type::_TYPE_TABLE_LOCK:
      this->tableCount++;
      break;
    case type::_TYPE_TADABLASE_LOCK:
      this->databaseCount++;
      break;
    default:
      break;
  }
  ++this->count;
}
int Lock::returnTableCount() {
  return tableCount;
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
  return _file::create(Name, style);
}

bool Lock::add(Table table) {
  return Lock::add(table.returnName(), type::_TYPE_TABLE_LOCK);
}

bool Lock::remove(Table table) {
  return Lock::remove(table.returnName(), type::_TYPE_TABLE_LOCK);
}

bool Lock::add(DataBase database) {
  return Lock::add(database.returnName(), type::_TYPE_TADABLASE_LOCK);
}
bool Lock::remove(DataBase database) {
  return Lock::remove(database.returnName(), type::_TYPE_TADABLASE_LOCK);
}