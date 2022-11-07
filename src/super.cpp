/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:19
 * @LastEditTime : 2022-11-07 11:45:22
 */

#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <dirent.h>
#endif
#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_
#include <sys/types.h>
#endif
#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_
#include <sys/stat.h>
#endif
#ifndef _UNISTD_H_
#define _UNISTD_H_
#include <unistd.h>
#endif
bool _super::isExist() {
  switch (style) {
    case type::_TYPE_DIR:
      return access(this->path.c_str(), F_OK) != -1;
      break;
    case type::_TYPE_FILE:
    case type::_TYPE_INDEX:
    case type::_TYPE_LOCK:
      return access((this->path + ".csv").c_str(), F_OK) != -1;
      break;
    default:
      return false;
      break;
  }
}

_super::_super(std::string Path, type style) {
  int size = Path.size() - 1;
  while (size >= 0) {
    if (Path[size] == '/') {
      break;
    }
    --size;
  }
  this->name = Path.substr(size + 1, INT64_MAX);
  this->path = Path;
  this->style = style;
}
_super::_super(std::string& Path, type style) {
  int size = Path.size() - 1;
  while (size >= 0) {
    if (Path[size] == '/') {
      break;
    }
    --size;
  }
  this->name = Path.substr(size + 1, INT64_MAX);
  this->path = Path;
  this->style = style;
}
_super::_super(_super& copy) {
  this->name = copy.returnName();
  this->path = copy.returnPath();
  this->style = copy.returnType();
}
_super::~_super() {}
std::string _super::returnName() {
  return this->name;
}
bool _super::create(){
    
}
std::string _super::returnPath() {
  return this->path;
}

type _super::returnType() {
  return style;
}