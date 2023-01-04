/*
 * @Description  : 用户数据操作类封装
 * @Auto         : TMD
 * @Date         : 2022-12-17 11:01:28
 * @LastEditTime : 2023-01-04 11:47:06
 */
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
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
_file User::pd(_TruePathForUserData);
User::User()
    : loginStatus(false),
      reset(false),
      power(TYPE_POWER::NONE),
      UserName(""),
      UserPassword("") {
  if (nameBuff.size() == 0) {
    this->readAllNameDate();
  }
}
User::User(std::string UserName, std::string UserPassword)
    : UserName(UserName),
      UserPassword(UserPassword),
      loginStatus(false),
      reset(false),
      power(TYPE_POWER::NONE) {
  if (nameBuff.size() == 0) {
    this->readAllNameDate();
  }
  ++count;
  this->loginStatus = this->login();
}
void User::readAllNameDate() {
  UserVectorBuff;
  while (pd.readline(vectorbuff)) {
    User::nameBuff.insert(vectorbuff[0]);
  }
}
void User::exitLogin() {
  if (loginStatus) {
    this->power = TYPE_POWER::NONE;
    this->loginStatus = false;
    this->nowLoginId.erase(this->UserName);
  }
}
void User::addUser(std::string UserName,
                   std::string Userpassword,
                   TYPE_POWER power) {
  UserVectorBuff;
  vectorbuff.clear();
  vectorbuff.push_back(UserName);
  vectorbuff.push_back(Userpassword);
  vectorbuff.push_back(std::to_string((int)power));
  pd.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
  ++count;
  nameBuff.insert(UserName);
}
bool User::addNormalUser(std::string UserName, std::string Userpassword) {
  if (power >= 2 || nameBuff.count(UserName)){
    return false;
  }
  this->addUser(UserName, Userpassword, TYPE_POWER::NORMAL);
  return true;
}
bool User::addManagerUser(std::string UserName, std::string Userpassword) {
  if (power >= 1 ||  nameBuff.count(UserName))
    return false;
  this->addUser(UserName, Userpassword, TYPE_POWER::Manager);
  return true;
}
std::string User::ReturnUserName() const {
  return (this->loginStatus) ? this->UserName : "";
}
bool User::login() {
  pd.setReadSeek(0);
  UserVectorBuff;
  while (pd.readline(vectorbuff)) {
     if (vectorbuff[0] == this->UserName) {
      if (vectorbuff[1] == this->UserPassword) {
           this->power = (TYPE_POWER)atoi(vectorbuff[2].c_str());
        ++this->count;
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}
bool User::login(std::string UserName, std::string UserPassword) {
  this->UserName = UserName;
  this->UserPassword = UserPassword;
  this->loginStatus = this->login();
  return this->loginStatus;
}
bool User::ReturnLoginStatus() const {
  return this->loginStatus;
}
void User::resetPassword(std::string Userpassword) {
  if (!this->loginStatus) {
    return;
  }
  this->UserPassword = Userpassword;
  rename(_TruePathForUserData.c_str(), ("." + _TruePathForUserData).c_str());
  _file tmp(_TruePathForUserData);
  this->reset = true;
}

TYPE_POWER User::ReturnPower() const {
  return this->power;
}
User::~User() {
  --this->count;
  if (!reset)
    return;
  UserVectorBuff;
  pd.deleteLine(this->UserName);
  vectorbuff.clear();
  vectorbuff.push_back(UserName);
  vectorbuff.push_back(UserPassword);
  vectorbuff.push_back(std::to_string((int)power));
  pd.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
}