/**
 * @file shell.cpp
 * @brief TMDSQL语句的设计与实现
 * @author TMD
 * @version 1.3
 * @date 2022-11-01
 */
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _VIEW_H_
#define _VIEW_H_
#include "view.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _INDEX_H_
#define _INDEX_H_
#include "Index.h"
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
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
shell::shell() : User(), commandCount(0), need(true) {
  menuOutput::printPower();
}
shell::~shell() {}
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
    }
  }
  menuOutput::printCommandError(ReturnPower());
  Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                   第二个关键字错误);
  return;
}
void shell::toChooseDatabase() {
  switch (pwd.size()) {
    case 1:
    case 2:
    case 3: {
      if (DataBase(data[0]).isExist()) {
        pwd.clear();
        pwd.push_back("/");
        pwd.push_back(data[0]);
        menuOutput::printChooseACK(ReturnPower(), need);
        Log::LogForSelectDatabase(ReturnUserName(), ReturnPower(), data[0]);
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         无法选择不存在的数据库);
        menuOutput::printNotExistsDatabase(ReturnPower(), need);
      }
    }
  }
  return;
}
void shell::toChooseTable() {
  switch (pwd.size()) {
    case 1: {
      menuOutput::printNotChooseDatabase(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       未选择数据库越级选择表);
      return;
    }
    case 2:
    case 3: {
      if (Table(pwd[1] + "/" + data[0], type::_TYPE_TABLE).isExist()) {
        pwd.push_back(data[0]);
        Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                       data[0]);
        menuOutput::printChooseACK(ReturnPower(), need);
        return;
      } else {
        Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                       data[0], 已选择的数据库中不存在目标表);
        menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
      }
      break;
    }
  }
  return;
}
void shell::toChooseDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 无法选择不存在的数据库);
    return;
  } else if (!Table(data[0] + "/" + data[1], type::_TYPE_TABLE).isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], 已选择的数据库中不存在目标表);
    return;
  }
  pwd.clear();
  pwd.push_back("/");
  pwd.push_back(data[0]);
  pwd.push_back(data[1]);
  Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                 data[1]);
  menuOutput::printChooseACK(ReturnPower(), need);
  return;
}
bool shell::aidCheckData(std::string _str) {
  for (char& ch : _str) {
    if (checkErrorName.count(ch)) {
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       键入违规字符);
      return false;
    }
  }
  return true;
}
bool shell::check(revstring vectorbuff) {
  command.clear();
  data.clear();
  int size = vectorbuff.size();
  if (size == 0 || !(HashMapStringToCID.count(vectorbuff[0]))) {
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     键入不存在的关键字);
    return false;
  }
  int stap = 0;
  for (; stap < size; ++stap) {
    if (HashMapStringToCID.count(vectorbuff[stap])) {
      command.push_back(HashMapStringToCID[vectorbuff[stap]]);
    } else {
      if (vectorbuff[stap][0] != '@') {
        Log::LogForCompileError(ReturnUserName(), ReturnPower(), vectorbuff,
                                键入违规字符);
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
  if (command.size() == 0) {
    menuOutput::printCommandError(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
  }
  if (!ReturnLoginStatus()) {
    if (command[0] != 退出 && command[0] != 登录 && command[0] != 执行) {
      menuOutput::printNotLogin(need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       未登录拒绝执行);
      return true;
    }
  }
  switch (command[0]) {
    case 选择:
      if ((command.size() == 2 || command.size() == 3) &&
          (data.size() == 1 || data.size() == 2)) {
        toChoose();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      break;
    case 退出:
      if (command.size() == 1 && data.size() == 0) {
        menuOutput::printExit(ReturnPower(), need);
        Log::LogForExit(ReturnUserName(), ReturnPower());
        exitLogin();
        return false;
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      break;
    case 创建:
      if (ReturnPower() < 2) {  // 管理员和超级管理员权限
        toCreate();
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         普通用户违规操作);
        menuOutput::printPowerNoEnough(ReturnPower(),
                                       need);  // 普通用户或未登录没有权限创建
      }
      break;
    case 删除:
      if (ReturnPower() < 2) {
        toDelete();
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         普通用户违规操作);
        menuOutput::printPowerNoEnough(ReturnPower(), need);
      }
      break;
    case 登录: {
      if (command.size() != 1) {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        break;
      }
      if (data.size() == 2) {
        std::string oldUserName = ReturnUserName();
        TYPE_POWER oldUserPower = ReturnPower();
        if (this->login(data[0], data[1])) {
          if (pwd.size() == 0) {
            pwd.push_back("/");
          }
          Log::LogForLogin(oldUserName, oldUserPower, data[0], data[1]);
        } else {
          switch (returnErrorCase()) {
            case 密码错误:
              Log::LogForLogin(oldUserName, oldUserPower, data[0], data[1],
                               登录密码错误);
              break;
            case 帐号不存在:
              Log::LogForLogin(oldUserName, oldUserPower, data[0], data[1],
                               登录帐号错误);
              break;
          }
        }
        menuOutput::printLoginOrNot(this->ReturnLoginStatus(),
                                    returnErrorCase(), ReturnPower(),
                                    ReturnUserName(), need);
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        menuOutput::printCommandError(ReturnPower(), need);
      }
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
      if (data.size() == 1 && command.size() == 1) {
        toExecute();
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        menuOutput::printCommandError(ReturnPower(), need);
      }
      break;
    case 设置:
      if (ReturnPower() >= 2) {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         普通用户违规操作);
      }
      toSet();
      break;
    default:
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第一个关键字错误);
      menuOutput::printCommandError(ReturnPower(), need);
      break;
  };
  return true;
}
bool shell::read(std::string str) {
  if (!check(str)) {
    menuOutput::printCommandError(ReturnPower(),
                                  need);  // 不需要Log，在check中已经log输出了
    return true;
  }
  return read();
}
bool shell::read(revstring value) {
  if (!check(value)) {
    menuOutput::printCommandError(ReturnPower(),
                                  need);  // 不需要Log，在check中已经log输出了
    return true;
  }
  return read();
}
void shell::toExecute() {
  _file file(_SQLPath + data[0]);
  if (!file.isExist()) {
    menuOutput::printNotFindSQL(ReturnPower());
    Log::LogForExecuteSQL(ReturnUserName(), ReturnPower(), data[0],
                          SQL文件未找到);
    return;
  }
  vstring tmp;
  command.clear();
  data.clear();
  this->need = false;
  Log::LogForExecuteSQL(ReturnUserName(), ReturnPower(), data[0]);
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
  if (command.size() > 3 || data.size() == 0 || data.size() > 2) {
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
    menuOutput::printCommandError(ReturnPower(), need);
    return;
  }
  switch (command[1]) {
    case 数据库:
      if (command.size() == 2 && data.size() == 1) {
        toCreateDatabase();
        return;
      }
      if (command.size() == 3 && data.size() == 2 && command[2] == 表) {
        toCreateDatabaseTable();
        return;
      }
      break;
    case 表:
      if (command.size() != 2 || data.size() != 1) {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        menuOutput::printCommandError(ReturnPower(), need);
        return;
      }
      if (pwd.size() < 2) {
        menuOutput::printNotChooseDatabase(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         未选择数据库越级选择表);
        return;
      }
      toCreateTable();
      return;
    case 用户:
      if (command.size() == 2 && data.size() == 2) {
        if (!addNormalUser(data[0], data[1])) {
          menuOutput::printUserExists(ReturnPower(), need);
          Log::LogForCreateUser(ReturnUserName(), ReturnPower(), data[0],
                                data[1], 创建已存在的用户);
        } else {
          menuOutput::printCreateACK(ReturnPower(), need);
          Log::LogForCreateUser(ReturnUserName(), ReturnPower(), data[0],
                                data[1]);
        }
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        menuOutput::printCommandError(ReturnPower(), need);
      }
      break;
    case 管理员:
      if (ReturnPower()) {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         管理员违规操作);
      }
      if (command.size() == 2 && data.size() == 2) {
        if (!addManagerUser(data[0], data[1])) {
          menuOutput::printManagerExists(ReturnPower(), need);
          Log::LogForCreateManager(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 创建已存在的管理员);
        } else {
          menuOutput::printCreateACK(ReturnPower(), need);
          Log::LogForCreateManager(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
        }
      }
      {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
        menuOutput::printCommandError(ReturnPower(), need);
      }
      break;
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
      break;
  }
}
void shell::toCreateTable() {
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (table.isExist()) {
    menuOutput::printTableIsExists(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], 表已存在无法创建);
  } else {
    table.create();
    menuOutput::printCreateACK(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
  }
}
void shell::toCreateDatabase() {
  DataBase database(data[0]);
  if (database.isExist()) {
    menuOutput::printDatabaseIsExists(ReturnPower(), need);
    Log::LogForCreateDatabase(ReturnUserName(), ReturnPower(), data[0],
                              数据库已存在无法创建);
  } else {
    database.create();
    menuOutput::printCreateACK(ReturnPower(), need);
    Log::LogForCreateDatabase(ReturnUserName(), ReturnPower(), data[0]);
  }
}
void shell::toCreateDatabaseTable() {
  DataBase database(data[0]);
  if (!database.isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForCreateDatabase(ReturnUserName(), ReturnPower(), data[0],
                              无法选择不存在的数据库);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (table.isExist()) {
    menuOutput::printTableIsExists(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 表已存在无法创建);
  } else {
    table.create();
    menuOutput::printCreateACK(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
  }
}
void shell::toDelete() {
  switch (command[1]) {
    case 数据库: {
      if (command.size() == 3 && command[2] == 表 && data.size() == 2) {
        toDeleteDatabaseTable();
        return;
      } else if (command.size() == 2 && data.size() == 1) {
        toDeleteDatabase();
        return;
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
    case 表:
      if (command.size() == 2 && data.size() == 1) {
        toDeleteTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    case 用户:
      if (command.size() == 2 && data.size() == 1) {
        toDeleteUser();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    case 管理员:
      if (command.size() == 2 && data.size() == 1) {
        toDeleteManager();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
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
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], 未选择数据库越级选择表);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], 表不存在无法删除);
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  } else if (!TablePCB(table).returnEndLineIndex()) {
    table.remove();
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table, 5, false);
  if (inputACK()) {
    table.remove();
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], 输入非确定指令取消);
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 数据库不存在无法删除);
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 表不存在无法删除);

    return;
  } else if (!TablePCB(table).returnEndLineIndex()) {
    table.remove();
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table, 5, false);
  if (inputACK()) {
    table.remove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
    return;
  } else {
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 输入非确定指令取消);
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteDatabase() {
  DataBase database(data[0]);
  if (!database.isExist()) {
    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0],
                              数据库不存在无法删除);
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    return;
  }
  if (database.remove()) {
    menuOutput::printDeleteACK(ReturnPower(), need);

    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0]);
    return;
  } else {
    menuOutput::printDatabaseNotEmptyAndDeleteTip(ReturnPower(), false);
  }
  menuOutput::printShowDatabase(ReturnPower(), database, false);
  if (inputACK()) {
    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0]);
    database.forceremove();
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  } else {
    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0],
                              输入非确定指令取消);
    menuOutput::printCommandBackout(ReturnPower(), need);
    return;
  }
}
void shell::toDeleteManager() {
  if (ReturnPower() != ROOT) {
    menuOutput::printPowerNoEnough(ReturnPower(), need);
    Log::LogForDeleteManager(ReturnUserName(), ReturnPower(), data[0],
                             管理员违规操作);
    return;
  }
  if (!deleteUser(data[0])) {
    Log::LogForDeleteManager(ReturnUserName(), ReturnPower(), data[0],
                             目标管理员不存在无法删除);
    menuOutput::printManagerNotExists(ReturnPower(), need);
    return;
  }
  menuOutput::printDeleteACK(ReturnPower(), need);
  Log::LogForDeleteManager(ReturnUserName(), ReturnPower(), data[0]);
}
void shell::toDeleteUser() {
  if (!deleteUser(data[0])) {
    Log::LogForDeleteUser(ReturnUserName(), ReturnPower(), data[0],
                          目标用户不存在无法删除);
    menuOutput::printUserNotExists(ReturnPower(), need);
    return;
  }
  Log::LogForDeleteUser(ReturnUserName(), ReturnPower(), data[0]);
  menuOutput::printDeleteACK(ReturnPower(), need);
}
void shell::toInsert() {
  switch (command.size()) {
    case 1: {
      if (data.size() == 1) {
        toInsertDefaultTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
    case 2: {
      if (data.size() > 1 && command[1] == 表) {
        toInsertTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
    case 3: {
      if (data.size() > 2 && command[1] == 数据库 && command[2] == 表) {
        toInsertDatabaseTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
      break;
  }
}
void shell::toInsertDatabaseTable() {
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  vstring tmp(data.begin() + 2, data.end());
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], tmp, 数据库不存在无法插入数据);
    return;
  }
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], tmp, 表不存在无法插入数据);
    return;
  }
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);

  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                 data[1], tmp);
}
void shell::toInsertDefaultTable() {  // 当选择到表的时候，说明数据库+表都存在
  Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
  table.append(data);
  menuOutput::printInsertACK(ReturnPower(), need);
  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 pwd[2], data);
}
void shell::toInsertTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
    return;
  }
  vstring tmp(data.begin() + 1, data.end());
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], tmp, 表不存在无法插入数据);
    menuOutput::printNotExistsTable(ReturnPower(), need);
    return;
  }
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);
  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 data[0], tmp);
}
void shell::toFind() {
  switch (command.size()) {
    case 1:
      if (data.size() == 1) {
        toFindDefalutTable();
        return;
      }
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
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
      menuOutput::printCommandError(ReturnPower(), need);
      return;
  }

  Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
  menuOutput::printCommandError(ReturnPower(), need);
  return;
}
void shell::toFindTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
    return;
  }
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 data[0], data[1], 表不存在无法查找数据);
    return;
  }
  menuOutput::printShowFindTable(ReturnPower(), ReturnUserName(), table,
                                 data[1], need);
  Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1], data[0],
                               data[1]);
}
void shell::toFindDefalutTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
    return;
  }
  if (pwd.size() == 2) {
    menuOutput::printNotChooseTable(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 未选择表);
  }
  Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 pwd[2], data[0], 表不存在无法查找数据);
    return;
  }
  menuOutput::printShowFindTable(ReturnPower(), ReturnUserName(), table,
                                 data[0], need);
  Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1], pwd[2],
                               data[0]);
}
void shell::toFindDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 data[0], data[1], 数据库不存在无法查找数据);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 data[0], data[1], 表不存在无法查找数据);
    return;
  }
  menuOutput::printShowFindTable(ReturnPower(), ReturnUserName(), table,
                                 data[2], need);
  Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1], data[0],
                               data[1]);
}
void shell::toShow() {
  switch (command.size()) {
    case 1: {
      if (data.size() == 0) {
        menuOutput::printPWD(pwd, ReturnPower(), need);
        Log::LogForShow(ReturnUserName(), ReturnPower());
      } else {
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      break;
    }
    case 2: {
      switch (command[1]) {
        case 数据库:
          if (data.size() == 0 || data.size() == 1) {
            toShowDatabase();
          } else {
            menuOutput::printCommandError(ReturnPower(), need);
            Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                             编译错误);
          }
          break;
        case 表:
          if (data.size() == 2 || data.size() == 3) {
            toShowTable();
          } else {
            menuOutput::printCommandError(ReturnPower(), need);
            Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                             编译错误);
          }
          break;
        default:
          menuOutput::printCommandError(ReturnPower(), need);
          Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                           第二个关键字错误);
          break;
      }
      break;
    }
    case 3: {
      if (data.size() == 3 && command[1] == 数据库 && command[2] == 表) {
        toShowDatabaseTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      break;
    }
    default:
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
      break;
  }
}
void shell::toShowDatabase() {
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
  }
}
void shell::toShowTable() {
  if (pwd.size() <= 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
    return;
  }
  switch (data.size()) {
    case 1: {
      if (pwd.size() == 2) {
        menuOutput::printNotChooseTable(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         未选择表);
        return;
      }
      Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
      if (!table.isExist()) {
        menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
        Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                     pwd[2], 表不存在无法显示数据);
        return;
      }
      menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table,
                                 _super::stringToInt(data[0]), need);
      Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   pwd[2]);
      return;
    }
    case 2: {
      Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
      if (!table.isExist()) {
        menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
        Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                     data[0], 表不存在无法显示数据);
        return;
      }
      menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table,
                                 _super::stringToInt(data[1]), need);
      Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
      return;
    }
  }
}
void shell::toShowDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                 data[1], 数据库不存在无法显示数据);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                 data[1], 表不存在无法显示数据);
    return;
  }
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table,
                             _super::stringToInt(data[2]), need);
  Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                               data[1]);
}
void shell::toSet() {
  if (command.size() < 2 || data.size() == 0) {
    menuOutput::printCommandError(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
  }
  switch (command[1]) {
    case 索引:
      toSetIndex();
      return;
    case 视图: {
      toSetView();
      return;
    }
    default: {
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
      break;
    }
  }
}
void shell::toSetIndex() {
  if (command.size() == 2 && data.size() == 1) {
    toSetIndexDefault();
    return;
  } else if (command.size() > 2) {
    switch (command[2]) {
      case 数据库:
        if (command.size() == 4 && data.size() == 3 && command[3] == 表) {
          toSetIndexDatabaseTable();
          return;
        }
        break;
      case 表:
        if (command.size() == 3 && data.size() == 2) {
          toSetIndexTable();
          return;
        }
        break;
      default:
        break;
    }
    menuOutput::printCommandError(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
  }
}
void shell::toSetIndexDatabaseTable() {
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                     data[1], data[2], 无法选择不存在的数据库);
    return;
  }
  if (!Table(data[0] + "/" + data[1], type::_TYPE_TABLE).isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                     data[1], data[2],
                                     已选择的数据库中不存在目标表);
    return;
  }
  TablePCB::setIndex(data[0] + "/" + data[1], INDEX(atoi(data[2].c_str())));
  Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], data[2]);
  menuOutput::printSetACK(ReturnPower(), need);
  Index::update(data[0] + "/" + data[1]);
}
void shell::toSetIndexTable() {
  if (!Table(pwd[1] + "/" + data[0], type::_TYPE_TABLE).isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                     data[0], data[1],
                                     已选择的数据库中不存在目标表);
    return;
  }
  TablePCB::setIndex(pwd[1] + "/" + data[0], INDEX(atoi(data[1].c_str())));
  Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], data[1]);
  menuOutput::printSetACK(ReturnPower(), need);
  Index::update(pwd[1] + "/" + data[0]);
}
void shell::toSetIndexDefault() {
  TablePCB::setIndex(pwd[1] + "/" + pwd[2], INDEX(atoi(data[0].c_str())));
  Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   pwd[2], data[0]);
  menuOutput::printSetACK(ReturnPower(), need);
  Index::update(pwd[1] + "/" + pwd[2]);
}
void shell::toSetView() {
  if (command.size() == 2 && data.size() >= 1) {
    toSetViewDefault();
    return;
  } else if (command.size() > 2 && data.size() >= 3) {
    switch (command[2]) {
      case 数据库:
        if (data.size() >= 4 && command.size() == 4 && command[3] == 表) {
          toSetViewDatabaseTable();
          return;
        }
        break;
      case 表:
        if (data.size() >= 3 && command.size() == 3) {
          toSetViewTable();
          return;
        }
        break;
      default:
        break;
    }
  }
  menuOutput::printCommandError(ReturnPower(), need);
  Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
}
void shell::toSetViewDatabaseTable() {
  vstring allowCol(data.begin() + 3, data.end());
  if (!DataBase(data[0]).isExist()) {
    menuOutput::printNotExistsDatabase(ReturnPower(), need);
    Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                    data[1], data[2], allowCol,
                                    无法选择不存在的数据库);
    return;
  }
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                    data[1], data[2], allowCol,
                                    已选择的数据库中不存在目标表);
    return;
  }
  View::setAllowShowColumn(data[2], allowCol, data[0], data[1]);
  Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                  data[1], data[2], allowCol);
  menuOutput::printSetACK(ReturnPower(), need);
}
void shell::toSetViewTable() {
  vstring allowCol(data.begin() + 2, data.end());
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                    data[0], data[1], allowCol,
                                    已选择的数据库中不存在目标表);
    return;
  }
  View::setAllowShowColumn(data[1], allowCol, pwd[1], data[0]);
  Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                  data[0], data[1], allowCol);
  menuOutput::printSetACK(ReturnPower(), need);
}
void shell::toSetViewDefault() {
  vstring allowCol(data.begin() + 1, data.end());
  Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
  View::setAllowShowColumn(data[0], allowCol, pwd[1], pwd[2]);
  Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                  pwd[2], data[0], allowCol);
  menuOutput::printSetACK(ReturnPower(), need);
}
