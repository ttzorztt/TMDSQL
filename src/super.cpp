/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:19
 * @LastEditTime : 2022-12-18 10:33:49
 */

#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
std::vector<std::string> _super::openDirReturnFileName(std::string truePath) {
  bool isTableOrDatabase = true;
  DIR* dirname = opendir(truePath.c_str());
  struct dirent* dirInfo;
  std::vector<std::string> name;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count > 0) {
      --count;
      continue;
    }
    std::string tmpname = dirInfo->d_name;
    if (tmpname.substr(tmpname.size() - 4) == ".csv") {
      name.push_back(tmpname.substr(0, tmpname.size() - 4));
    } else {
      name.push_back(tmpname);
    }
  }

  return name;
}

bool _super::create() {
  return true;
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
std::vector<std::string> _super::dispartDatabaseNameAndTableName(
    std::string TableName) {
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
  std::vector<std::string> part;
  switch (style) {
    case type::_TYPE_DATABASE:
      return _databasePath + Name;
      break;
    case type::_TYPE_TABLE_LOCK:
      part = _super::dispartDatabaseNameAndTableName(Name);
      return _tableLockPath + part[0] + "/." + part[1];
      break;
    case type::_TYPE_DATABASE_LOCK:
      return _databaseLockPath + "/." + Name;
      break;
    case type::_TYPE_TABLE:
      part = _super::dispartDatabaseNameAndTableName(Name);
      return _tablePath +part[0] + "/" + part[1];
    case type::_TYPE_INDEX_TABLE:
      return _indexPath + Name;
      break;
    case type::_TYPE_CREATE_INDEX_DATABASE:
      return _indexPath + Name;
      break;
    case type::_TYPE_CREATE_LOCK_DATABASE:
      return _databaseLockPath + Name;
      break;
    case type::_TYPE_PCB:
      part = _super::dispartDatabaseNameAndTableName(Name);
      return _PCBPath + part[0] + "/" + part[1];
      break;
      case type::_TYPE_CREATE_PCB_DATABASE:
      return _PCBPath + Name;
    default:
      break;
  }
  return "";
}