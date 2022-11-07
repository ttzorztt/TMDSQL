/*
 * @Description  : 目录操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 11:10:24
 * @LastEditTime : 2022-11-07 15:52:47
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
_dir::_dir(_dir& copy): _super(this->dirPath,this->dirName){}
bool _dir::deleteDir() {
  return rmdir(this->dirPath.c_str());
}
_dir::_dir(std::string dirPath) : _super(dirPath,_super::computeDirName(dirPath)){
}

std::string _dir::returnName(){
  return dirName;
}
std::vector<std::string> _dir::openDirReturnFileName() {
  DIR* dirname = opendir(this->dirPath.c_str());
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
bool _dir::createDir(std::string dirName) {
  return mkdir(dirName.c_str(), 777);
}
bool _dir::deleteDir(std::string Path) {
  return rmdir(Path.c_str());
}
std::string _dir::returnPath() {
  return dirPath;
}
bool _dir::isExist(std::string name) {
  return access(name.c_str(), F_OK);
}