/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-12-15 17:02:41
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#include <iostream>
int Table::count = 0;
Table::Table(std::string databaseAndTableName, type style)
    : _file(databaseAndTableName, style) {
  this->style = type::_TYPE_TABLE;
  
  ++Table::count;
}
Table::Table(DataBase database, std::string tableName, type style)
    : _file(database.returnName() + "/" + tableName, style) {
  this->style = type::_TYPE_TABLE;
  ++Table::count;
}

Table::~Table() {
  --Table::count;
}

bool Table::create() {
  std::string str;

         if(_file::create(this->returnName(), type::_TYPE_TABLE)){
           str += "1";
         }else{
           str += "0";
         }
         if(_file::create(this->returnName(), type::_TYPE_INDEX_TABLE)){
           str += "1";
         }else{
           str += "0";
         } 
         if(_file::create(this->returnName(), type::_TYPE_PCB)){
           str += "1";
         }else{
           str += "0";
         }
         std::cout << str << std::endl << std::endl;
         return true;
}
bool Table::remove() {
        if(type::_TYPE_TABLE){
         return _file::remove(this->returnName(), type::_TYPE_INDEX_TABLE) &&
         _file::remove(this->returnName(), type::_TYPE_TABLE) &&
         _file::remove(this->returnName(), type::_TYPE_PCB);
        }
        return true;
} 
int Table::returnCount() {
  return Table::count;
}
bool Table::isExist() {
  return _super::isExist(this->returnName(), style);
}

void Table::updateIndex() {}

std::vector<std::string> Table::find(std::string index) {
  std::vector<std::string> value;
  Table indexFile(this->returnName(), type::_TYPE_INDEX_TABLE);
  while (indexFile.readline(value)) {
    if (value[0] == index) {
      int x = atoi(value[1].c_str());
      std::cout << "x: " << x << std::endl;
      return this->indexReadline(x);
    }
  }
  return {};
}

bool Table::append(std::vector<std::string> value) {
  
  TablePCB pcb(this->returnName());
  int fileIndex = pcb.returnEndLineIndex();
  if (value.size() <= 0) {
    return false;
  }
  this->write("dssfsf",type_mode::WRITEBUFF_MODE_TRUNC);
  this->appInsertIndex(value[0], fileIndex + 2);
  for (std::string& str : value) {
    fileIndex += str.size();
  }
  // std::cout << "fileIndex is "<<  fileIndex << std::endl;
  pcb.addLength();
  pcb.setEndLineIndex(fileIndex + 1);
  // std::cout << pcb.returnEndLineIndex();
  return true;
}
Table::Table(Table& table) : _file(table.name, table.style) {
  this->style = table.style;
  ++this->count;
}
bool Table::append(Table table, std::vector<std::string> value) {
  return table.append(value);
}
bool Table::append(std::string tableName, std::vector<std::string> value) {
  Table tmp(tableName, type::_TYPE_TABLE);
  return tmp.append(value);
}
bool Table::appInsertIndex(std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(this->returnName(), index, fileIndex);
}
bool Table::appInsertIndex(std::string tableName,
                           std::string index,
                           POINTER fileIndex) {
  return _file::write(tableName, type::_TYPE_INDEX_TABLE,
                      {index, std::to_string(fileIndex)},type_mode::WRITEBUFF_MODE_TRUNC);
}
bool Table::appInsertIndex(Table table, std::string index, POINTER fileIndex) {
  return Table::appInsertIndex(table.returnName(), index, fileIndex);
}

std::vector<std::string> Table::indexReadline(POINTER fileIndex) {
  POINTER oldIndex = this->returnReadTell();
  this->readFileBuff.seekg(100);
  std::cout << readFileBuff.tellg() << std::endl;
  std::vector<std::string> value;
  this->readline(value);
  std::cout << value.size() << std::endl;
  for (std::string& x : value) {
    std::cout << x << std::endl;
  }
  std::cout << value[0] << "  TMD " << value[1] << std::endl;
  this->setReadSeek(oldIndex);
  return value;
}

std::vector<std::string> Table::indexReadline(std::string tableName,
                                              POINTER fileIndex) {
  Table _table(tableName, type::_TYPE_TABLE);
  return _table.indexReadline(fileIndex);
}

std::vector<std::string> Table::indexReadline(Table table, POINTER fileIndex) {
  return table.indexReadline(fileIndex);
}