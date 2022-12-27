/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2022-12-27 09:35:37
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#include <iostream>
// 记录由dir打开的文件
int _dir::count = 0;
_dir::_dir(_dir& copy) : _super(copy.returnName()) {
  this->style = copy.returnType();
  this->truePath = copy.returnTruePath();
}
void _dir::forceremove() {
  _dir::forceremove(this->name);
}
bool _dir::remove() {
  return _dir::remove(_super::returnTruePath(this->name,style));
}
int _dir::returnCount() {
  return _dir::count;
}
bool _dir::isExist() {
  return _super::isExist(
      _super::returnTruePath(this->name, type::_TYPE_DATABASE));
}
_dir::_dir(std::string dirName,type style) : _super(dirName) {
  this->style = style;
  this->truePath = _super::returnTruePath(dirName,style);
  }
std::string _dir::returnTruePath(){
  return this->truePath;
}
vstring _dir::openDirReturnFileName() {
  DIR* dirname =
      opendir(_super::returnTruePath(this->name, type::_TYPE_DATABASE).c_str());
  struct dirent* dirInfo;
  vstring ret;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count != 0) {
      --count;
      continue;
    }
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  return ret;
}
bool _dir::create() {
  return _dir::create(
             _super::returnTruePath(this->name, type::_TYPE_DATABASE)) &&
         _dir::create(_super::returnTruePath(
             this->name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::create(_super::returnTruePath(this->name,
                                             type::_TYPE_CREATE_LOCK_DATABASE));
}

type _dir::returnType(){
  return this->style;
}
vstring _dir::openDirReturnFileName(std::string truePath) {
  if (!_super::isExist(truePath))
    return {};
  DIR* dirname = opendir(truePath.c_str());
  struct dirent* dirInfo;
  vstring vectorbuff;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count != 0) {
      --count;
      continue;
    }
    vectorbuff.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  return vectorbuff;
}
bool _dir::create(std::string truePath) {
  return mkdir(truePath.c_str(), 777) == 0;
}
bool _dir::remove(std::string truePath) {
  return rmdir(truePath.c_str()) == 0;
}

void _dir::forceremove(std::string Name) {
  std::string truePath = _super::returnTruePath(Name, type::_TYPE_DATABASE);
  vstring vectorbuff;
  vectorbuff = _dir::openDirReturnFileName(truePath);
  for (std::string& str : vectorbuff) {
    _file::remove(truePath + "/" + str);
    std::cout << truePath + "/" + str << std::endl;
  }
  rmdir(truePath.c_str());
}