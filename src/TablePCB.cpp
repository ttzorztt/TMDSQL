/*
 * @Description  : 表的PCB实现
 * @Autor        : TMD
 * @Date         : 2022-11-20 23:12:57
 * @LastEditTime : 2022-12-02 07:19:55
 */
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#include "iostream"
TablePCB::TablePCB(std::string tableName) : file(tableName, type::_TYPE_PCB) {
  if(file.isExist()){
  readData();
  }else{
    std::cout << "TMD" << std::endl;
  }
}
TablePCB::TablePCB(Table table) : file(table.returnName(), type::_TYPE_PCB) {
  readData();
}

void TablePCB::readData() {
  std::vector<std::string> vec;
  file.readline(vec);
  if(vec.empty()){
    std::cout << "empty" << std::endl;
    return;
  }
  this->endLineIndex = atoi(vec[1].c_str());
  this->length = atoi(vec[2].c_str());
}
TablePCB::~TablePCB() {
  writeData();
}

void TablePCB::writeData() {
  file.write((file.returnName() + "," + std::to_string(this->endLineIndex) +
              "," + std::to_string(this->length)),
             type_mode::MODE_TRUNC);
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
bool TablePCB::isOpen() {
  return this->open;
}
void TablePCB::setEndLineIndex(Table table, POINTER fileIndex) {
  TablePCB pcb(table);
  pcb.setEndLineIndex(fileIndex);
}
void TablePCB::setEndLineIndex(std::string tableName, POINTER fileIndex) {
  TablePCB pcb(tableName);
  pcb.setEndLineIndex(fileIndex);
}