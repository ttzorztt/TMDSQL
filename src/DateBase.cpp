#include "DateBase.h"


DateBase::DateBase(string path,string datebasename)
          :_file(path),datebasename(datebasename){
  status = 1;
  if(_file::isExist(path)) status = 0;
}

void DateBase::Create(){
  if(!status) return ;
  
}