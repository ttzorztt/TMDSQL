/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2022-11-09 15:25:21
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
_dir::_dir(_dir& copy) : _super(copy.returnPath(), copy.returnName()) {}
bool _dir::remove() {
  std::string truePath = _super::returnTruePath(this->path, type::_TYPE_DIR);
  return rmdir(truePath.c_str());
}
_dir::_dir(std::string dirPath)
    : _super(dirPath, _super::computeName(dirPath)) {}
std::vector<std::string> _dir::openDirReturnFileName() {
  DIR* dirname = opendir(this->path.c_str());
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
std::vector<std::string> _dir::openDirReturnFileName(Table table) {
  DIR* dirname = opendir(table.returnPath().c_str());
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
bool _dir::create(std::string dirName) {
  return mkdir(dirName.c_str(), 777);
}
bool _dir::remove(std::string Path) {
  return rmdir(Path.c_str());
}