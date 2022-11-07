/*
 * @Description  : 封装锁操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:00
 * @LastEditTime : 2022-11-07 22:45:49
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
Lock::Lock(std::string Path) : _super(_super::computeName(Path), Path) {}
Lock::Lock(Lock& copy) : _super(copy.returnName(),copy.returnName()){}

Lock::~Lock() {}
int Lock::returncount() {
  return count;
}
bool Lock::removeLock() {
  if (!_super::isExist(this->path, type::_TYPE_LOCK)) {
    return false;
  }
  std::ifstream filereadbuff(this->path);
  if (!filereadbuff.good()) {
    filereadbuff.close();
    return false;
  } else {
    if (!std::remove(this->path.c_str())) {  // 成功返回0，失败返回-1
      filereadbuff.close();

      return true;
    } else {
      filereadbuff.close();
      return false;
    }
  }
}
bool Lock::addLock() {
  if (!_super::isExist(this->path, type::_TYPE_LOCK)) {
    std::ofstream filewritebuff;
    filewritebuff.open(this->path, std::ios::app);
    if (filewritebuff.is_open()) {
      filewritebuff.close();

      return true;
    }
  }
  return false;
}