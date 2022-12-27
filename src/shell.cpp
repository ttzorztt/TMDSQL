/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-12-27 17:39:01
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
std::unordered_map<std::string, TYPE_CID> shell::HashMapCID = {
    {"退出", 退出},    {"创建", 创建}, {"数据库", 数据库},
    {"删除", 删除},    {"选择", 选择}, {"重命名", 重命名},
    {"登录", 登录},    {"显示", 显示}, {"插入", 插入},
    {"查询", 查询},    {"表", 表},     {"普通用户", 普通用户},
    {"管理员", 管理员}};
shell::shell() : User() {
  menuOutput::printPower();
}
shell::~shell() {}
bool shell::logn(std::string ID, std::string password) {
  return login(ID, password);
}
void shell::toChoose() {
  if (command.size() > 1 && data.size() > 0) {
    switch (command[1]) {
      case 数据库: {
        if (command.size() == 2 && data.size() == 1) {
          toChooseDatabase();
          return;
        }
        if (command.size() == 3 && command[2] == 表 && data.size() == 2) {
          toChooseDatabaseTable();
          return;
        }
        break;
      }
      case 表: {
        if (command.size() == 2 && data.size() == 1) {
          toChooseTable();
          return;
        }
        break;
      }
      default: {
        break;
      }
    }
  }
  menuOutput::printCommandError(ReturnPower());
  return;
}
void shell::toChooseDatabase() {
  switch (pwd.size()) {
    case 0: {
      menuOutput::printNotLogin();
    }
    case 1:
    case 2:
    case 3: {
      if (User::HaveDatabase(data[0])) {
        pwd.clear();
        pwd.push_back("/");
        pwd.push_back(data[0]);
      } else {
        menuOutput::printCommandError(ReturnPower());
      }
    }
    default: {
      break;
    }
  }
  return;
}
void shell::toChooseTable() {
  switch (pwd.size()) {
    case 0: {
      menuOutput::printNotLogin();
      return;
    }
    case 1: {
      menuOutput::printNotChooseDatabase(ReturnPower());
      return;
    }
    case 2:
    case 3: {
      if (User::DatabaseHaveTable(pwd[2], data[0])) {
        pwd.push_back(data[0]);
        return;
      } else {
        menuOutput::printDatabaseNotHaveTable(ReturnPower());
      }
      break;
    }
    default: {
      break;
    }
  }
  return;
}
void shell::toChooseDatabaseTable() {
  if (User::DatabaseHaveTable(data[0], data[1])) {
    pwd.clear();
    pwd.push_back("/");
    pwd.push_back(data[0]);
    pwd.push_back(data[1]);
  } else {
    menuOutput::printCommandError(ReturnPower());
  }
  return;
}
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
      if (!aidCheckData(tmp)) {
        return false;
      }
      data.push_back(tmp);
      break;
    }
  }
  for (++stap; stap < size; ++stap) {
    if (aidCheckData(vectorbuff[stap])) {
      data.push_back(vectorbuff[stap]);
    } else {
      return false;
    }
  }
}
bool shell::read(std::string str) {
  if (!check(str)) {
    menuOutput::printCommandError(ReturnPower());
    return false;
  }
  switch (command[0]) {
    case 选择:
      toChoose();
      break;
    case 退出:
      // if (vectorbuff.size() == 1) {
      //   menuOutput::printExit(ReturnPower());
      // } else {
      //   menuOutput::printCommandError(ReturnPower());
      // }
      // break;
    case 创建:
      // if (ReturnPower() < 2) {  // 管理员和超级管理员权限
      //   toCreate(vectorbuff);
      // } else {
      //   menuOutput::printPowerNoEnough(
      //       ReturnPower());  // 普通用户或未登录没有权限创建
      // }
      // break;
    case 删除:
      // if (ReturnPower() < 2) {
      //   toDelete(vectorbuff);
      // } else {
      //   menuOutput::printPowerNoEnough(ReturnPower());
      // }
      // break;
    case 重命名:
      // if (ReturnPower() < 2) {
      //   toRename(vectorbuff);
      // } else {
      //   menuOutput::printPowerNoEnough(ReturnPower());
      // }
      // break;
    case 登录:
      // if (vectorbuff.size() != 3) {
      //   menuOutput::printCommandError(ReturnPower());
      // } else {
      //   bool Login = this->login(vectorbuff[1], vectorbuff[2]);
      //   menuOutput::printLoginOrNot(Login);
      // }
      // break;
    case 插入:
      // if (ReturnLoginStatus() < 2) {
      //   toInsert(vectorbuff);
      // } else {
      //   menuOutput::printPowerNoEnough(ReturnPower());
      // }
      // break;
    case 查询:
      // toFind(vectorbuff);
      // break;
    case 显示:
      toShow();
      break;
    default:
      // menuOutput::printCommandError(ReturnPower());
      break;
  }
  return false;
}

void shell::toCreate() {
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
  //   switch (HashMapCID[value[1]]) {
  //     case 表:
  //       toCreateTable(value);
  //       break;
  //     case 数据库:
  //       toCreateDatabase(value);
  //       break;
  //     default:
  //       menuOutput::printCommandError(ReturnPower());
  //   }
}
void shell::toCreateTable() {}
void shell::toCreateDatabase() {}
void shell::toDelete() {
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
  //   switch (HashMapCID[value[1]]) {
  //     case 表:
  //       toDeleteTable(value);
  //       break;
  //     case 数据库:
  //       toDeleteDatabase(value);
  //       break;
  //     default:
  //       menuOutput::printCommandError(ReturnPower());
  //   }
}
void shell::toDeleteTable() {}
void shell::toDeleteDatabase() {}
void shell::toRename() {
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
  //   switch (HashMapCID[value[1]]) {
  //     case 数据库:
  //       toRenameTable(value);
  //       break;
  //     case 表:
  //       toRenameDatabase(value);
  //       break;
  //     default:
  //       menuOutput::printCommandError(ReturnPower());
  //       break;
  //   }
}
void shell::toRenameTable() {}
void shell::toRenameDatabase() {}
void shell::toInsert() {
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
}
void shell::toFind() {
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
}
void shell::toShow() {
  if(command.size() == 1 && data.size() == 0){
    menuOutput::printPWD(pwd,ReturnPower());
  }
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
}