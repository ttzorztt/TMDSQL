/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-07 22:32:00
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif

Table::Table(string databaseName, string stableName)
    : _file("../data/" + databaseName + "/" + stableName) {}
Table::Table(DataBase database, string tableName)
    : _file(database.returnPath() + "/" + tableName) {}
Table::Table(DataBase database, _file tableName)
    : _file(database.returnPath() + "/" + tableName.returnName()) {}
Table::~Table() {}