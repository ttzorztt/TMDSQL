#include "DateBase.h"


DateBase::DateBase(string path,string datebasename)
          :_file(path),datebasename(datebasename){
  status = 1;
  if(_file::isExists(path)) status = 0;
}

void DateBase::Create(){
  if(!status) return ;
  
}