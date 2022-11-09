/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-09 21:07:28
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif

 
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
  std::string truePath = _super::returnTruePath(Name,style); 
  switch (_super::isExist(truePath)) {
    case true: {
      return !std::remove(truePath.c_str());
    }
    case false:{
      return false;
      break;
    }
  }
}

bool Lock::add(std::string Name, type style) {
  if(_super::isExist(_super::returnTruePath(Name, style), style)) {
      return false;
  }
      return _file::create(Name, style);
}

bool Lock::add(Table table) {
  return Lock::add(_super::returnTruePath(table.returnName(), type::_TYPE_TABLE_LOCK),type::_TYPE_TABLE_LOCK);
}

bool Lock::remove(Table table) {
  return Lock::remove(_super::returnTruePath(table.returnName(), type::_TYPE_TABLE_LOCK),type::_TYPE_TABLE_LOCK);
}

bool Lock::add(DataBase database){
  return Lock::add(_super::returnTruePath(database.returnName(), type::_TYPE_TADABLASE_LOCK),type::_TYPE_TADABLASE_LOCK);
}
bool Lock::remove(DataBase database){
  return Lock::remove(_super::returnTruePath(database.returnName(), type::_TYPE_TADABLASE_LOCK),type::_TYPE_TADABLASE_LOCK);
}