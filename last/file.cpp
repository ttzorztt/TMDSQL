/**
 * @file file.cpp
 * @brief 文件操作类的实现
 * @author TMD
 * @version 1.3
 * @date 2023-11-01
 */
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"

#include <cstdio>

#include "super.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
#endif
//当前打开的文件数总数
int _file::count = 0;
_file::_file(std::string Name, type style) : _super(Name) {
  this->style = style;
  this->truePath = _super::returnTruePath(Name, style);
  ++_file::count;
  this->nowMode = type_mode::DEFAULT;
}
_file::_file(std::string TruePath)
    : _super(_super::dispartDatabaseNameAndTableName(TruePath)[1]) {
  this->truePath = TruePath;
  ++_file::count;
  this->nowMode = type_mode::DEFAULT;
  this->style = type::_TYPE_NONE;
}
_file::_file(_file& _copy) : _super(_copy.returnName()) {
  this->style = _copy.returnType();
  this->truePath = _copy.truePath;
  ++_file::count;
  this->nowMode = type_mode::DEFAULT;
}
_file::~_file() {
  if (writeFileBuff.is_open()) {
    writeFileBuff.close();
  }
  if (readFileBuff.is_open()) {
    readFileBuff.close();
  }
  --_file::count;
}
bool _file::deleteTableLine(std::string index) {
  std::string oldTruePath = this->truePath;
  bool command = false;
  vstring vectorbuff;
  Table* tmptable = new Table(this->name + "tmp", type::_TYPE_TABLE);
  if (tmptable->isExist()) {
    tmptable->remove();
  }
  tmptable->create();
  TablePCB* tmpPCB = new TablePCB(this->name);
  int indexcol = tmpPCB->returnIndex();
  delete tmpPCB;
  _file* tmpOldFile = new _file(this->returnName(), type::_TYPE_TABLE);
  while (tmpOldFile->readline(vectorbuff)) {
    if (vectorbuff[indexcol] == index) {
      command = true;
      continue;
    } else {
      tmptable->append(vectorbuff);
    }
  }
  delete tmpOldFile;
  rename(this->name + "tmp", this->name, type::_TYPE_TABLE);  //表改名
  rename(this->name + "tmp", this->name,
         type::_TYPE_INDEX_TABLE); /* index改名 */
  _file(this->name + "tmp", type::_TYPE_PCB).remove();
  _file(this->name + "tmp", type::_TYPE_VIEW).remove();
  delete tmptable;
  return command;
}
bool _file::deleteFileLine(std::string index) {
  std::string oldTruePath = this->truePath;
  bool command = false;
  vstring vectorbuff;
  _file* tmpfile = new Table(this->truePath + "tmp");
  if (tmpfile->isExist()) {
    tmpfile->remove();
  }
  tmpfile->create();
  _file* tmpOldFile = new _file(this->truePath);
  while (tmpOldFile->readline(vectorbuff)) {
    if (vectorbuff[0] == index) {
      command = true;
      continue;
    } else {
      tmpfile->write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
    }
  }
  delete tmpOldFile;
  rename(this->name + "tmp", this->name,
         type::_TYPE_INDEX_TABLE); /* index改名 */
  _file::rename(this->truePath + "tmp", this->truePath);
  delete tmpfile;
  return command;
}
bool _file::deleteCol(const int& col) {
  std::string oldTruePath = this->truePath;
  vstring vectorbuff;
  vstring tmpvectorbuff;
  Table* tmptable = new Table(this->name + "tmp", type::_TYPE_TABLE);
  if (tmptable->isExist()) {
    tmptable->remove();
  }
  tmptable->create();
  _file* oldtable = new _file(this->name, type::_TYPE_TABLE);
  oldtable->readline(vectorbuff);
  int size = vectorbuff.size();
  if (col < 0 || col > size) {
    return false;
  }
  do {
    tmpvectorbuff.clear();
    for (int a = 0; a < size; ++a) {
      if (a == col) {
        continue;
      } else {
        tmpvectorbuff.push_back(vectorbuff[a]);
      }
    }
    tmptable->append(tmpvectorbuff);
  } while (oldtable->readline(vectorbuff));
  delete oldtable;
  delete tmptable;
  rename(this->name + "tmp", this->name, type::_TYPE_TABLE);  //表改名
  rename(this->name + "tmp", this->name, type::_TYPE_INDEX_TABLE);
  _file(this->name + "tmp", type::_TYPE_PCB).remove();
  _file(this->name + "tmp", type::_TYPE_VIEW).remove();
  return true;
}
void _file::setOpenBuff(MODE mode) {
  if ((mode == type_mode::WRITEBUFF_MODE_APP &&
       this->nowMode == type_mode::WRITEBUFF_MODE_APP) ||
      (mode == type_mode::READBUFF_MODE && mode == this->nowMode)) {
    return;
  }
  switch (mode) {
    case type_mode::READBUFF_MODE: {
      if (readFileBuff.is_open()) {
        readFileBuff.clear();
      }
      readFileBuff.open(this->truePath);
      this->nowMode = type_mode::READBUFF_MODE;
      break;
    }
    case type_mode::WRITEBUFF_MODE_APP: {
      if (readFileBuff.is_open()) {
        writeFileBuff.clear();
      }
      writeFileBuff.open(this->truePath, std::ios::app);
      this->nowMode = type_mode::WRITEBUFF_MODE_APP;
      break;
    }
    case type_mode::WRITEBUFF_MODE_TRUNC: {
      if (readFileBuff.is_open()) {
        writeFileBuff.clear();
      }
      writeFileBuff.open(this->truePath, std::ios::trunc);
      this->nowMode = type_mode::WRITEBUFF_MODE_TRUNC;
      break;
    }
    default:
      break;
  }
}

