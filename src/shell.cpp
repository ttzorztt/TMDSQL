/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2023-01-11 21:32:34
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
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif

#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
std::unordered_map<std::string, TYPE_CID> shell::HashMapCID = {
    {"退出", 退出}, {"创建", 创建}, {"数据库", 数据库}, {"删除", 删除},
    {"选择", 选择}, {"登录", 登录}, {"显示", 显示},     {"插入", 插入},
    {"查询", 查询}, {"表", 表},     {"用户", 用户},     {"管理员", 管理员},
    {"执行", 执行}};
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
      if (DataBase(data[0]).isExist()) {
        pwd.clear();
        pwd.push_back("/");
        pwd.push_back(data[0]);
        menuOutput::printPower(ReturnPower(), need);
      } else {
        menuOutput::printNotExistsDatabase(ReturnPower(), need);
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
      if (Table(pwd[1] + "/" + data[0], type::_TYPE_TABLE).isExist()) {
        pwd.push_back(data[0]);
        menuOutput::printPower(ReturnPower(), need);
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
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  } else if (!Table(data[0] + "/" + data[1], type::_TYPE_TABLE).isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    return;
  }
  if (Table(data[0] + "/" + data[1], type::_TYPE_TABLE).isExist()) {
    pwd.clear();
    pwd.push_back("/");
    pwd.push_back(data[0]);
    pwd.push_back(data[1]);
    menuOutput::printPower(ReturnPower(), need);
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
  command.clear();
  data.clear();
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

bool shell::read() {
  ++commandCount;
  switch (command[0]) {
    case 选择:
      toChoose();
      break;
    case 退出:
      exitLogin();
      menuOutput::printExit(ReturnPower(), need);
      return false;
    case 创建:
      if (ReturnPower() < 2) {  // 管理员和超级管理员权限
        toCreate();
      } else {
        menuOutput::printPowerNoEnough(ReturnPower(),
                                       need);  // 普通用户或未登录没有权限创建
      }
      break;
    case 删除:
      if (ReturnPower() < 2) {
        toDelete();
      } else {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
      }
      break;
    case 登录: {
      if (data.size() == 2) {
        this->login(data[0], data[1]);
        if (pwd.size() == 0) {
          pwd.push_back("/");
        }
      }
      menuOutput::printLoginOrNot(this->ReturnLoginStatus(), returnErrorCase(),
                                  ReturnPower(), ReturnUserName(), need);
      break;
    }
    case 插入: {
      toInsert();
      break;
    }
    case 查询:
      toFind();
      break;
    case 显示:
      toShow();
      break;
    case 执行:
      toExecute();
      break;
    default:

      menuOutput::printCommandError(ReturnPower(), need);
      break;
  };
  return true;
}
bool shell::read(std::string str) {
  if (!check(str)) {
    menuOutput::printCommandError(ReturnPower(), need);
    return true;
  }
  return read();
}
bool shell::read(revstring value) {
  if (!check(value)) {
    menuOutput::printCommandError(ReturnPower(), need);
    return true;
  }
  return read();
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
        return;
      }
      break;
    case 表:
      if (pwd.size() < 2) {
        menuOutput::printNotChooseDatabase(ReturnPower(), need);
        return;
      }
      if (command.size() == 2 && data.size() == 1) {
        toCreateTable();
        return;
      }
      break;
    case 用户:
      if (command.size() == 2 && data.size() == 2) {
        if (!addNormalUser(data[0], data[1])) {
          menuOutput::printUserExists(ReturnPower(), need);
        } else {
          menuOutput::printCreateACK(ReturnPower(), need);
        }
      }
      break;
    case 管理员:
      if (ReturnPower()) {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
      }
      if (command.size() == 2 && data.size() == 2) {
        if (!addManagerUser(data[0], data[1])) {
          menuOutput::printManagerExists(ReturnPower(), need);
        } else {
          menuOutput::printCreateACK(ReturnPower(), need);
        }
      }
      break;
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  }
}
void shell::toCreateTable() {
  if (!DataBase(pwd[1]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (table.isExist()) {
    menuOutput::printTableIsExists(ReturnPower(), need);
  } else {
    table.create();
    menuOutput::printCreateACK(ReturnPower(), need);
  }
}
void shell::toCreateDatabase() {
  DataBase database(data[0]);
  if (database.isExist()) {
    menuOutput::printDatabaseIsExists(ReturnPower(), need);
  } else {
    database.create();
    menuOutput::printCreateACK(ReturnPower(), need);
  }
}
void shell::toDelete() {
  if (command.size() == 1 || data.size() == 0 || data.size() > 3) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  switch (command[1]) {
    case 数据库:
      if (command.size() == 3 && command[2] == 表) {
        toDeleteDatabaseTable();
        return;
      }
      toDeleteDatabase();
      return;
    case 表:
      toDeleteTable();
      return;
    case 用户:
      toDeleteUser();
      return;
    case 管理员:
      toDeleteManager();
      return;
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  }
}
bool shell::inputACK() {
  std::string tmp;
  std::cout << "如果您仍然执意删除，请键入 \"确定\" :";
  while (1) {
    std::getline(std::cin, tmp);
    if (tmp == "") {
      return false;
    } else {
      return (tmp == "确定");
    }
  }
}
void shell::toDeleteTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  } else if (!TablePCB(table).returnEndLineIndex()) {
    table.remove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), table, 5, false);
  if (inputACK()) {
    table.remove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteDatabaseTable() {
  if (data.size() != 2) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  } else if (!TablePCB(table).returnEndLineIndex()) {
    table.remove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), table, 5, false);
  if (inputACK()) {
    table.remove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteDatabase() {
  if (data.size() != 1) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  DataBase database(data[0]);
  if (!database.isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  if (database.remove()) {
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    menuOutput::printDatabaseNotEmptyAndDeleteTip(ReturnPower(), false);
  }
  menuOutput::printShowDatabase(ReturnPower(), database, false);
  if (inputACK()) {
    database.forceremove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteManager() {
  if (data.size() != 1) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  if (ReturnPower() != ROOT) {
    menuOutput::printPowerNoEnough(ReturnPower(), need);
    return;
  }
  if (!deleteUser(data[0])) {
    menuOutput::printManagerNotExists(ReturnPower(), need);
    return;
  }
  menuOutput::printDeleteACK(ReturnPower(), need);
}
void shell::toDeleteUser() {
  if (data.size() != 1) {
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  if (!deleteUser(data[0])) {
    menuOutput::printUserNotExists(ReturnPower(), need);
    return;
  }
  menuOutput::printDeleteACK(ReturnPower(), need);
}
void shell::toInsert() {
  switch (command.size()) {
    case 2: {
      if (command[1] != 表 || data.size() == 0) {
        menuOutput::printCommandError(ReturnPower(), need);
        return;
      }
      if (data.size() == 1) {
        menuOutput::printInsertNoValue(ReturnPower(), need);
        return;
      }
      toInsertTable();
      break;
    }
    case 3: {
      if (command[1] != 数据库 || command[2] != 表 || data.size() < 2) {
        menuOutput::printCommandError(ReturnPower(), need);
        return;
      }
      if (data.size() == 2) {
        menuOutput::printInsertNoValue(ReturnPower(), need);
        return;
      }
      toInsertDatabaseTable();
      break;
    }
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  }
}
void shell::toInsertDatabaseTable() {
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    return;
  }
  vstring tmp(data.begin() + 2, data.end());
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);
}
void shell::toInsertTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  }
  vstring tmp(data.begin() + 1, data.end());
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);
}
void shell::toFind() {
  switch (command.size()) {
    case 2:
      if (command[1] == 表 && data.size() == 2) {
        toFindTable();
        return;
      }
      break;
    case 3:
      if (command[1] == 数据库 && command[2] == 表 && data.size() == 3) {
        toFindDatabaseTable();
        return;
      }
      break;
    default:
      break;
  }
  menuOutput::printCommandError(ReturnPower(), need);
}
void shell::toFindTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  }
  menuOutput::printShowFindTable(ReturnPower(), table.find(data[1]), need);
}
void shell::toFindDatabaseTable() {
  if(!DataBase(data[0]).isExist()){
    menuOutput::printNotExistsDatabase(ReturnPower(),need);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  }
  menuOutput::printShowFindTable(ReturnPower(), table.find(data[2]), need);
}
void shell::toShow() {
  switch (command.size()) {
    case 1: {
      if (data.size() == 0) {
        menuOutput::printPWD(pwd, ReturnPower(), need);
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
      }
      break;
    }
    case 2: {
      switch (command[1]) {
        case 数据库:
          toShowDatabase();
          break;
        case 表:
          toShowTable();
          break;
        default:
          menuOutput::printCommandError(ReturnPower(), need);
          break;
      }
      break;
    }
    case 3: {
      toShowDatabaseTable();
      break;
    }
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  }
}
void shell::toShowDatabase() {
  switch (command.size()) {
    case 2: {
      switch (data.size()) {
        case 0: {
          menuOutput::printShowDatabase(ReturnPower(), need);
          return;
        }
        case 1: {
          DataBase database(data[0]);
          menuOutput::printShowDatabase(ReturnPower(), database, need);
          return;
        }
        default:
          menuOutput::printCommandError(ReturnPower(), need);
          return;
      }
      break;
    }
    case 3: {
      if (command[2] != 表) {
        menuOutput::printCommandError(ReturnPower(), need);
        return;
      }
      toShowDatabaseTable();
      break;
    }
    default: {
      menuOutput::printCommandError(ReturnPower(), need);
    }
  }
}
void shell::toShowTable() {
  if (pwd.size() <= 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    return;
  }
  switch (data.size()) {
    case 1: {
      menuOutput::printShowTable(ReturnPower(), table, 5, need);
      return;
    } break;
    case 2: {
      menuOutput::printShowTable(ReturnPower(), table,
                                 _super::stringToInt(data[1]), need);
      return;
    }
    default: {
      menuOutput::printCommandError(ReturnPower(), need);
      return;
    }
  }
}
void shell::toShowDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    return;
  }
  switch (data.size()) {
    case 2:
      menuOutput::printShowTable(ReturnPower(), table, 5, need);
      return;
    case 3:
      menuOutput::printShowTable(ReturnPower(), table,
                                 _super::stringToInt(data[2]), need);
      return;
    default:
      break;
  }
}