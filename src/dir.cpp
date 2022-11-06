/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2022-11-06 19:46:12
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
_dir::_dir(_dir& copy){
  this->dirPath = copy.dirPath;
}
bool _dir::deleteDir() {
  return rmdir(this->dirPath.c_str());
}
_dir::_dir(string dirPath) : dirPath(dirPath) {}

vector<string> _dir::openDirReturnFileName(string dirPath) {
  DIR* dirname = opendir(dirPath.c_str());
  struct dirent* dirInfo;
  vector<string> name;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count > 0) {
      --count;
      continue;
    }
    name.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  return name;
}
vector<string> _dir::openDirReturnFileName() {
  DIR* dirname = opendir(this->dirPath.c_str());
  struct dirent* dirInfo;
  vector<string> ret;
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
bool _dir::createDir(string dirName) {
  return mkdir(dirName.c_str(), 777);
}
bool _dir::deleteDir(string Path) {
  return rmdir(Path.c_str());
}
string _dir::returnDirPath() {
  return dirPath;
}
bool _dir::isExist(string name) {
  return access(name.c_str(), F_OK);
}