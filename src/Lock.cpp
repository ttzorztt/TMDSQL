/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-08 16:14:13
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
type Lock::returnType(){
  return style;
}

Lock::Lock(Lock& copy) : _super(copy.returnName(), copy.returnName()) {
  this->style = copy.returnType();
}

Lock::~Lock() {}
int Lock::returncount() {
  return count;
}
  int  Lock::returnFileCount(){
    return fileCount;
  }
  int  Lock::returnDatabaseCount(){
    return databaseCount;
  }
bool Lock::remove(std::string Path) {
  std::string LockPath = Path + "csv";
  switch (_super::isExist(LockPath, type::_TYPE_LOCK)) {
    case false:
      return false;
      break;
    case true:
      return !std::remove(LockPath.c_str());
      break;
    default:
      return false;
      break;
  }
}

bool Lock::add(std::string Path,type style) {
  std::string LockPath = Path + "csv";
  switch (_super::isExist(LockPath, type::_TYPE_LOCK)) {
    case true:
      return false;
      break;
    case false:
      return _file::create(LockPath, type::_TYPE_LOCK);
      break;
    default:
      return false;
      break;
  }
}

bool Lock::add(Table table) {
  return Lock::add(table.returnPath() + ".csv");
}

bool Lock::remove(Table table) {
  return Lock::remove(table.returnPath() + ".csv");
}

bool Lock::remove() {
  return Lock::remove(this->path + ".csv");
}

bool Lock::add() {
  return Lock::add(this->path + ".csv");
}
