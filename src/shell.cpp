/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2023-01-01 17:07:08
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
std::unordered_map<std::string, TYPE_CID> shell::HashMapCID = {
    {"退出", 退出},     {"创建", 创建},     {"数据库", 数据库}, {"删除", 删除},
    {"选择", 选择},     {"重命名", 重命名}, {"登录", 登录},     {"显示", 显示},
    {"插入", 插入},     {"查询", 查询},     {"表", 表},         {"用户", 用户},
    {"管理员", 管理员}, {"执行", 执行}};
shell::shell() : User(), commandCount(0), need(true) {
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
      menuOutput::printNotLogin(need);
    }
    case 1:
    case 2:
    case 3: {
      if (User::HaveDatabase(data[0])) {
        pwd.clear();
        pwd.push_back("/");
        pwd.push_back(data[0]);
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
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
      menuOutput::printNotLogin(need);
      return;
    }
    case 1: {
      menuOutput::printNotChooseDatabase(ReturnPower(), need);
      return;
    }
    case 2:
    case 3: {
      if (User::DatabaseHaveTable(pwd[1], data[0])) {
        pwd.push_back(data[0]);
        return;
      } else {
        menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
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
    menuOutput::printCommandError(ReturnPower(), need);
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
bool shell::check(revstring vectorbuff) {
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
  return true;
}
bool shell::check(std::string _str) {
  vstring vectorbuff;
  _super::stringToVector(_str, vectorbuff);
  return check(vectorbuff);
}

void shell::read() {
  ++commandCount;
  switch (command[0]) {
    case 选择:
      toChoose();
      break;
    case 退出:
      exitLogin();
      menuOutput::printExit(ReturnPower(), need);
      break;
    case 创建:
      if (ReturnPower() < 2) {  // 管理员和超级管理员权限
        toCreate();
      } else {
        menuOutput::printPowerNoEnough(
            ReturnPower());  // 普通用户或未登录没有权限创建
      }
      break;
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
    case 登录: {
      bool Login = false;
      if (data.size() == 2) {
        Login = this->login(data[0], data[1]);
        if (pwd.size() == 0) {
          pwd.push_back("/");
        }
      }
      menuOutput::printLoginOrNot(Login, ReturnPower(), ReturnUserName(), need);
      break;
    }
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
    case 执行:
      toExecute();
      break;
    default:
      // menuOutput::printCommandError(ReturnPower());
      break;
  }
  command.clear();
  data.clear();
}
void shell::read(std::string str) {
  if (!check(str)) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  read();
}
void shell::read(revstring value) {
  if (!check(value)) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  read();
}
void shell::toExecute() {
  _file file("../data/SQL/" + data[0]);
  if (!file.isExist()) {
    menuOutput::printNotFindSQL(ReturnPower());
    return;
  }
  vstring tmp;
  command.clear();
  data.clear();
  this->need = false;
  while (file.readline(tmp)) {
    if (!tmp.size()) {
      return;
    }
    read(tmp);
  }
  this->need = true;
  menuOutput::printPower(ReturnPower());
}
void shell::toCreate() {
  if (command.size() == 0 || command.size() > 2 || data.size() == 0 ||
      data.size() > 2) {
    menuOutput::printCommandError(ReturnPower(), need);
  }
  switch (command[1]) {
    case 数据库:
      if (command.size() == 2 && data.size() == 1) {
        toCreateDatabase();
      }
      break;
    case 表:
      if (command.size() == 2 && data.size() == 1) {
        toCreateTable();
      }
      break;
    case 用户:
      if (command.size() == 2 && data.size() == 2) {
        toCreateUser();
      }
      break;
    case 管理员:
      if (ReturnPower()) {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
      }
      if (command.size() == 2 && data.size() == 2) {
        toCreateManager();
      }
      break;
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  }
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
  //
  //   }
}
void shell::toCreateTable() {
  Table table(data[0], type::_TYPE_TABLE);
  if (table.isExist()) {
    menuOutput::printTableIsExists(ReturnPower(), need);
  } else {
    table.create();
  }
}
void shell::toCreateDatabase() {
  DataBase database(data[0]);
  if (database.isExist()) {
    menuOutput::printDatabaseIsExists(ReturnPower(), need);
  } else {
    database.create();
  }
}
void shell::toCreateManager() {
  User tmp;
  tmp.addNormalUser(data[0], data[1]);
}
void shell::toCreateUser() {
  User tmp;
  tmp.addNormalUser(data[0], data[1]);
}
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
  if (command.size() == 1 && data.size() == 0) {
    menuOutput::printPWD(pwd, ReturnPower(), need);
  }
  //   if (!HashMapCID.count(value[1])) {
  //     menuOutput::printCommandError(ReturnPower());
  //   }
}