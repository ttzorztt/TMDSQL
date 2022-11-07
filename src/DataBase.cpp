/*
 * @Description  : 实现DataBase类中的一些操作
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:27:53
 * @LastEditTime : 2022-11-06 21:02:38
 */
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
DataBase::DataBase(string name) : _dir("../data/database/" + name) {}

bool DataBase::create() {
  string Path = returnDirPath();
  return _dir::createDir(Path);
  // return true;
}

bool DataBase::insertTable(string tableName) {
  string Path = returnDirPath() + "/" + tableName;
  return _file::createFile(Path);
}

bool DataBase::insertTable(string tableName, const vector<string>& tableItem) {
  string Path = returnDirPath() + "/" + tableName;
  _file::createFile(Path);
  _file::writeFile(Path, tableItem);
  return true;
}

void DataBase::showDataBaseTable() {
  vector<string> ans = _dir::openDirReturnFileName(this->returnDirPath());
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "这个数据库是空的!" << endl;
    return;
  }
  for (string& str : ans) {
    maxtablename = max(maxtablename, (int)str.size() + 2);
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << endl;
  for (string& str : ans) {
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
    std::cout << endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << endl;
}
string DataBase::returnPath(){
  return dirPath;
}
void DataBase::showDataBase() {
  vector<string> ans = _dir::openDirReturnFileName("../data/database/");
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "暂时还没有建立数据库" << endl;
    return;
  }
  for (string& str : ans) {
    maxtablename = max(maxtablename, (int)str.size() + 2);
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << endl;
  for (string& str : ans) {
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
    std::cout << endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << endl;
}
bool DataBase::isExist() {
  if (access(this->returnDirPath().c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}
bool DataBase::isExist(string DataBaseName) {
  if (access(DataBaseName.c_str(), F_OK) != -1) {
    return true;
  } else {
    return false;
  }
}

bool DataBase::deleteTable(string tableName) {
  string Path = "../data/database/" + tableName;
  if (!_file::isExist(Path)) {
    return false;
  } else {
    string tmp = "rm " + Path;
    system(tmp.c_str());
  }
  if (_file::isExist(Path)) {
    return false;
  } else {
    return true;
  }
}

bool DataBase::removeDataBase(string DataBaseName) {
  string Path = "../data/database/" + DataBaseName;
  if (access(Path.c_str(), F_OK) == -1) {
    return false;
  } else {
    _dir::deleteDir(Path);
    if (access(Path.c_str(), F_OK) != -1) {
      return false;
    } else {
      return true;
    }
  }
}

bool DataBase::removeDataBase() {
  if (access(this->returnDirPath().c_str(), F_OK) == -1) {
    return false;
  } else {
    _dir::deleteDir(this->returnDirPath());
    if (access(this->returnDirPath().c_str(), F_OK) != -1) {
      return false;
    } else {
      return true;
    }
  }
}