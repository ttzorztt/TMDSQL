#include "file.h"
_file::_file(string& Path){
  filePath = Path;
  lockPath = "../data/lock/." + filePath;
}
_file::~_file(){
  writeFileBuff.close();
}
bool _file::isExists(){
  return ifstream(this->filePath).good();
}
bool _file::isExists(string filePath){
  return ifstream(filePath).good();
}
bool _file::writeFile(const string& str){
  if(!isExists()){
    return false;
  }
  // 判断ofstream是否打开
  if(!writeFileBuff.is_open()){ 
    writeFileBuff.open(filePath);
  }
  if(addLock()){
    writeFileBuff << str << endl;
  }
  return true;
}
bool  _file::writeFile(const vector<string>& array){
  if(!isExists()){ 
    return false;
  }
  if(!writeFileBuff.is_open()){
    writeFileBuff.open(filePath);
  } 
  if(addLock()){
    for(auto& x:array){
      writeFileBuff << x << " ";
    }
    writeFileBuff << endl;
  }
  return true;
}
vector<string> _file::readline(){
  vector<string> ret;
  string _str;
  readFileBuff.open(filePath,ios::in);
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
  if(!isExists()){
    return false;
  }
  ifstream filereadbuff(lockPath);
  if(filereadbuff.good()){
    filereadbuff.close();
    return false;
  } else{
    ofstream filewritebuff(lockPath);
    if(filewritebuff.good()){
      filewritebuff.close();
      return true;
    }
    filewritebuff.close();
    filereadbuff.close();
  }
  return false;
}

bool _file::removeLock(){
  if(!isExists()){
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
  if(_file::isExists(path)){
    return false;
  }
  ofstream filewritebuff(path);
  if(filewritebuff.good()){
      filewritebuff.close();
      return true;
    }
    filewritebuff.close();
  return false;
}

bool _file::createFile(){
  if(isExists()){
    return false;
  }
  writeFileBuff.open(filePath);
  if(writeFileBuff.good()){
      writeFileBuff.close();
      return true;
    }
    writeFileBuff.close();
  return false;
}

void _file::writeBuffOpen(){
  if(isExists() && !writeFileBuff.is_open()){
    writeFileBuff.open(filePath);
  } 
}

void _file::readBuffOpen(){
    if(isExists() && !readFileBuff.is_open()){
    readFileBuff.open(filePath);
  } 
}