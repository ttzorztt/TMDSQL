/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-11-07 15:55:00
 */
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif

int _file::count = 0;
int _file::fileCount = 0;
int _file::indexCount = 0;
int _file::lockCount = 0;
_file::_file(std::string Path): _super(_super::computeFileName(Path),Path + ".csv"){
  lockPath = "../data/lock/." + this->name + ".csv";
}
_file::~_file() {
  writeFileBuff.close();
}
bool _file::isExist() {
  return access(this->path.c_str(), F_OK) != -1;
}
bool _file::isExist(std::string _name) {
  return access(_name.c_str(), F_OK) != -1;
}
bool _file::write(const std::string& str) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  while (_file::addLock())
    ;
  writeFileBuff << str << std::endl;
  _file::removeLock();
  return true;
}
bool _file::write(const std::vector<std::string>& array) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  addLock();
  for (auto& x : array) {
    writeFileBuff << x << " ";
  }
  writeFileBuff << std::endl;
  removeLock();
  return true;
}
bool _file::writeFile(std::string Path, const std::vector<std::string>& array) {
  _file tmd(Path);
  return tmd.write(array);
}
bool _file::readline(std::vector<std::string>& ret) {
  if (!readBuffOpen(true)) {
    return {};
  }
  std::string _str;
  getline(readFileBuff, _str);
  if (this->returnReadFileBuff().eof()) {
    return false;
  }
  int left = 0;
  int right = 1;
  int size = _str.size();
  while (right <= size) {
    if (_str[right] == ' ') {
      ++right;
      continue;
    } else {
      ret.push_back(_str.substr(left, right - left));
      left = right;
      ++right;
    }
  }
  return true;
}

bool _file::addLock() {
  if (!_file::isExist(lockPath)) {
    std::ofstream filewritebuff;
    filewritebuff.open(lockPath, std::ios::app);
    if (filewritebuff.is_open()) {
      filewritebuff.close();
      return true;
    }
  }
  return false;
}
bool _file::removeLock() {
  if (!isExist()) {
    return false;
  }
  std::ifstream filereadbuff(lockPath);
  if (!filereadbuff.good()) {
    filereadbuff.close();
    return false;
  } else {
    if (!std::remove(lockPath.c_str())) {  // 成功返回0，失败返回-1
      filereadbuff.close();
      return true;
    } else {
      filereadbuff.close();
      return false;
    }
  }
}
bool _file::create(std::string path) {
  if (_file::isExist(path)) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(path, std::ios::out);
  if (filewritebuff.good()) {
    filewritebuff.close();
    return true;
  }
  filewritebuff.close();
  return false;
}

bool _file::create() {
  if (!writeBuffOpen(false)) {
    return false;
  }
  if (writeFileBuff.good()) {
    writeFileBuff.close();
    return true;
  }
  writeFileBuff.close();
  return false;
}

bool _file::writeBuffOpen(bool need) {
  if (need && !isExist()) {
    return false;
  }
  if (!writeFileBuff.is_open()) {
    writeFileBuff.open(path, std::ios::app);
  }
  return true;
}

bool _file::readBuffOpen(bool need) {
  if (need && !isExist()) {
    return false;
  }
  if (!readFileBuff.is_open()) {
    readFileBuff.open(path);
  }
  return true;
}

bool _file::remove() {
  return std::remove(this->path.c_str());
}

const std::string& _file::returnPath() {
  return this->path;
}
_file::_file(_file& _copy) : _super(_copy.returnName(),_copy.returnPath()) {
  this->lockPath = _copy.lockPath;
  this->name = _copy.name;
  this->path = _copy.path;
}
const std::string& _file::returnName() {
  return this->name;
}
const std::ofstream& _file::returnWriteFileBuff() {
  return writeFileBuff;
}
const std::ifstream& _file::returnReadFileBuff() {
  return readFileBuff;
}