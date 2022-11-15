/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:51
 * @LastEditTime : 2022-11-15 13:59:16
 */

#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
#endif
Index::Index(){
    ++Index::count;
}

Index::~Index(){}

int Index::returnCount(){
    return Index::count;
}

