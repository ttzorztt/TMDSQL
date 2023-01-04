/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2023-01-04 11:35:51
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
  return _dir::remove(_super::returnTruePath(this->name, style));
}
int _dir::returnCount() {
  return _dir::count;
}
bool _dir::isExist() {
  return _super::isExist(
      _super::returnTruePath(this->name, type::_TYPE_DATABASE));
}
_dir::_dir(std::string dirName, type style) : _super(dirName) {
  this->style = style;
  this->truePath = _super::returnTruePath(dirName, style);
}
std::string _dir::returnTruePath() {
  return this->truePath;
}
void _dir::openDirReturnFileName(vstring& ret) {
  #ifdef __linux__
  DIR* dirname =
      opendir(_super::returnTruePath(this->name, type::_TYPE_DATABASE).c_str());
  struct dirent* dirInfo;
  
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count != 0) {
      --count;
      continue;
    }
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  #endif
  #ifdef __WIN32__
  intptr_t handle;
  _finddata_t findData;
  handle = _findfirst(this->name.c_str(), &findData);  // 查找目录中的第一个文件
  if (handle == -1) {
    return ;
  }
  do {
      ret.push_back(findData.name);
  } while (_findnext(handle, &findData) == 0);  // 查找目录中的下一个文件
  _findclose(handle);  // 关闭搜索句柄
  return;
  #endif
}
bool _dir::create() {
  return _dir::create(
             _super::returnTruePath(this->name, type::_TYPE_DATABASE)) &&
         _dir::create(_super::returnTruePath(
             this->name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::create(_super::returnTruePath(this->name,
                                             type::_TYPE_CREATE_LOCK_DATABASE));
}

type _dir::returnType() {
  return this->style;
}
void _dir::openDirReturnFileName(std::string truePath,vstring& ret) {
  if (!_super::isExist(truePath))
    return ;
  #ifdef __linux__
  DIR* dirname = opendir(truePath.c_str());
  struct dirent* dirInfo;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count != 0) {
      --count;
      continue;
    }
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  #endif
  #ifdef __WIN32__
  intptr_t handle;
  _finddata_t findData;
  handle = _findfirst(truePath.c_str(), &findData);  // 查找目录中的第一个文件
  if (handle == -1) {
    return ;
  }
  do {
      ret.push_back(findData.name);
  } while (_findnext(handle, &findData) == 0);  // 查找目录中的下一个文件
  _findclose(handle);  // 关闭搜索句柄
  return;
  #endif
}
bool _dir::create(std::string truePath) {
  return createDir(truePath.c_str()) == 0;
}
bool _dir::remove(std::string truePath) {
  return rmdir(truePath.c_str()) == 0;
}

void _dir::forceremove(std::string Name) {
  std::string truePath = _super::returnTruePath(Name, type::_TYPE_DATABASE);
  vstring vectorbuff;
  _dir::openDirReturnFileName(truePath,vectorbuff);
  for (std::string& str : vectorbuff) {
    _file::remove(truePath + "/" + str);
    std::cout << truePath + "/" + str << std::endl;
  }
  rmdir(truePath.c_str());
}