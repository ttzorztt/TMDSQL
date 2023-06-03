/**
 * @file dir.cpp
 * @brief 目录操作
 * @author TMD
 * @date 2023-11-06
 */
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _STRING_H_
#define _STRING_H_
#include <string.h>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifdef __WIN32__
#include <windows.h>
#endif
// 记录由dir打开的文件
int _dir::count = 0;
_dir::_dir(_dir& copy) : _super(copy.returnName()) {
  this->style = copy.returnType();
  this->truePath = copy.returnTruePath();
}
bool _dir::remove() { return _dir::remove(this->truePath); }
_dir::_dir(std::string truePath)
    : _super(_super::dispartDatabaseNameAndTableName(truePath)[1]) {
  this->style = type::_TYPE_NONE;
  this->truePath = truePath;
}
int _dir::returnCount() { return _dir::count; }
bool _dir::isExist() { return _super::isExist(this->truePath); }
_dir::_dir(std::string dirName, type style) : _super(dirName) {
  this->style = style;
  this->truePath = _super::returnTruePath(dirName, style);
}
std::string _dir::returnTruePath() const { return this->truePath; }
void _dir::openDirReturnFileName(vstring& ret) {
#ifdef __linux__
  DIR* dirname = opendir(this->truePath.c_str());
  struct dirent* dirInfo;
  while ((dirInfo = readdir(dirname)) != 0) {
		if(0 == strcmp(dirInfo->d_name,".") || 0 == strcmp(dirInfo->d_name,"..")){
			continue;
		}
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
#endif
#ifdef __WIN32__
  /* intptr_t handle; */
  /* _finddata_t findData; */
  /* handle = */
  /*     _findfirst(this->truePath.c_str(), &findData);  // 查找目录中的第一个文件 */
  /* if (handle != -1) { */
  /*   do { */
  /*     ret.push_back(findData.name); */
  /*   } while (_findnext(handle, &findData) == 0);  // 查找目录中的下一个文件 */
  /*   _findclose(handle); */
  /* }  // 关闭搜索句柄 */
#endif
}
bool _dir::create() {
  return _dir::create(this->truePath) &&
         _dir::create(_super::returnTruePath(
             this->name, type::_TYPE_CREATE_INDEX_DATABASE)) &&
         _dir::create(_super::returnTruePath(this->name,
                                             type::_TYPE_CREATE_LOCK_DATABASE));
}

type _dir::returnType() { return this->style; }
void _dir::openDirReturnFileName(std::string truePath, vstring& ret) {
  if (!_super::isExist(truePath)) return;
#ifdef __linux__
  DIR* dirname = opendir(truePath.c_str());
  struct dirent* dirInfo;
  while ((dirInfo = readdir(dirname)) != 0) {
		if(0 == strcmp(dirInfo->d_name,".") || 0 == strcmp(dirInfo->d_name,"..")){
			continue;
		}
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
#endif
#ifdef __WIN32__	
  /* HANDLE hFind; */
  /* WIN32_FIND_DATA findData; */
  /* LARGE_INTEGER size; */
  /* hFind = FindFirstFile((truePath + "*.*").c_str(), &findData); */
  /* if (hFind == INVALID_HANDLE_VALUE) { */
  /*   return; */
  /* } */
  /* do { */
  /*   // 忽略"."和".."两个结果 */
  /*   if (strcmp(findData.cFileName, ".") == 0 || */
  /*       strcmp(findData.cFileName, "..") == 0) */
  /*     continue; */
		/* ret.push_back(findData.cFileName); */
  /* } while (FindNextFile(hFind, &findData)); */
  /* return; */
#endif
}
bool _dir::create(std::string truePath) { return _super::createDir(truePath); }
bool _dir::remove(std::string truePath) { return rmdir(truePath.c_str()) == 0; }
