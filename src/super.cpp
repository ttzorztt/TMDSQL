/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:19
 * @LastEditTime : 2022-11-09 22:09:38
 */

#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
std::vector<std::string> _super::openDirReturnFileName(std::string truePath) {
  bool isTableOrDatabase = (".csv" == truePath.substr(truePath.size() - 4));
  DIR* dirname = opendir(truePath.c_str());
  struct dirent* dirInfo;
  std::vector<std::string> name;
  int count = 2;
  if (".csv" == truePath.substr(truePath.size() - 4)) {
    while ((dirInfo = readdir(dirname)) != 0) {
      if (count > 0) {
        --count;
        continue;
      }
      std::string tmpname = dirInfo->d_name;
      name.push_back(tmpname.substr(0, tmpname.size() - 4));
    }
  } else {
    while ((dirInfo = readdir(dirname)) != 0) {
      if (count > 0) {
        --count;
        continue;
      }
      std::string tmpname = dirInfo->d_name;
      name.push_back(tmpname.substr(0, tmpname.size()));
    }
  }
  closedir(dirname);
  return name;
}

bool _super::create() {
  return true;
}
bool _super::remove() {
  return true;
}
type _super::returnType() {
  return type::_TYPE_TABLE;
}
std::string _super::returnName() {
  return name;
}
int _super::returnCount() {
  return -1;
}
bool _super::isExist() {
  return false;
}
_super::~_super() {}
_super::_super(_super& copy) {
  this->name = copy.name;
}
_super::_super(std::string name) {
  this->name = name;
}

bool _super::isExist(std::string name, type style) {
  return access(_super::returnTruePath(name, style).c_str(), F_OK) != -1;
}
bool _super::isExist(std::string truePath) {
  return access(truePath.c_str(), F_OK) != -1;
}
std::string _super::returnTruePath(std::string Name, type style) {
  switch (style) {
    case type::_TYPE_DADABASE:
      return _databasePath + Name;
      break;
    case type::_TYPE_TABLE_LOCK:
      return _tableLockPath + "." + Name + ".csv";
      break;
    case type::_TYPE_TADABLASE_LOCK:
      return _databaseLockPath + "." + Name;
      break;
    case type::_TYPE_TABLE:
      return _tablePath + Name + ".csv";
    case type::_TYPE_INDEX:
      return _indexPath + Name + ".csv";
      break;
    default:
      break;
  }
  return "";
}
// bool _super::isExist() {
//   switch (style) {
//     case type::_TYPE_DIR:
//       return access(this->path.c_str(), F_OK) != -1;
//       break;
//     case type::_TYPE_FILE:
//     case type::_TYPE_INDEX:
//     case type::_TYPE_LOCK:
//       return access((this->path + ".csv").c_str(), F_OK) != -1;
//       break;
//     default:
//       return false;
//       break;
//   }
// }

// _super::_super(std::string Path, type style) {
//   int size = Path.size() - 1;
//   while (size >= 0) {
//     if (Path[size] == '/') {
//       break;
//     }
//     --size;
//   }
//   this->name = Path.substr(size + 1, INT64_MAX);
//   this->path = Path;
//   this->style = style;
// }

// bool _super::remove(){
//     switch (style){
//         case type::_TYPE_DIR :{

//             return std::remove(this->path.c_str());
//             break;
//         }
//         case type::_TYPE_FILE:
//         case type::_TYPE_INDEX:
//         case type::_TYPE_LOCK:{
//             return std::remove(this->path.c_str());
//             break;
//         }
//         default:
//             break;
//     }
//     return false;
// }

// _super::_super(std::string& Path, type style) {
//   int size = Path.size() - 1;
//   while (size >= 0) {
//     if (Path[size] == '/') {
//       break;
//     }
//     --size;
//   }
//   this->name = Path.substr(size + 1, INT64_MAX);
//   this->path = Path;
//   this->style = style;
// }
// _super::_super(_super& copy) {
//   this->name = copy.returnName();
//   this->path = copy.returnPath();
//   this->style = copy.returnType();
// }
// _super::~_super() {}
// std::string _super::returnName() {
//   return this->name;
// }
// bool _super::create() {
//   if (isExist()) {
//     return false;
//   }
//    switch (style) {
//     case type::_TYPE_DIR:{
//       mkdir(this->path.c_str(), 777);
//       break;
//     }
//     case type::_TYPE_FILE:
//     case type::_TYPE_INDEX:
//     case type::_TYPE_LOCK:{
//       std::ofstream filewritebuff;
//       filewritebuff.open(this->path, std::ios::out);
//       if (filewritebuff.good()) {
//         filewritebuff.close();
//         return true;
//       }
//       filewritebuff.close();
//       return false;
//     }
//     default:
//       break;
//   }
//   if (isExist()) {
//     return false;
//   }
//   return true;
// }
// std::string _super::returnPath() {
//   return this->path;
// }

// type _super::returnType() {
//   return style;
// }