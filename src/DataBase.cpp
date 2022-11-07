/*
 * @Description  : 实现DataBase类中的一些操作
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:27:53
 * @LastEditTime : 2022-11-07 15:48:33
 */
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
DataBase::DataBase(std::string name) : _dir("../data/database/" + name) {}

bool DataBase::create() {
  std::string Path = returnPath();
  return _dir::createDir(Path);
  // return true;
}

bool DataBase::insertTable(std::string tableName) {
  std::string Path = returnPath() + "/" + tableName;
  return _file::create(Path);
}

bool DataBase::insertTable(std::string tableName, const std::vector<std::string>& tableItem) {
  std::string Path = returnPath() + "/" + tableName;
  _file::create(Path);
  _file::writeFile(Path, tableItem);
  return true;
}

void DataBase::showDataBaseTable() {
  std::vector<std::string> ans = _super::openDirReturnFileName(this->returnPath());
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "这个数据库是空的!" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "|";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "|";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
}
std::string DataBase::returnPath(){
  return dirPath;
}
void DataBase::showDataBase() {
  std::vector<std::string> ans = _super::openDirReturnFileName("../data/database/");
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "暂时还没有建立数据库" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "?";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "?";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
}
bool DataBase::isExist() {
  if (access(this->returnPath().c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}
bool DataBase::isExist(std::string DataBaseName) {
  if (access(DataBaseName.c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}

bool DataBase::deleteTable(std::string tableName) {
  return _file::deleteFile("../data/database/" + tableName);
}

bool DataBase::removeDataBase(std::string DataBaseName) {
  return _dir::deleteDir("../data/database/" + DataBaseName);
}

bool DataBase::removeDataBase() {
  return _dir::deleteDir("../data/database/" + dirName);
}