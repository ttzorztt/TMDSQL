/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-15 16:34:30
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _ALGORITHM_
#define _ALGORITHM_
#include <algorithm>
#endif
int Table::count = 0;
Table::Table(string stableName)
    : _file(stableName, type::_TYPE_TABLE) {
  this->style = type::_TYPE_TABLE;
  ++Table::count;
}
Table::Table(DataBase database, string tableName)
    : _file(database.returnName() + "/" + tableName, type::_TYPE_TABLE) {
  this->style = type::_TYPE_TABLE;
  ++Table::count;
}

Table::~Table() {
    --Table::count;
}

bool Table::create() {
    return _file::create(this->name,style);
}
bool Table::remove() {
    return _file::remove(this->name,style);
}
int Table::returnCount() {
  return Table::count;
}
bool Table::isExist() {
  return _super::isExist(this->name, style);
}

void Table::updateIndex(){

}
std::vector<std::string> Table::find(std::string index){
  return {};
}

bool Table::append(std::vector<std::string> value){
  return Table::append(this->name,value);
}
bool Table::append(Table table,std::vector<std::string> value){
  return Table::append(table.returnName(),value);
}
bool Table::append(std::string tableName,std::vector<std::string> value){
  int fileIndex = 0;
  if(value.size() <= 0){
    return false;
  }
  for(std::string & str : value){
    fileIndex += str.size();
  }
  if(!_file::write(tableName,type::_TYPE_TABLE,value)){
    return false;
  }
  return Table::appInsertIndex(tableName,value[0],fileIndex + 1);
  
}
bool Table::appInsertIndex(std::string index,int fileIndex){
  return Table::appInsertIndex(this->name,index,fileIndex);
}
bool Table::appInsertIndex(std::string tableName,std::string index,int fileIndex){
  return _file::write(tableName,type::_TYPE_INDEX_TABLE,{index,std::to_string(fileIndex)});
}
bool Table::appInsertIndex(Table table,std::string index,int fileIndex){
  return Table::appInsertIndex(table.returnName(),index,fileIndex);
}