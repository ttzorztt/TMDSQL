/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:51
 * @LastEditTime : 2022-11-15 18:12:33
 */

#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#include <iostream>
int Index::count = 0;
Index::Index(){
    ++Index::count;
}

Index::~Index(){}

int Index::returnCount(){
    return Index::count;
}

void Index::update(std::string name){
    std::string truePath = _super::returnTruePath(name,type::_TYPE_INDEX_TABLE);
    std::string newname =  name + ".";
    std::cout << "this->" << name << std::endl;
    // rename(truePath.c_str(), oldPath.c_str());
    
    // _file newfile(newname,type::_TYPE_INDEX_TABLE);
    // if(newfile.isExist()){
    //     newfile.remove();
    // }
    // if(!newfile.isExist()){
    // newfile.create();
    // }
    _file file(name,type::_TYPE_INDEX_TABLE);
    if(file.isExist()){
        std::cout << file.returnTruePath() << endl;
        std::cout << "文件存在" << std::endl;
    }
    std::vector<std::string> value;
    std::cout << file.readline(value) << value.size() << std::endl;
    return;
    int tmpcount = std::atoi(value[value.size() - 1].c_str());
    return;
    // newfile.write("vadfaf");
    
    // while(file.readline(value)){
    //     int size = std::atoi(value[value.size() - 1].c_str());
    //     tmpcount += size;
    //     value[value.size() - 1] = std::to_string(tmpcount);
    //     newfile.write(value);
    // }
}
void Index::update(Table table){
    Index::update(table.returnName());
}