/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2022-11-09 21:52:39
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif 
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
// 记录由dir打开的文件
int  _dir::count = 0;
_dir::_dir(_dir& copy) : _super(copy.returnName()) {}
bool _dir::remove() {
  return rmdir(_super::returnTruePath(this->name, type::_TYPE_DADABASE).c_str());
}
int _dir::returnCount(){
  return _dir::count;
}
bool _dir::isExist(){
  return _super::isExist(_super::returnTruePath(this->name, type::_TYPE_DADABASE));
}
_dir::_dir(std::string dirName)
    : _super(dirName) {}
std::vector<std::string> _dir::openDirReturnFileName() {
  DIR* dirname = opendir(_super::returnTruePath(this->name, type::_TYPE_DADABASE).c_str());
  struct dirent* dirInfo;
  std::vector<std::string> ret;
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
bool _dir::create(){
  return _dir::create(_super::returnTruePath(this->name, type::_TYPE_DADABASE));
}
std::vector<std::string> _dir::openDirReturnFileName(std::string Path) {
  if (!_super::isExist(Path))
    return {};
  DIR* dirname = opendir(Path.c_str());
  struct dirent* dirInfo;
  std::vector<std::string> ret;
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
bool _dir::create(std::string truePath) {
  return mkdir(truePath.c_str(), 777);
}
bool _dir::remove(std::string truePath) {
  return rmdir(truePath.c_str());
}