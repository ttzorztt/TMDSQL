/*
 * @Description  : 用户数据操作类封装
 * @Auto         : TMD
 * @Date         : 2022-12-17 11:01:28
 * @LastEditTime : 2022-12-22 10:29:12
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

std::set<std::string> User::nameBuff;
int User::count = 0;
_file User::pd(_TruePathForUserData);
User::User() : loginStatus(false), reset(false), power(TYPE_POWER::NONE) {}
User::User(std::string UserName, std::string UserPassword)
    : UserName(UserName),
      UserPassword(UserPassword),
      loginStatus(false),
      reset(false),
      power(TYPE_POWER::NONE) {
  this->readAllNameDate();
  this->loginStatus = this->login();
}

void User::readAllNameDate() {
  UserVectorBuff;
  while (pd.readline(vectorbuff)) {
    User::nameBuff.insert(vectorbuff[0]);
  }
}
void User::addUser(std::string UserName,
                   std::string Userpassword,
                   TYPE_POWER power) {
                     UserVectorBuff;
  vectorbuff.clear();
  vectorbuff.push_back(UserName);
  vectorbuff.push_back(UserPassword);
  vectorbuff.push_back(std::to_string((int)power));
  pd.write(vectorbuff, type_mode::WRITEBUFF_MODE_APP);
}
bool User::addNormalUser(std::string UserName, std::string Userpassword) {
  if (power >= 2)
    return false;
  this->addUser(UserName, UserPassword, TYPE_POWER::NORMAL);
  return true;
}
bool User::addManagerUser(std::string UserName, std::string Userpassword) {
  if (power >= 1)
    return false;
  this->addUser(UserName, UserPassword, TYPE_POWER::Manager);
  return true;
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
TYPE_POWER User::ReturnPower() const{
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