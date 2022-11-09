/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-09 16:22:10
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
bool Lock::remove(std::string Path, type style) {
  std::string truePath = _super::returnTruePath(Path,style); 
  if(_super::isExist(truePath,style)){

  } 


  
   
  switch (style) {
    case type::_TYPE_FILE: {
      std::string LockPath = Path + "csv";
      switch (_super::isExist(LockPath, style)) {
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
      break;
    }
  }
}

bool Lock::add(std::string Path, type style) {
  switch (_super::isExist(Path, style)) {
    case true:
      return false;
      break;
    case false:
      return _file::create(Path, style);
      break;
    default:
      return false;
      break;
  }
}

bool Lock::add(Table table) {
  return Lock::add(table.returnPath(),type::_TYPE_FILE_LOCK);
}

bool Lock::remove(Table table) {
  return Lock::remove(table.returnPath(),type::_TYPE_FILE_LOCK);
}

bool Lock::add(DataBase database){
  return Lock::add(database.returnPath(),type::_TYPE_TADABLASE_LOCK);
}
bool Lock::remove(DataBase database){
  return Lock::remove(database.returnPath(),type::_TYPE_TADABLASE_LOCK);
}