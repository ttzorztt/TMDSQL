/*
 * @Description  : 用户数据操作类封装
 * @Auto         : TMD
 * @Date         : 2022-12-17 11:01:28
 * @LastEditTime : 2022-12-21 09:32:47
 */
#ifndef _USER_H_
#define _SUER_H_
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

std::vector<std::string> User::buff(4);
std::set<std::string> User::nameBuff;
int User::count = 0;
_file User::pd(_TruePathForUserData);
User::User(std::string UserName, std::string UserPassword)
    : UserName(UserName),
      UserPassword(UserPassword),
      loginStatus(false),
      reset(false) {
  this->readAllNameDate();
  this->loginStatus = this->login();
}

void User::readAllNameDate() {
  while (pd.readline(buff)) {
    User::nameBuff.insert(buff[0]);
  }
}
void User::addUser(std::string UserName,
                   std::string Userpassword,
                   TYPE_POWER power) {
  buff.clear();
  buff.push_back(UserName);
  buff.push_back(UserPassword);
  buff.push_back(std::to_string((int)power));
  pd.write(buff, type_mode::WRITEBUFF_MODE_APP);
}
bool User::addNormalUser(std::string UserName, std::string Userpassword) {
  if (power >= 2)
    return false;
  this->addUser(UserName, UserPassword, TYPE_POWER::NORMAL);
}
bool User::addManagerUser(std::string UserName, std::string Userpassword) {
  if (power >= 1)
    return false;
  this->addUser(UserName, UserPassword, TYPE_POWER::Manager);
}
bool User::login() {
  pd.setReadSeek(0);
  while (pd.readline(buff)) {
    if (buff[0] == this->UserName) {
      if (buff[1] == this->UserPassword) {
        this->power = (TYPE_POWER)atoi(buff[2].c_str());
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
bool User::ReturnLoginStatus() {
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
TYPE_POWER User::ReturnPower() {
  if (!this->loginStatus)
    return (TYPE_POWER)-1;
  return this->power;
}
User::~User() {
  --this->count;
  if (!reset)
    return;
  pd.deleteLine(this->UserName);
  buff.clear();
  buff.push_back(UserName);
  buff.push_back(UserPassword);
  buff.push_back(std::to_string((int)power));
  pd.write(buff, type_mode::WRITEBUFF_MODE_APP);
}