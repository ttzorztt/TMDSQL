/*
 * @Description: 文件操作类_file的实现
 * @Autor: TMD
 * @Date: 2022-11-01 17:07:21
 * @LastEditTime: 2022-11-05 19:41:29
 */
#include "file.h"
_file::_file(string& Path) {
  name = Path;
  lockPath = "../data/lock/." + Path;
}
_file::~_file() {
  writeFileBuff.close();
}
bool _file::isExist() {
  return access(this->name.c_str(), F_OK);
}
bool _file::isExist(string _name) {
  return access(_name.c_str(), F_OK);
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
vector<string> _file::readline() {
  if (!readBuffOpen(true)) {
    return {};
  }
  vector<string> ret;
  string _str;
  getline(readFileBuff, _str);
  int left = 0;
  int right = 1;
  int size = ret.size();
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
  return ret;
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
    writeFileBuff.open(name, ios::app);
  }
  return true;
}

bool _file::readBuffOpen(bool need) {
  if (need && !isExist()) {
    return false;
  }
  if (!readFileBuff.is_open()) {
    readFileBuff.open(name);
  }
  return true;
}
bool _file::createDir(string dirName) {
  string path = "mkdir " + dirName;
  return mkdir(path.c_str(), 0777);
}

vector<string> _file::openDirReturnFileName(string dirPath) {
  DIR* dirname = opendir(dirPath.c_str());
  struct dirent* dirInfo;
  vector<string> name;
  while ((dirInfo = readdir(dirname)) != 0) {
    name.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  return name;
}
vector<string> _file::openDirReturnFileName() {
  DIR* dirname = opendir(name.c_str());
  struct dirent* dirInfo;
  vector<string> ret;
  int count = 2;
  while ((dirInfo = readdir(dirname)) != 0) {
    if (count != 0) {
      --count;
      continue;
    }
    ret.push_back(dirInfo->d_name);
  }
  closedir(dirname);
  return ret;
}

bool _file::deleteFile(string Path) {
  return remove(Path.c_str());
}

bool _file::deleteFile() {
  return remove(this->name.c_str());
}

bool _file::deleteDir() {
  return rmdir(this->name.c_str());
}

bool _file::deleteDir(string Path) {
  return rmdir(Path.c_str());
}