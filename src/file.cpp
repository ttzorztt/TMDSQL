#include "file.h"
_file::_file(string& Path){
  filePath = Path;
  lockPath = "../data/lock/." + Path;
}
_file::~_file(){
  writeFileBuff.close();
}
bool _file::isExist(){
  ifstream tmp1(this->filePath);
  bool ret = tmp1.good();
  tmp1.close();
  return ret;
}
bool _file::isExist(string _filePath){
  ifstream tmp(_filePath);
  bool ret = tmp.good();
  tmp.close();
  return ret;
}
bool _file::writeFile(const string& str){
  if(!writeBuffOpen(true)){
    return false;
  }
  while(addLock());
  writeFileBuff << str << endl;
  removeLock();
  return true;
}
bool  _file::writeFile(const vector<string>& array){
 if(!writeBuffOpen(true)){
    return false;
  }
  addLock();
  for(auto& x:array){
    writeFileBuff << x << " ";
  }
  writeFileBuff << endl;
  removeLock();
  return true;
}
vector<string> _file::readline(){
  if(!readBuffOpen(true)){
    return {};
  }
  vector<string> ret;
  string _str;
  getline(readFileBuff,_str);
  int left = 0;
  int right = 1;
  int size = ret.size();
  while(right <= size){
    if(_str[right] == ' '){
      ++right;
      continue;
    }else{
      ret.push_back(_str.substr(left,right-left));
      left = right;
      ++right;
    }
  }
  return ret;
}

bool _file::addLock(){
  if(!_file::isExist(lockPath)){
    ofstream filewritebuff;
    filewritebuff.open(lockPath,ios::app);
    if(filewritebuff.is_open()){
         filewritebuff.close();
      return true;
    }
  }
  return false;
}

bool _file::removeLock(){
  if(!isExist()){
    return false;
  }
  
  ifstream filereadbuff(lockPath);
  if(!filereadbuff.good()){
    filereadbuff.close();
    return false;
  }else{
    if(!remove(lockPath.c_str())){ // 成功返回0，失败返回-1
      filereadbuff.close();
      return true;
    }else{
      filereadbuff.close();
      return false;
    }
  }
}

bool _file::createFile(string path){
  if(_file::isExist(path)){
    return false;
  }
  ofstream filewritebuff;
  filewritebuff.open(path,ios::out);
  if(filewritebuff.good()){
      filewritebuff.close();
      return true;
    }
    filewritebuff.close();
  return false;
}

bool _file::createFile(){
  if(!writeBuffOpen(false)){
    return false;
  }
  if(writeFileBuff.good()){
      writeFileBuff.close();
      return true;
    }
    writeFileBuff.close();
  return false;
}

bool _file::writeBuffOpen(bool need){
  if(need && !isExist()){
    return false;
  }
  if(!writeFileBuff.is_open()){
    writeFileBuff.open(filePath,ios::app);
  } 
  return true;
}

bool _file::readBuffOpen(bool need){
  if(need && !isExist()){
    return false;
  }
  if(!readFileBuff.is_open()){
    readFileBuff.open(filePath);
  } 
  return true;
}