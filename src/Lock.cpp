/**
 * @file Lock.cpp
 * @brief 封装锁操作
 * @author TMD
 * @version 1.3
 * @date 2023-02-08
 */
#ifndef _LOCK_H_
#define _LOCK_H_
#include "Lock.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif
Lock::Lock() {}
Lock::~Lock() {}
bool Lock::addLock(Table& table) {
	_file lock(table.returnTruePath() + "_lock");
	if (!lock.isExist()) {
		lock.create();
		return true;
	}else {
		return false;
	}
}
bool Lock::addLock(std::string truePath) {
	_file lock(truePath + "_lock");
	if (!lock.isExist()) {
		lock.create();
		return true;
	}else {
		return false;
	}
}
bool Lock::addLock(std::string DBID, std::string TBID) {
	_file lock(DBID + "/" + TBID + "_lock", type::_TYPE_TABLE);
	if (!lock.isExist()) {
		lock.create();
		return true;
	}else {
		return false;
	}
}
bool Lock::addLock(_file& file){
	_file lock(file.returnTruePath() + "_lock");
	if(!lock.isExist()){
		lock.create();
		return true;
	}else {
		return false;
	}
}
void Lock::removeLock(_file& file){
	_file lock(file.returnTruePath() + "_lock");
	if(lock.isExist()){
		lock.remove();
	}
}
void Lock::removeLock(std::string DBID, std::string TBID) {
	_file lock(DBID + "/" + TBID + "_lock", type::_TYPE_TABLE);
	if (lock.isExist()) {
		lock.remove();
	}
}

void Lock::removeLock(std::string truePath) {
	_file lock(truePath + "_lock");
	if (lock.isExist()) {
		lock.remove();
	}
}
void Lock::removeLock(Table& table) {
	_file lock(table.returnTruePath() + "_lock");
	if (lock.isExist()) {
		lock.remove();
	}
}
bool Lock::addLog() {
	return false;
}
bool Lock::addPd() {
	return false;
}
