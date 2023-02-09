/**
 * @file User.cpp
 * @brief 用户数据操作类封装
 * @author TMD
 * @version 1.3
 * @date 2022-12-17
 */
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#include "super.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "DataBase.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
std::set<std::string> User::nameBuff;
std::set<std::string> User::nowLoginId;
int User::count = 0;
_file User::pd(_PathForUserData + std::string("pd"));
_file User::pdlock(_PathForUserData + std::string("pd_tmp"));
bool User::addLock(){
	if(pdlock.isExist()){
		return false;
	}else{
		pdlock.create();
		return true;
	}
}
bool User::removeLock(){
	if(!pdlock.isExist()){
		return false;
	}else{
		pdlock.remove();
		return true;
	}
}
User::User()
	: loginStatus(false),
	errorCause(TYPE_LOGIN_ERROR::未登录),
	reset(false),
	power(TYPE_POWER::NONE),
	UserName("未登录"),
	UserPassword("") {
		if (nameBuff.size() == 0) {
			this->readAllNameDate();
		}
	}
User::User(std::string UserName, std::string UserPassword)
	: UserName("未登录"),
	UserPassword(""),
	loginStatus(false),
	reset(false),
	errorCause(未登录),
	power(TYPE_POWER::NONE) {
		if (nameBuff.size() == 0) {
			this->readAllNameDate();
		}
		++count;
		this->loginStatus = this->login();
	}
void User::readAllNameDate() {
	vstring vectorbuff;
	while (pd.readline(vectorbuff)) {
		User::nameBuff.insert(vectorbuff[0]);
	}
}
void User::exitLogin() {
	if (loginStatus) {
		this->power = TYPE_POWER::NONE;
		this->loginStatus = false;
		this->errorCause = 未登录;
		this->nowLoginId.erase(this->UserName);
	}
}
void User::addUser(std::string UserName,
		std::string Userpassword,
		TYPE_POWER power) {
	vstring vectorbuff;
	vectorbuff.clear();
	vectorbuff.push_back(UserName);
	vectorbuff.push_back(Userpassword);
	vectorbuff.push_back(std::to_string((int)power));
	pd.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
	++count;
	nameBuff.insert(UserName);
}
bool User::addNormalUser(std::string UserName, std::string Userpassword) {
	if (nameBuff.count(UserName)) {
		return false;
	}
	this->addUser(UserName, Userpassword, TYPE_POWER::NORMAL);
	return true;
}
bool User::addManagerUser(std::string UserName, std::string Userpassword) {
	if (nameBuff.count(UserName))
		return false;
	this->addUser(UserName, Userpassword, TYPE_POWER::Manager);
	return true;
}
std::string User::ReturnUserName() const {
	return (this->loginStatus) ? this->UserName : "未登录";
}
bool User::deleteUser(std::string index) {
	return pd.deleteLine(index);
}
bool User::login() {
	pd.setReadSeek(0);
	vstring vectorbuff;
	while (pd.readline(vectorbuff)) {
		if (vectorbuff[0] == this->UserName) {
			if (vectorbuff[1] == this->UserPassword) {
				this->power = (TYPE_POWER)atoi(vectorbuff[2].c_str());
				++this->count;
				this->loginStatus = true;
				return true;
			} else {
				this->errorCause = 密码错误;
				return false;
			}
		}
	}
	this->errorCause = 帐号不存在;
	return false;
}
TYPE_POWER User::returnInputUserPower(std::string UserName) {
	pd.setReadSeek(0);
	vstring vectorbuff;
	while (pd.readline(vectorbuff)) {
		if (vectorbuff[0] == UserName) {
			return (TYPE_POWER)atoi(vectorbuff[2].c_str());
		}
	}
	return TYPE_POWER::NONE;
}
bool User::login(std::string UserName, std::string UserPassword) {
	pd.setReadSeek(0);
	vstring vectorbuff;
	while (pd.readline(vectorbuff)) {
		if (vectorbuff[0] == UserName) {
			if (vectorbuff[1] == UserPassword) {
				this->power = (TYPE_POWER)atoi(vectorbuff[2].c_str());
				this->UserName = UserName;
				this->UserPassword = UserPassword;
				this->loginStatus = true;
				++this->count;
				return true;
			} else {
				this->errorCause = 密码错误;
				return false;
			}
			break;
		}
	}
	this->errorCause = 帐号不存在;
	return false;
}
bool User::ReturnLoginStatus() const {
	return this->loginStatus;
}
void User::resetPassword(std::string Userpassword) {
	// if (!this->loginStatus) {
	//   return;
	// }
	// this->UserPassword = Userpassword;
	// rename(_PathForUserData, ("." + _PathForUserData).c_str());
	// _file tmp(_PathForUserData);
	// this->reset = true;
}

TYPE_POWER User::ReturnPower() const {
	return this->power;
}
TYPE_LOGIN_ERROR User::returnErrorCase() const {
	return this->errorCause;
}
User::~User() {
	--this->count;
	if (!reset)
		return;
	vstring vectorbuff;
	pd.deleteLine(this->UserName);
	vectorbuff.clear();
	vectorbuff.push_back(UserName);
	vectorbuff.push_back(UserPassword);
	vectorbuff.push_back(std::to_string((int)power));
	pd.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
}