void _file::setReadSeek(POINTER fileIndex) {
  /* if (this->readFileBuff.eof()) { */
  this->readFileBuff.close();
  this->readFileBuff.open(this->truePath);
  /* } */
  this->readFileBuff.seekg(fileIndex, std::ios::beg);
}
void _file::setWriteSeek(POINTER fileIndex) {
  writeFileBuff.seekp(fileIndex, std::ios::beg);
}
POINTER _file::returnReadTell() { return readFileBuff.tellg(); }
POINTER _file::returnWriteTell() { return writeFileBuff.tellp(); }
bool _file::write(std::string str, type_mode mode) {
  switch (mode) {
    case type_mode::WRITEBUFF_MODE_APP: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_APP);
      writeFileBuff << std::endl << str;
      break;
    }
    case type_mode::WRITEBUFF_MODE_TRUNC: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_TRUNC);
      writeFileBuff << str << std::endl;
      break;
    }
    case type_mode::DEFAULT:
    case type_mode::READBUFF_MODE:
      break;
  }
  this->writeFileBuff.flush();
  return true;
}

void _file::resetPath(std::string Name, type style) {
  this->name = Name;
  this->nowMode = type_mode::DEFAULT;
  this->style = style;
  this->truePath = _super::returnTruePath(Name, style);
}
bool _file::writeAnyLine(vvstring array, type_mode mode) {
  switch (mode) {
    case type_mode::WRITEBUFF_MODE_APP: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_APP);
      break;
    }
    case type_mode::WRITEBUFF_MODE_TRUNC: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_TRUNC);
      break;
    }
    case type_mode::DEFAULT:
    case type_mode::READBUFF_MODE:
      break;
  }
  int size = array.size();
  if (size == 0) {
    return false;
  }
  for (int tmp = 0; tmp < size; ++tmp) {
    writeFileBuff << array[tmp][0];
    int lineSize = array[tmp].size();
    for (int index = 1; index < lineSize; ++index) {
      writeFileBuff << "," << array[tmp][index];
    }
    writeFileBuff << std::endl;
  }
  this->writeFileBuff.flush();
  return true;
}
bool _file::write(const vstring array, type_mode mode) {
  switch (mode) {
    case type_mode::WRITEBUFF_MODE_APP: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_APP);
      break;
    }
    case type_mode::WRITEBUFF_MODE_TRUNC: {
      this->setOpenBuff(type_mode::WRITEBUFF_MODE_TRUNC);
      break;
    }
    case type_mode::DEFAULT:
    case type_mode::READBUFF_MODE:
      break;
  }
  int size = array.size();
  if (size == 0) {
    return false;
  }
  writeFileBuff << array[0];
  for (int index = 1; index < size; ++index) {
    writeFileBuff << "," << array[index];
  }
  writeFileBuff << std::endl;
  this->writeFileBuff.flush();
  return true;
}
bool _file::remove(std::string Name, type style) {
  return _file::remove(_super::returnTruePath(Name, style));
}
bool _file::remove(std::string truePath) {
  if (!_super::isExist(truePath)) {
    return false;
  }
  std::remove(truePath.c_str());
  if (!_super::isExist(truePath)) {
    --_file::count;
    return true;
  }
  return false;
}
bool _file::write(std::string Name, type style, const vstring array,
                  type_mode mode) {
  _file tmd(Name, style);
  return tmd.write(array, mode);
}
bool _file::write(std::string Name, type style, const std::string& str,
                  type_mode mode) {
  _file tmd(Name, style);
  return tmd.write(str, mode);
}
bool _file::readline(revstring ret) {
  ret.clear();
  this->setOpenBuff(type_mode::READBUFF_MODE);
  std::string _str;

  if (this->returnReadFileBuff().eof()) {
    return false;
  }
  getline(readFileBuff, _str);
  if (_str == "") {
    return false;
  }
  _super::stringToVector(_str, ret);
  return true;
}

