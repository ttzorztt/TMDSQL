/*
 * @Description  : 表的PCB实现
 * @Autor        : TMD
 * @Date         : 2022-11-20 23:12:57
 * @LastEditTime : 2022-11-30 23:03:14
 */
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif 
TablePCB::TablePCB(std::string tableName) : file(tableName, type::_TYPE_TABLE) {
  readData();
}
TablePCB::TablePCB(Table table) : file(table.returnName(), type::_TYPE_TABLE) {
  readData();
}

void TablePCB::readData() {
  std::vector<std::string> vec;
  file.readline(vec);
  this->endLineIndex = atoi(vec[1].c_str());
  this->length = atoi(vec[2].c_str());
}
TablePCB::~TablePCB() {
  writeData();
}

void TablePCB::writeData() {
  file.write(
      (file.returnName() + "," + std::to_string(this->endLineIndex)  + "," + std::to_string(this->length)),
      type_mode::MODE_OUT);
}