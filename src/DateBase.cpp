#include "DateBase.h"
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
}

void DateBase::showDateBase(){
  
}