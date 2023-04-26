/*
 * @Description  : 
 * @Autor        : TMD
 * @Date         : 2023-04-25 14:37:14
 * @LastEditTime : 2023-04-25 14:37:15
 */
/**
 * @file TablePCB.cpp
 * @brief 表PCB的实现
 * @author TMD
 * @version 1.3
 * @date 2022-11-20
 */
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
void TablePCB::init() {
	if (file.isExist()) {
		readData();
	} else {
		this->endLineIndex = 0;
		this->length = 0;
		this->index = 0;
		file.create();
		file.inputPCBInformation();
	}
}
TablePCB::TablePCB(std::string DBIDAndTBID)
	: file(DBIDAndTBID, type::_TYPE_PCB) {
		init();
	}
TablePCB::TablePCB(Table& table) : file(table.returnName(), type::_TYPE_PCB) {
	init();
}
TablePCB::TablePCB(std::string DBID, std::string TBID)
	: file(DBID + "/" + TBID, type::_TYPE_PCB) {
		init();
	}
void TablePCB::readData() {
	vstring vec;
	file.readline(vec);
	if (vec.empty()) {
		std::cout << "empty" << std::endl;
		return;
	}
	this->endLineIndex = atoi(vec[1].c_str());
	this->length = atoi(vec[2].c_str());
	this->index = atoi(vec[3].c_str());
}
TablePCB::~TablePCB() {
	writeData();
}
INDEX TablePCB::returnIndex(){
	return this->index;
}
void TablePCB::addLength() {
	++this->length;
}
void TablePCB::writeData() {
	vstring tmp(4);
	tmp[0] = file.returnName();
	tmp[1] = std::to_string(endLineIndex);
	tmp[2] = std::to_string(length);
	tmp[3] = std::to_string(index);
	file.write(tmp, type_mode::WRITEBUFF_MODE_TRUNC);
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
void TablePCB::setIndex(INDEX index) {
	this->index = index;
}
void TablePCB::setEndLineIndex(Table table, POINTER fileIndex) {
	TablePCB pcb(table);
	pcb.setEndLineIndex(fileIndex);
}	
void TablePCB::setIndex(std::string tableName, INDEX fileIndex) {
	TablePCB pcb(tableName);
	pcb.setIndex(fileIndex);
}
