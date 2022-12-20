/*
 * @Description  : 用户数据操作类封装
 * @Auto         : TMD
 * @Date         : 2022-12-17 11:01:28
 * @LastEditTime : 2022-12-20 10:53:04
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
_file User::pd(_TruePathForUserData);
User::User(std::string UserName, std::string UserPassword)
    : UserName(UserName), UserPassword(UserPassword), loginStatus(false) {
  this->readAllNameDate();
  this->loginStatus = this->login();
}
User::User() : loginStatus(false) {}
void User::readAllNameDate() {
  while (pd.readline(buff)) {
    nameBuff.insert(buff[0]);
  }
}
bool User::login() {
  pd.setReadSeek(0);
  while (pd.readline(buff)) {
    if (buff[0] == this->UserName) {
      if (buff[1] == this->UserPassword) {
        this->power = (TYPE_POWER)atoi(buff[2].c_str());
        return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
      } else {
        return false;
      }
    }
  }
  return false;
}
bool User::login(std::string UserName,std::string UserPassword) {
  this->UserName = UserName;
  this->UserPassword = UserPassword;
  this->loginStatus = this->login();
  return this->loginStatus;
}

void User::resetPassword(std::string Userpassword){
  this->UserPassword = Userpassword;
  rename(_TruePathForUserData.c_str(),("." + _TruePathForUserData).c_str());
  _file tmp(_TruePathForUserData);
  
}