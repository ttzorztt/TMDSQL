/*
 * @Description  : 表的PCB实现
 * @Autor        : TMD
 * @Date         : 2022-11-20 23:12:57
 * @LastEditTime : 2022-11-21 07:27:39
 */
#include "TablePCB.h"
TablePCB::TablePCB(std::string tableName): _super(tableName){
    readData();
}
TablePCB::TablePCB(Table table): _super(table.returnName()){
    readData();
}
void TablePCB::readData(){
    _file(this->name,type::_TYPE_TABLE);
}