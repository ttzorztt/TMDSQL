/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:19
 * @LastEditTime : 2023-01-14 10:54:14
 */

#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#include <iostream>
bool _super::createDir(std::string path) {
#ifdef __WIN32__
  return mkdir(path.c_str());
#endif
#ifdef __linux__
  return mkdir(path.c_str(), 777);
#endif
}
bool _super::create() {
  return true;
}
void _super::stringToVector(const std::string& _str, revstring vec) {
  vec.clear();
  int size = _str.size();
  int left = 0;
  while (left < size) { //去除前导空格
    if (_str[left] != ' ') {
      break;
    }
    ++left;
  }
  if (left == size) {
    return;
  }
  int right = left + 1;
  while (right <= size) {
    if(_str[right] == ' ' && _str[right - 1] == ' '){
      ++left;
      ++right;
      continue;
    }
    if (_str[right] != ',' && _str[right] != ' ') {
      ++right;
      continue;
    } else {
      vec.push_back(_str.substr(left, right - left));
      left = right + 1;
      ++right;
    }
  }
  if (_str[size - 1] != ' ') {
    vec.push_back(_str.substr(left));
  }
}
bool _super::remove() {
  return true;
}
type _super::returnType() {
  return type::_TYPE_TABLE;
}
std::string _super::returnName() {
  return name;
}
int _super::returnCount() {
  return -1;
}
bool _super::isExist() {
  return false;
}
_super::~_super() {}
_super::_super(_super& copy) {
  this->name = copy.name;
}
_super::_super(std::string name) {
  this->name = name;
}
vstring _super::dispartDatabaseNameAndTableName(std::string TableName) {
  int size = TableName.size();
  if (size == 0) {
    return {};
  }
  while (size >= 0) {
    if (TableName[size] == '/') {
      break;
    }
    --size;
  }
  return {TableName.substr(0, size), TableName.substr(size + 1)};
}

bool _super::isExist(std::string name, type style) {
  return access(_super::returnTruePath(name, style).c_str(), F_OK) != -1;
}
bool _super::isExist(std::string truePath) {
  return access(truePath.c_str(), F_OK) != -1;
}
    
std::string _super::returnTruePath(std::string Name, type style) {
  vstring vectorbuff;
  switch (style) {
    case type::_TYPE_DATABASE:
    case type::_TYPE_TABLE:
      return _databaseAndTablePath + Name;
    case type::_TYPE_INDEX_TABLE:
    case type::_TYPE_CREATE_INDEX_DATABASE:
      return _indexPath + Name;
    case type::_TYPE_PCB:
      vectorbuff = _super::dispartDatabaseNameAndTableName(Name);
      return _PCBPath + vectorbuff[0] + "/" + vectorbuff[1];
    case type::_TYPE_CREATE_PCB_DATABASE:
      return _PCBPath + Name;
    case type::_TYPE_LOG: 
      return _PathForLog + Name;
    default:
      break;
  }
  return "";
}
int _super::stringToInt(std::string& str) {
  for (char& ch : str) {
    if (ch > '9' || ch < '0') {
      return -1;
    }
  }
  return atoi(str.c_str());
}