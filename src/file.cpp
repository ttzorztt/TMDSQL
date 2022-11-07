/*
 * @Description  : 文件操作类_file的实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 17:07:21
 * @LastEditTime : 2022-11-07 09:17:15
 */
#include "file.h"
#include <iostream>
using namespace std;
_file::_file(string Path) {
  int size = Path.size() - 1;
  while (size >= 0) {
    if (Path[size] == '/') {
      break;
    }
    --size;
  }
  this->name = Path.substr(size + 1, INT64_MAX);
  path = Path;
  lockPath = "../data/lock/." + Path;
}
_file::~_file() {
  writeFileBuff.close();
}
bool _file::isExist() {
  return access(this->path.c_str(), F_OK) != -1;
}
bool _file::isExist(string _name) {
  return access(_name.c_str(), F_OK) != -1;
}
bool _file::writeFile(const string& str) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  while (addLock())
    ;
  writeFileBuff << str << endl;
  removeLock();
  return true;
}
bool _file::writeFile(const vector<string>& array) {
  if (!writeBuffOpen(true)) {
    return false;
  }
  addLock();
  for (auto& x : array) {
    writeFileBuff << x << " ";
  }
  writeFileBuff << endl;
  removeLock();
  return true;
}
bool _file::writeFile(string Path, const string& str) {
  _file tmd(Path);
  return tmd.writeFile(str);
}
bool _file::writeFile(string Path, const vector<string>& array) {
  _file tmd(Path);
  return tmd.writeFile(array);
}
bool _file::readline(vector<string>& ret) {
  if (!readBuffOpen(true)) {
    return {};
  }
  string _str;
  getline(readFileBuff, _str);
  if (this->returnReadFileBuff().eof()) {
    return false;
  }
  int left = 0;
  int right = 1;
  int size = _str.size();
  while (right <= size) {
    if (_str[right] == ' ') {
      ++right;
      continue;
    } else {
      ret.push_back(_str.substr(left, right - left));
      left = right;
      ++right;
    }
  }
  return true;
}

bool _file::addLock() {
  if (!_file::isExist(lockPath)) {
    ofstream filewritebuff;
    filewritebuff.open(lockPath, ios::app);
    if (filewritebuff.is_open()) {
      filewritebuff.close();
      return true;
    }
  }
  return false;
}
bool _file::removeLock() {
  if (!isExist()) {
    return false;
  }
  ifstream filereadbuff(lockPath);
  if (!filereadbuff.good()) {
    filereadbuff.close();
    return false;
  } else {
    if (!remove(lockPath.c_str())) {  // 成功返回0，失败返回-1
      filereadbuff.close();
      return true;
    } else {
      filereadbuff.close();
      return false;
    }
  }
}
bool _file::createFile(string path) {
  if (_file::isExist(path)) {
    return false;
  }
  ofstream filewritebuff;
  filewritebuff.open(path, ios::out);
  if (filewritebuff.good()) {
    filewritebuff.close();
    return true;
  }
  filewritebuff.close();
  return false;
}

bool _file::createFile() {
  if (!writeBuffOpen(false)) {
    return false;
  }
  if (writeFileBuff.good()) {
    writeFileBuff.close();
    return true;
  }
  writeFileBuff.close();
  return false;
}

bool _file::writeBuffOpen(bool need) {
  if (need && !isExist()) {
    return false;
  }
  if (!writeFileBuff.is_open()) {
    writeFileBuff.open(path, ios::app);
  }
  return true;
}

bool _file::readBuffOpen(bool need) {
  if (need && !isExist()) {
    return false;
  }
  if (!readFileBuff.is_open()) {
    readFileBuff.open(path);
  }
  return true;
}

bool _file::deleteFile(string Path) {
  return remove(Path.c_str());
}

bool _file::deleteFile() {
  return remove(this->path.c_str());
}

const string& _file::returnFilePath() {
  return path;
}
_file::_file(_file& _copy) {
  this->lockPath = _copy.lockPath;
  this->name = _copy.name;
  this->path = _copy.path;
}
const string& _file::returnFileName() {
  return name;
}
const ofstream& _file::returnWriteFileBuff() {
  return writeFileBuff;
}
const ifstream& _file::returnReadFileBuff() {
  return readFileBuff;
}
