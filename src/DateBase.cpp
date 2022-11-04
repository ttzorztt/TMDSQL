#include "DateBase.h"


DateBase::DateBase(string path)
          :_file(path){
  status = 1;
  if(_file::isExist(path)) status = 0;
}

bool DateBase::create(){
  string tmp = "mkdir "+ filePath;
  system(tmp.c_str());
  return true;
}