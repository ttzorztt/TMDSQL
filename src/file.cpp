#include "file.h"
_file::_file(string& Path){
  // 如果文件不存在，则退出
  if(! _file::isExists(Path)) return;
  filePath = Path;
  writeFileBuff.open(filePath,ios::app);
  readFileBuff.open(filePath);
  lockPath = "../data/lock/." + filePath;
}
_file::~_file(){
  writeFileBuff.close();
}
bool _file::isExists(string filePath){
  return ifstream(filePath).good();
}
void _file::writeFile(const string& str){
  if(addLock()){
    writeFileBuff << str << endl;
  }
}
void  _file::writeFile(const vector<string>& array){
  if(addLock()){
  for(auto& x:array){
    writeFileBuff << x << " ";
  }
  writeFileBuff << endl;
}
}
vector<string> _file::readline(){
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

    }
  }
  return {};
}

bool _file::addLock(){
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