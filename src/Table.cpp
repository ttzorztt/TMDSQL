/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-11 21:17:47
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
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

bool Table::create(std::string databaseAndTableName){
  return _super::isExist(databaseAndTableName, type::_TYPE_TABLE);
}

 bool Table::remove(std::string databaseAndTableName){
  return _file::remove(databaseAndTableName,type::_TYPE_TABLE); 
}
 bool Table::append(const std::vector<string>& value){
  return _file::writeFile(this->name,value);
}
void Table::updateIndex(){

}
std::vector<std::string> Table::find(std::string index){
  
}