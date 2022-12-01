/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-12-02 07:28:03
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
_file::_file(std::string Name, type style) : _super(Name) {
  this->style = style;
  this->truePath = _super::returnTruePath(Name, style);
  ++_file::count;
}
_file::_file(_file& _copy) : _super(_copy.returnName()) {
  this->style = _copy.returnType();
  this->truePath = _copy.truePath;
  ++_file::count;
}
_file::~_file() {
  if (writeFileBuff.is_open()) {
    writeFileBuff.close();
  }
  if (readFileBuff.is_open()) {
    readFileBuff.close();
  }
  --_file::count;
}
void _file::setReadSeek(POINTER fileIndex) {
  readFileBuff.clear();
  this->readFileBuff.seekg(fileIndex, std::ios::beg);
}
void _file::setWriteSeek(POINTER fileIndex) {
  writeFileBuff.seekp(fileIndex, std::ios::beg);
}
POINTER _file::returnReadTell() {
  return readFileBuff.tellg();
}
POINTER _file::returnWriteTell() {
  return writeFileBuff.tellp();
}
bool _file::write(const std::string& str, type_mode mode) {
  if (!writeBuffOpen(true, mode)) {
    return false;
  }
  switch (mode) {
    case type_mode::MODE_APP:
      writeFileBuff << std::endl << str;
    case type_mode::MODE_TRUNC:
      writeFileBuff << str;
    default:
      break;
  }
  return true;
}

bool _file::write(const std::vector<std::string>& array, type_mode mode) {
  if (!writeBuffOpen(true, mode)) {
    return false;
  }
  int size = array.size();
  if (size == 0)
    return false;
  writeFileBuff << array[0];
  for (int index = 1; index < size; ++index) {
    writeFileBuff << "," << array[index];
  }
  writeFileBuff << std::endl;
  return true;
}
bool _file::remove(std::string Name, type style) {
  return _file::remove(_super::returnTruePath(Name, style));
}
bool _file::remove(std::string truePath) {
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
bool _file::write(std::string Name,
                  type style,
                  const std::vector<std::string>& array,
                  type_mode mode) {
  _file tmd(Name, style);
  return tmd.write(array, mode);
}
bool _file::write(std::string Name,
                  type style,
                  const std::string& str,
                  type_mode mode) {
  _file tmd(Name, style);
  return tmd.write(str, mode);
}
bool _file::readline(std::vector<std::string>& ret) {
  ret.clear();
  if (!readBuffOpen(true)) {
    return false;
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
    if (_str[right] != ',') {
      ++right;
      continue;
    } else {
      ret.push_back(_str.substr(left, right - left));
      left = right + 1;
      ++right;
    }
  }
  ret.push_back(_str.substr(left));
  return true;
}

type _file::returnType() {
  return this->style;
}
bool _file::create(std::string name, type style) {
  std::string truePath = _super::returnTruePath(name, style);
  if (_super::isExist(truePath) || style == type::_TYPE_DATABASE) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(truePath, std::ios::out);
  if (filewritebuff.good()) {
    filewritebuff.close();
    ++_file::count;
    if (style == type::_TYPE_PCB && !_file(name, type::_TYPE_PCB).isExist()) {
      _file(name, type::_TYPE_PCB).inputPCBInformation();
    }
    return true;
  }
  filewritebuff.close();
  return false;
}

void _file::inputPCBInformation() {
  std::string input = this->name + ",0,0\n";
  this->write(input, type_mode::MODE_TRUNC);
}
bool _file::create() {
  return _file::create(this->name, this->style);
}

bool _file::writeBuffOpen(bool need, MODE mode) {
  if (need && !_super::isExist(this->truePath)) {
    return false;
  }
  if (!writeFileBuff.is_open()) {
    switch (mode) {
      case type_mode::MODE_APP:
        writeFileBuff.open(this->truePath, std::ios::app);
        break;
      case type_mode::MODE_TRUNC:
        writeFileBuff.open(this->truePath, std::ios::out|std::ios::trunc);
        break;
      default:
        break;
    }
  }
  return true;
}
std::string _file::returnTruePath() {
  return truePath;
}
bool _file::readBuffOpen(bool need) {
  if (need && !_super::isExist(this->truePath)) {
    return false;
  }
  if (!readFileBuff.is_open()) {
    readFileBuff.open(this->truePath);
  }
  return true;
}

bool _file::remove() {
  return _file::remove(this->name, style);
}

std::ofstream& _file::returnWriteFileBuff() {
  return writeFileBuff;
}

std::ifstream& _file::returnReadFileBuff() {
  return readFileBuff;
}
bool _file::isExist() {
  return _super::isExist(_super::returnTruePath(name, style));
}
int _file::returnCount() {
  return _file::count;
}