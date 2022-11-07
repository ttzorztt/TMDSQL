/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-11-07 22:37:05
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
_file::_file(std::string Path)
    : _super(_super::computeName(Path), Path + ".csv") {
  lockPath = "../data/lock/." + this->name + ".csv";
}
_file::~_file() {
  if(writeFileBuff.is_open()){
  writeFileBuff.close();
  }
  if(readFileBuff.is_open()){
    readFileBuff.close();
  }
}

bool _file::write(const std::string& str) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  writeFileBuff << str << std::endl;
  return true;
}
bool _file::write(const std::vector<std::string>& array) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  for (auto& x : array) {
    writeFileBuff << x << " ";
  }
  writeFileBuff << std::endl;
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



bool _file::create(std::string path, type style) {
  if (_super::isExist(path, style)) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(path, std::ios::out);
  if (filewritebuff.good()) {
    filewritebuff.close();
    ++_file::count;

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
    ++_file::count;

    return true;
  }
  writeFileBuff.close();
  return false;
}

bool _file::writeBuffOpen(bool need) {
  if (need && !_super::isExist(this->path, style)) {
    return false;
  }
  if (!writeFileBuff.is_open()) {
    writeFileBuff.open(path, std::ios::app);
  }
  return true;
}

bool _file::readBuffOpen(bool need) {
  if (need && !isExist(this->path, style)) {
    return false;
  }
  if (!readFileBuff.is_open()) {
    readFileBuff.open(path);
  }
  return true;
}

bool _file::remove() {
  if (!_super::isExist(this->path, type::_TYPE_FILE)) {
    return false;
  }
  std::remove(this->path.c_str());
  if (!_super::isExist(this->path, type::_TYPE_FILE)) {
    --_file::count;
    return true;
  }
  return false;
}

_file::_file(_file& _copy) : _super(_copy.returnName(), _copy.returnPath()) {
  this->lockPath = _copy.lockPath;
  this->name = _copy.name;
  this->path = _copy.path;
  ++_file::count;
}

const std::ofstream& _file::returnWriteFileBuff() {
  return writeFileBuff;
}
const std::ifstream& _file::returnReadFileBuff() {
  return readFileBuff;
}