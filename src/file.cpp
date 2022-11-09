/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-11-09 16:53:04
 */
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
//当前打开的文件数总数
int _file::count = 0;
_file::_file(std::string Path)
    : _super(_super::computeName(Path), Path) {
}
_file::_file(_file& _copy) : _super(_copy.returnName(), _copy.returnPath()) {
  this->name = _copy.name;
  this->path = _copy.path;
  ++_file::count;
}
_file::~_file() {
  if (writeFileBuff.is_open()) {
    writeFileBuff.close();
  }
  if (readFileBuff.is_open()) {
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
bool _file::remove(std::string path,type style){
  std::string truePath = _super::returnTruePath(path,style);
    if (!_super::isExist(truePath)) {
    return false;
  }
  std::remove(truePath.c_str());
  if (!_super::isExist(truePath)) {
    --_file::count;
    return true;
  }
  return false;
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
  if (_super::isExist(path, style) || style == type::_TYPE_DIR ||
      style == type::_TYPE_TADABLASE_LOCK) {
    return false;
  }
  std::ofstream filewritebuff;
  std::string truePath = _super::returnTruePath(path, style);
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
 return _file::create(this->path,this->style);
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
  return _file::remove(this->path,style);
}

const std::ofstream& _file::returnWriteFileBuff() {
  return writeFileBuff;
}

const std::ifstream& _file::returnReadFileBuff() {
  return readFileBuff;
}
