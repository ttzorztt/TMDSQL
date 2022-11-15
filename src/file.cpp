/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-11-15 18:11:55
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
_file::_file(std::string Name,type style) : _super(Name) {
  this->style = style;
  this->truePath = _super::returnTruePath(Name,style);
  std::cout << this->truePath << std::endl;
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

bool _file::write(const std::string& str) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  writeFileBuff << std::endl << str;
  return true;
}

bool _file::write(const std::vector<std::string>& array) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  int size = array.size();
  if(size == 0) return false;
  writeFileBuff << array[0];
  for(int index = 1; index < size; ++index){
    writeFileBuff << " " << array[index];
  }
  writeFileBuff << std::endl;
  return true;
}
bool _file::remove(std::string Name, type style) {
  return _file::remove(_super::returnTruePath(Name, style));
}
bool  _file::remove(std::string truePath){
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
bool _file::write(std::string Name, type style,const std::vector<std::string>& array) {
  _file tmd(Name,style);
  return tmd.write(array);
}
bool _file::write(std::string Name, type style ,const std::string& str){
  _file tmd(Name,style);
  return tmd.write(str);
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
    if (_str[right] != ',') {
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

type _file::returnType(){
  return this->style;
}
bool _file::create(std::string name, type style) {
  std::string truePath = _super::returnTruePath(name, style);
  if (_super::isExist(truePath) || style == type::_TYPE_DADABASE) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(truePath, std::ios::out);
  if (filewritebuff.good()) {
    filewritebuff.close();
    ++_file::count;
    return true;
  }
  filewritebuff.close();
  return false;
}
bool _file::create() {
  return _file::create(this->name, this->style);
}

bool _file::writeBuffOpen(bool need) {
  if (need && !_super::isExist(this->truePath)) {
    return false;
  }
  if (!writeFileBuff.is_open()) {
    writeFileBuff.open(this->truePath, std::ios::app);
  }
  return true;
}
std::string _file::returnTruePath(){
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