type _file::returnType() { return this->style; }
bool _file::create(std::string TruePath) {
  if (_super::isExist(TruePath)) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(TruePath, std::ios::out);
  if (filewritebuff.good()) {
    ++_file::count;
  }
  filewritebuff.close();
  return true;
}
bool _file::create(std::string name, type style) {
  std::string truePath = _super::returnTruePath(name, style);
  if (_super::isExist(truePath) || style == type::_TYPE_DATABASE) {
    return false;
  }
  std::ofstream filewritebuff;
  filewritebuff.open(truePath, std::ios::out);
  if (filewritebuff.good()) {
    ++_file::count;
  }
  filewritebuff.close();
  if (style == type::_TYPE_PCB) {
    _file(name, type::_TYPE_PCB).inputPCBInformation();
  }
  return true;
}
void _file::inputPCBInformation() {
  std::string input = this->name + ",0,0,0";
  this->write(input, type_mode::WRITEBUFF_MODE_TRUNC);
  this->setReadSeek(0);
  this->setWriteSeek(0);
}
bool _file::create() { return _file::create(this->name, this->style); }
std::string _file::returnTruePath() { return truePath; }
bool _file::remove() { return _file::remove(this->name, style); }
std::ofstream& _file::returnWriteFileBuff() { return writeFileBuff; }
std::ifstream& _file::returnReadFileBuff() { return readFileBuff; }
bool _file::isExist() { return _super::isExist(this->truePath); }
int _file::returnCount() { return _file::count; }
void _file::rename(std::string newTrueName) {
  std::rename(this->truePath.c_str(), newTrueName.c_str());
}
void _file::rename(std::string oldname, std::string newname, type fileType) {
  std::rename(_super::returnTruePath(oldname, fileType).c_str(),
              _super::returnTruePath(newname, fileType).c_str());
}
void _file::rename(std::string oldTruePath, std::string newTrueName) {
  std::rename(oldTruePath.c_str(), newTrueName.c_str());
}