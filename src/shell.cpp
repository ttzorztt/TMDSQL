/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-12-27 11:54:12
 */
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
std::unordered_map<std::string, int> shell::HashMapCID = {
    {"退出", 0},   {"创建", 1},      {"数据库", 2}, {"删除", 3}, {"选择", 4},
    {"重命名", 5}, {"登录", 6},      {"显示", 7},   {"插入", 8}, {"查询", 9},
    {"表", 10},    {"普通用户", 11}, {"管理员", 12}};
shell::shell() : User() {}
shell::~shell() {}
bool shell::logn(std::string ID, std::string password) {
  return login(ID, password);
}
void shell::toChoose(revstring value) {
  switch (value.size()) {
    case 3:
      if (value[2] == "数据库") {
      }
      break;
    case 2:
    case 1:
    default:
      menuOutput::printCommandError(ReturnPower());
      break;
  }
  if (value.size() == 1 || !HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
  switch (HashMapCID[value[1]]) {
    case 数据库:
      toChooseDatabase(value);
      break;
    case 表:
      toChooseTable(value);
      break;
    default:
      menuOutput::printCommandError(ReturnPower());
  }
}
void shell::toChooseDatabase(revstring value) {
  switch (value.size()) {
    case 3:
      if (HashMapCID.count(value[2])) {
        menuOutput::printCommandError(ReturnPower());
      }
      break;
    case 2:
      menuOutput::printCommandError(ReturnPower());
      break;
    default:
      break;
  }
  if (value.size() == 2) {
    menuOutput::printCommandError(ReturnPower());
  }
  if (!HashMapCID.count(value[2]) && value.size() == 3) {
    switch (pwd.size()) {
      case 0:
        menuOutput::printNotLogin();
        break;
      default:
        if (!User::HaveDatabase(value[2])) {
          menuOutput::printNotExistsDatabase(ReturnPower());
        }
        pwd.clear();
        pwd.push_back("/");
        pwd.push_back(value[2]);
        break;
    }
  }
}
void shell::toChooseTable(revstring value) {
  if (value.size() == 2) {
    menuOutput::printCommandError(ReturnPower());
  }
  switch (pwd.size()) {
    case 0:
      menuOutput::printNotLogin();
      break;
    case 1:
      menuOutput::printNotChooseDatabase(ReturnPower());
      break;
    case 2:

    default:
      break;
  }
  if (pwd.size() == 1) {
  }
}
void shell::toChooseDatabaseTable(revstring value) {}
bool shell::aidCheckData(std::string _str) {
  for (char& ch : _str) {
    if (checkErrorName.count(ch)) {
      return false;
    }
  }
  return true;
}
bool shell::check(std::string _str) {
  vstring vectorbuff;
  _super::stringToVector(_str, vectorbuff);
  int size = vectorbuff.size();
  if (size == 0 || !(HashMapCID.count(vectorbuff[0]))) {
    return false;
  }
  int stap = 0;
  for (; stap < size; ++stap) {
    if (HashMapCID.count(vectorbuff[stap])) {
      command.push_back(HashMapCID[vectorbuff[stap]]);
    } else {
      if (vectorbuff[stap][0] != '@') {
        return false;
      }
      std::string tmp = vectorbuff[stap].substr(1);
      if (!aidCheckData(tmp)){
        return false;
      }
      data.push_back(tmp);
      break;
    }
  }
  for (++stap; stap < size; ++stap) {
    if(aidCheckData(vectorbuff[stap])){
      data.push_back(vectorbuff[stap]);
    }else{
      return false;
    }
  }
}
bool shell::read(std::string str) {
  if (!this->ReturnLoginStatus()) {  //未登录
    menuOutput::printExit(ReturnPower());
  }
  //error
  vstring vectorbuff;
  if (!HashMapCID.count(vectorbuff[0])) {
    return false;
  }
  switch (HashMapCID[vectorbuff[0]]) {
    case 选择:
      toChoose(vectorbuff);
      break;
    case 退出:
      if (vectorbuff.size() == 1) {
        menuOutput::printExit(ReturnPower());
      } else {
        menuOutput::printCommandError(ReturnPower());
      }
      break;
    case 创建:
      if (ReturnPower() < 2) {  // 管理员和超级管理员权限
        toCreate(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(
            ReturnPower());  // 普通用户或未登录没有权限创建
      }
      break;
    case 删除:
      if (ReturnPower() < 2) {
        toDelete(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(ReturnPower());
      }
      break;
    case 重命名:
      if (ReturnPower() < 2) {
        toRename(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(ReturnPower());
      }
      break;
    case 登录:
      if (vectorbuff.size() != 3) {
        menuOutput::printCommandError(ReturnPower());
      } else {
        bool Login = this->login(vectorbuff[1], vectorbuff[2]);
        menuOutput::printLoginOrNot(Login);
      }
      break;
    case 插入:
      if (ReturnLoginStatus() < 2) {
        toInsert(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(ReturnPower());
      }
      break;
    case 查询:
      toFind(vectorbuff);
      break;
    case 显示:
      toShow(vectorbuff);
      break;
    default:
      menuOutput::printCommandError(ReturnPower());
      break;
  }
  return false;
}

void shell::toCreate(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
  switch (HashMapCID[value[1]]) {
    case 表:
      toCreateTable(value);
      break;
    case 数据库:
      toCreateDatabase(value);
      break;
    default:
      menuOutput::printCommandError(ReturnPower());
  }
}
void shell::toCreateTable(revstring value) {}
void shell::toCreateDatabase(revstring value) {}
void shell::toDelete(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
  switch (HashMapCID[value[1]]) {
    case 表:
      toDeleteTable(value);
      break;
    case 数据库:
      toDeleteDatabase(value);
      break;
    default:
      menuOutput::printCommandError(ReturnPower());
  }
}
void shell::toDeleteTable(revstring value) {}
void shell::toDeleteDatabase(revstring value) {}
void shell::toRename(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
  switch (HashMapCID[value[1]]) {
    case 数据库:
      toRenameTable(value);
      break;
    case 表:
      toRenameDatabase(value);
      break;
    default:
      menuOutput::printCommandError(ReturnPower());
      break;
  }
}
void shell::toRenameTable(revstring value) {}
void shell::toRenameDatabase(revstring value) {}
void shell::toInsert(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
}
void shell::toFind(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
}
void shell::toShow(revstring value) {
  if (!HashMapCID.count(value[1])) {
    menuOutput::printCommandError(ReturnPower());
  }
}
