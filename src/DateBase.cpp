#ifndef _DATEBASE_H_
#define _DATEBASE_H_
#include "DateBase.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
DateBase::DateBase(string name)
          :_file(name){
  status = 1;
  if(_file::isExist(name)) status = 0;
}

bool DateBase::create(){
  string Path = "../data/database/" + name;
  return _file::createDir(Path);
  return true;
}

bool DateBase::insertTable(string tableName){
  string Path = "../data/database/"+ name + "/" + tableName;
  return _file::createFile(Path);
}

bool DateBase::insertTable(string tableName,const vector<string>& tableItem){
  string Path = "../data/database/"+ name + "/" + tableName;
  _file::createFile(Path);
  _file::writeFile(Path,tableItem);
  return true;
}

void DateBase::showDateBase(){
  vector<string>ans = openDirReturnFileName();
  int maxtablename = 0;
  for(string& str:ans){
    maxtablename = max(maxtablename,(int)str.size() + 2);
  }
  for(int a = 0; a < maxtablename; ++a){
    cout << "*";
  }
  cout << endl;
  for(string& str:ans){
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    for(int )
  }
}