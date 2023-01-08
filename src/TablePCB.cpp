/*
 * @Description  : 表的PCB实现
 * @Autor        : TMD
 * @Date         : 2022-11-20 23:12:57
 * @LastEditTime : 2023-01-08 11:42:58
 */
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
void TablePCB::init() {
  if (file.isExist()) {
    readData();
  } else {
    this->endLineIndex = 0;
    this->length = 0;
    file.create();
    file.inputPCBInformation();
  }
}
TablePCB::TablePCB(std::string DBIDAndTBID)
    : file(DBIDAndTBID, type::_TYPE_PCB) {
  init();
}
TablePCB::TablePCB(Table& table) : file(table.returnName(), type::_TYPE_PCB) {
  init();
}
TablePCB::TablePCB(std::string DBID, std::string TBID)
    : file(DBID + "/" + TBID, type::_TYPE_PCB) {
  init();
}
void TablePCB::readData() {
  vstring vec;
  file.readline(vec);
  if (vec.empty()) {
    std::cout << "empty" << std::endl;
    return;
  }
  this->endLineIndex = atoi(vec[1].c_str());
  this->length = atoi(vec[2].c_str());
  int size = vec.size() - 3;
  for (int a = 0; a < size; ++a) {
    maxSize.push_back(vec[a + 3]);
  }
}

TablePCB::~TablePCB() {
  writeData();
}
void TablePCB::addLength() {
  ++this->length;
}
void TablePCB::writeData() {
  vstring tmp(3);
  tmp[0] = file.returnName();
  tmp[1] = std::to_string(endLineIndex);
  tmp[2] = std::to_string(length);
  file.write(tmp, type_mode::WRITEBUFF_MODE_TRUNC);
}

int TablePCB::returnEndLineIndex() {
  return this->endLineIndex;
}
std::string TablePCB::returnName() {
  return this->file.returnName();
}
void TablePCB::setEndLineIndex(int value) {
  this->endLineIndex = value;
}
void TablePCB::setEndLineIndex(Table table, POINTER fileIndex) {
  TablePCB pcb(table);
  pcb.setEndLineIndex(fileIndex);
}
void TablePCB::setEndLineIndex(std::string tableName, POINTER fileIndex) {
  TablePCB pcb(tableName);
  pcb.setEndLineIndex(fileIndex);
}