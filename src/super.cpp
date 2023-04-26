/**
 * @file super.cpp
 * @brief 维护一些静态函数和变量
 * @author TMD
 * @date 2022-11-07
 */
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _SYS_STAT_
#define _SYS_STAT_
#include <sys/stat.h>
#endif
#ifndef _SYS_TYPES_
#define _SYS_TYPES_
#include <sys/types.h>
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
bool _super::createDir(std::string path) {
#ifdef __WIN32__
  mkdir(path.c_str());
#endif
#ifdef __linux__
  mode_t mode = umask(0);
  mkdir(path.c_str(), 0777);
  umask(mode);
#endif
  return (_super::isExist(path)) ? true : false;
}
bool _super::create() { return true; }
void _super::stringToVector(const std::string& _str, revstring vec) {
  vec.clear();
  int size = _str.size();
  int left = 0;
  while (left < size) {  //去除前导空格
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
    if (_str[right] == ' ' && _str[right - 1] == ' ') {
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
bool _super::remove() { return true; }
type _super::returnType() { return type::_TYPE_TABLE; }
std::string _super::returnName() { return name; }
int _super::returnCount() { return -1; }
bool _super::isExist() { return false; }
_super::~_super() {}
_super::_super(_super& copy) { this->name = copy.name; }
_super::_super(std::string name) { this->name = name; }
vstring _super::dispartDatabaseNameAndTableName(std::string TableName) {
  vstring ret(3);
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
  ret[1] = TableName.substr(size + 1);
  int mid = size;
  --size;
  while (size >= 0) {
    if (TableName[size] == '/') {
      break;
    }
    --size;
  }
  ret[0] = TableName.substr(size + 1, mid - size - 1);
  ret[2] = ret[0] + "/" + ret[1];
  return ret;
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
    case type::_TYPE_VIEW:
      return _ViewPath + Name;
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
