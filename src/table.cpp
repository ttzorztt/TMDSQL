/*
 * @Description  : 封装表操作
 * @Autor        : TMD
 * @Date         : 2022-11-06 16:11:53
 * @LastEditTime : 2022-11-07 10:15:06
 */
#ifndef _TABLE_H_
#define _TABLE_H_
#include "table.h"
#endif

_table::_table(string databaseName, string stableName)
    : _file("../data/" + databaseName + "/" + stableName) {}
_table::_table(DataBase database, string tableName)
    : _file(database.returnPath() + "/" + tableName) {}
_table::_table(DataBase database, _file tableName)
    : _file(database.returnPath() + "/" + tableName.returnFilePath()) {}
_table::~_table() {}