/**
 * @file shell.cpp
 * @brief TMDSQL语句的设计与实现
 * @author TMD
 * @date 2022-11-01
 */
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _string_
#define _string_
#include <string>
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
#ifndef _CACHE_H_
#define _CACHE_H_
#include "cache.h"
#endif
#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_
#include "BackTracking.h"
#endif
shell::shell() : User(), commandCount(0), need(true) {
  Cache();
  menuOutput::printPower();
  this->historyIndex = 0;
}
shell::~shell() {}
void shell::toChoose() {
  if (command.size() > 1 && data.size() > 0) {
    switch ((int)command[1]) {
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
        std::vector<std::string>().swap(pwd);
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
  /* 选择表会触发Cacheadd */
  switch (pwd.size()) {
    case 1: {
      menuOutput::printNotChooseDatabase(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       未选择数据库越级选择表);
      return;
    }
    case 2:
    case 3: {
      Table tmpTable(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
      if (tmpTable.isExist()) {
        pwd.push_back(data[0]);
        Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                       data[0]);
        menuOutput::printChooseACK(ReturnPower(), need);
        Cache::add(tmpTable);
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
    Log::LogForSelectDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 已选择的数据库中不存在目标表);
    return;
  }
  std::vector<std::string>().swap(pwd);
  pwd.push_back("/");
  pwd.push_back(data[0]);
  pwd.push_back(data[1]);
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  Cache::add(table);
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
  std::vector<TYPE_CID>().swap(command);
  std::vector<std::string>().swap(data);
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
      toLogin();
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
      } else {
        toSet();
      }
      break;
    case 回溯:
      if (ReturnPower() >= 2) {
        menuOutput::printPowerNoEnough(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         普通用户违规操作);
      }
      toBack();
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
void shell::toBack() {
  if (command.size() == 2 && data.size() == 0) {
    if (command[1] == 显示) {
      menuOutput::openDirPrintFile(ReturnPower(), "./data/Back/");
    } else if (command[1] == 清理) {
      toBackClear();
    } else {
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
    }
  } else if (command.size() == 2 && data.size() == 1) {
    if (command[1] == 显示) {
      toBackShowFile();
    } else {
      menuOutput::printCommandError(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       第二个关键字错误);
    }
  } else if (command.size() == 1 && data.size() == 2) {
    toBackFileExecute();
  } else {
    menuOutput::printCommandError(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
  }
}
void shell::toBackShowFile() {
  _file backTrackingFile(data[0], type::_TYPE_BACK);
  if (!backTrackingFile.isExist()) {
    return;
  }
  BackTracking::BackTrackingForShow(data[0]);
  menuOutput::printPower(ReturnPower(), need);
}
void shell::toBackFileExecute() {
  _file backTrackingFile(data[0], type::_TYPE_BACK);
  if (!backTrackingFile.isExist()) {
    return;
  }
  BackTracking::BackTrackingForExecute(data[0], std::atoi(data[1].c_str()));
  menuOutput::printBackTrackingACK(ReturnPower(), true);
}
void shell::toBackClear() {
  BackTracking::Clear();
  menuOutput::printBackTrackingClearACK(ReturnPower(), true);
}
void shell::toLogin() {
  if (data.size() == 2) {
    std::string oldUserName = ReturnUserName();
    TYPE_POWER oldUserPower = ReturnPower();
    if (this->login(data[0], data[1])) {
      if (pwd.size() == 0) {
        pwd.push_back("/");
      }
      Log::LogForLogin(oldUserName, oldUserPower, data[0], data[1]);
    menuOutput::printLoginOrNot(this->ReturnLoginStatus(), returnErrorCase(),
                                ReturnPower(), ReturnUserName(), need);
		return;
    } else {
      switch ((int)returnErrorCase()) {
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
    menuOutput::printLoginOrNot(false, returnErrorCase(),
                                ReturnPower(), ReturnUserName(), need);
  } else {
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
    menuOutput::printCommandError(ReturnPower(), need);
  }
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
  this->need = false;
  Log::LogForExecuteSQL(ReturnUserName(), ReturnPower(), data[0]);
  std::vector<std::string>().swap(data);
  std::vector<TYPE_CID>().swap(command);
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
          BackTracking::BackTrackingForDeleteUser(data[0]);
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
        return;
      }
      if (command.size() == 2 && data.size() == 2) {
        if (!addManagerUser(data[0], data[1])) {
          menuOutput::printManagerExists(ReturnPower(), need);
          Log::LogForCreateManager(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], 创建已存在的管理员);
        } else {
          BackTracking::BackTrackingForDeleteManager(data[0]);
          menuOutput::printCreateACK(ReturnPower(), need);
          Log::LogForCreateManager(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
        }
      } else {
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
    Cache::add(table);
    menuOutput::printCreateACK(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
    BackTracking::BackTrackingForDeleteDatabaseTable(pwd[1], data[0]);
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
    BackTracking::BackTrackingForDeleteDatabase(data[0]);
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
    Cache::add(table);
    menuOutput::printCreateACK(ReturnPower(), need);
    Log::LogForCreateDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
    BackTracking::BackTrackingForDeleteDatabaseTable(data[0], data[1]);
  }
}
void shell::toDelete() {
  switch (command[1]) {
    case 列: {
      if (command.size() == 2 &&
          data.size() == 1) {  // 删除_列(pwd默认选择到表)
        toDeleteCol();
      } else if (command.size() == 3 &&
                 data.size() == 2) {  //删除_列_表(pwd选择到数据库)
        toDeleteColTable();
      } else if (command.size() == 4 &&
                 data.size() == 3) {  // 删除_列_数据库_表 (pwd只需登录)
        toDeleteColDatabaseTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
    case 行: {
      if (command.size() == 2 && data.size() == 1) {
        toDeleteRow();
      } else if (command.size() == 3 && data.size() == 2) {
        toDeleteRowTable();
      } else if (command.size() == 4 && data.size() == 3) {
        toDeleteRowDatabaseTable();
      } else {
        menuOutput::printCommandError(ReturnPower(), need);
        Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                         编译错误);
      }
      return;
    }
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
    BackTracking::BackTrackingForCreateDatabaseTable(pwd[1], data[0]);
    table.remove();
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0]);
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table, 5, false);
  if (inputACK()) {
    BackTracking::BackTrackingForRecoverDatabaseTable(pwd[1], data[0]);
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
    BackTracking::BackTrackingForCreateDatabaseTable(data[0], data[1]);
    table.remove();
    Log::LogForDeleteDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1]);
    menuOutput::printDeleteACK(ReturnPower(), need);
    return;
  }
  menuOutput::printTableNotEmptyAndDeleteTip(ReturnPower(), false);
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table, 5, false);
  if (inputACK()) {
    BackTracking::BackTrackingForRecoverDatabaseTable(data[0], data[1]);
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
    BackTracking::BackTrackingForCreateDatabase(data[0]);
    menuOutput::printDeleteACK(ReturnPower(), need);

    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0]);
    return;
  } else {
    menuOutput::printDatabaseNotEmptyAndDeleteTip(ReturnPower(), false);
  }
  menuOutput::openDirPrintFile(ReturnPower(), database.returnTruePath(), false);
  if (inputACK()) {
    Log::LogForDeleteDatabase(ReturnUserName(), ReturnPower(), data[0]);
    BackTracking::BackTrackingForRecoverDatabase(data[0]);
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
  vstring tmpdata = deleteUser(data[0]);
  if (!tmpdata.size()) {
    BackTracking::BackTrackingForCreateManager(ReturnUserName(),
                                               returnPassword());
    Log::LogForDeleteManager(ReturnUserName(), ReturnPower(), data[0],
                             目标管理员不存在无法删除);
    menuOutput::printManagerNotExists(ReturnPower(), need);
    return;
  }
  BackTracking::BackTrackingForCreateManager(tmpdata[0], tmpdata[1]);
  menuOutput::printDeleteACK(ReturnPower(), need);
  Log::LogForDeleteManager(ReturnUserName(), ReturnPower(), data[0]);
}
void shell::toDeleteUser() {
  vstring tmpdata = deleteUser(data[0]);
  if (!tmpdata.size()) {
    Log::LogForDeleteUser(ReturnUserName(), ReturnPower(), data[0],
                          目标用户不存在无法删除);
    menuOutput::printUserNotExists(ReturnPower(), need);
    return;
  }
  BackTracking::BackTrackingForCreateUser(tmpdata[0], tmpdata[1]);
  Log::LogForDeleteUser(ReturnUserName(), ReturnPower(), data[0]);
  menuOutput::printDeleteACK(ReturnPower(), need);
}
void shell::toDeleteCol() {
  /* 这个一个特殊情况，删除列对于Cache存储索引来说需要大修，与其修倒不如删除倒不如退出索引等下次使用再导入*/
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
  } else if (pwd.size() == 2) {
    menuOutput::printNotChooseTable(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 未选择表);
  } else {
    Table tmpTable(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
    if (!tmpTable.isExist()) {
      menuOutput::printNotExistsTable(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       已选择的数据库中不存在目标表);
      return;
    }
    vstring deleteData = tmpTable.deleteCol(std::atoi(data[0].c_str()));
    if (deleteData.size() != 0) {
      BackTracking::BackTrackingForInsertColDatabaseTable(pwd[1], pwd[2],
                                                          deleteData);
      menuOutput::printDeleteACK(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        pwd[2], data[0]);
      View::deleteColUpdate(tmpTable.returnName(), data[0]);
    } else {
      menuOutput::printNotExistsTableRow(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        pwd[2], data[0], 不存在该列);
    }
  }
}
void shell::toDeleteColTable() {
  /* 这个一个特殊情况，删除列对于Cache存储索引来说需要大修，与其修倒不如删除倒不如退出索引等下次使用再导入*/
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
  } else {
    Table tmpTable(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
    if (!tmpTable.isExist()) {
      menuOutput::printNotExistsTable(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       已选择的数据库中不存在目标表);
      return;
    }
    vstring deleteData = tmpTable.deleteCol(std::atoi(data[1].c_str()));
    if (deleteData.size() != 0) {
      BackTracking::BackTrackingForInsertColDatabaseTable(pwd[1], data[0],
                                                          deleteData);
      menuOutput::printDeleteACK(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        data[0], data[1]);
      View::deleteColUpdate(tmpTable.returnName(), data[1]);
    } else {
      menuOutput::printNotExistsTableRow(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        data[0], data[1], 不存在该列);
    }
  }
}
void shell::toDeleteColDatabaseTable() {
  /* 这个一个特殊情况，删除列对于Cache存储索引来说需要大修，与其修倒不如删除倒不如退出索引等下次使用再导入*/
  Table tmpTable(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!tmpTable.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     已选择的数据库中不存在目标表);
    return;
  }
  vstring deleteData = tmpTable.deleteCol(std::atoi(data[2].c_str()));

  if (deleteData.size() != 0) {
    BackTracking::BackTrackingForInsertDatabaseTable(data[0], data[1],
                                                     deleteData);
    menuOutput::printDeleteACK(ReturnPower(), need);
    Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                      data[1], data[2]);
    View::deleteColUpdate(tmpTable.returnName(), data[2]);
  } else {
    menuOutput::printNotExistsTableCol(ReturnPower(), need);
    Log::LogForDeleteColDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                      data[1], data[2], 不存在该列);
  }
}
void shell::toInsert() {
  switch (command.size()) {
    case 1: {
      if (this->pwd.size() == 3) {
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
void shell::toDeleteRow() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
  } else if (pwd.size() == 2) {
    menuOutput::printNotChooseTable(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 未选择表);
  } else {
    Table tmpTable(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
    if (!tmpTable.isExist()) {
      menuOutput::printNotExistsTable(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       已选择的数据库中不存在目标表);
      return;
    }
    vstring deleteData = tmpTable.deleteTableLine(data[0]);
    if (deleteData.size() != 0) {
      BackTracking::BackTrackingForInsertDatabaseTable(pwd[1], pwd[2],
                                                       deleteData);
      if (!Cache::Count(tmpTable)) {
        Cache::add(tmpTable);
      } else {
        Cache::deleteTableItem(tmpTable, data[0]);
      }
      menuOutput::printDeleteACK(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        pwd[2], data[0]);
    } else {
      if (!Cache::Count(tmpTable)) {
        Cache::add(tmpTable);
      }
      menuOutput::printNotExistsTableRow(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        pwd[2], data[0], 不存在该列);
    }
  }
}
void shell::toDeleteRowTable() {
  if (pwd.size() == 1) {
    menuOutput::printNotChooseDatabase(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     未选择数据库越级选择表);
  } else {
    Table tmpTable(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
    if (!tmpTable.isExist()) {
      menuOutput::printNotExistsTable(ReturnPower(), need);
      Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                       已选择的数据库中不存在目标表);
      return;
    }
    Cache::add(tmpTable);
    vstring deleteData = tmpTable.deleteTableLine(data[1]);
    if (deleteData.size() != 0) {
      BackTracking::BackTrackingForInsertDatabaseTable(pwd[1], data[0],
                                                       deleteData);
      if (Cache::Count(tmpTable)) {
        Cache::deleteTableItem(tmpTable, data[1]);
      }
      menuOutput::printDeleteACK(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        data[0], data[1]);
    } else {
      menuOutput::printNotExistsTableRow(ReturnPower(), need);
      Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                        data[0], data[1], 不存在该列);
    }
  }
}
void shell::toDeleteRowDatabaseTable() {
  Table tmpTable(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!tmpTable.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data,
                     已选择的数据库中不存在目标表);
    return;
  }
  Cache::add(tmpTable);
  vstring deleteData = tmpTable.deleteTableLine(data[2]);
  if (deleteData.size() != 0) {
    BackTracking::BackTrackingForInsertDatabaseTable(data[0], data[1],
                                                     deleteData);
    if (Cache::Count(tmpTable)) {
      Cache::deleteTableItem(tmpTable, data[2]);
    }
    menuOutput::printDeleteACK(ReturnPower(), need);
    Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                      data[1], data[2]);
    return;
  }
  menuOutput::printNotExistsTableRow(ReturnPower(), need);
  Log::LogForDeleteRowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                    data[1], data[2], 不存在该列);
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
  Cache::add(table);
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);
  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                 data[1], tmp);
  TablePCB* tmpPCB = new TablePCB(data[0], data[1]);
  BackTracking::BackTrackingForDeleteRowDatabaseTable(
      data[0], data[1], tmp[tmpPCB->returnIndex()]);
  delete tmpPCB;
}
void shell::toInsertDefaultTable() {  // 当选择到表的时候，说明数据库+表都存在
  Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
  Cache::add(table);
  table.append(data);
  menuOutput::printInsertACK(ReturnPower(), need);
  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 pwd[2], data);
  TablePCB* tmpPCB = new TablePCB(pwd[1], pwd[2]);
  BackTracking::BackTrackingForDeleteRowDatabaseTable(
      pwd[1], pwd[2], data[tmpPCB->returnIndex()]);
  delete tmpPCB;
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
  Cache::add(table);
  table.append(tmp);
  menuOutput::printInsertACK(ReturnPower(), need);
  Log::LogForInsertDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                 data[0], tmp);
  TablePCB* tmpPCB = new TablePCB(pwd[1], data[0]);
  BackTracking::BackTrackingForDeleteRowDatabaseTable(
      pwd[1], data[0], tmp[tmpPCB->returnIndex()]);
  delete tmpPCB;
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
  Cache::add(table);
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
  Cache::add(table);
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
  Cache::add(table);
  menuOutput::printShowFindTable(ReturnPower(), ReturnUserName(), table,
                                 data[2], need);
  Log::LogForFindDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                               data[1], data[2]);
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
          if (data.size() == 1 || data.size() == 2 || data.size() == 3) {
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
      menuOutput::openDirPrintFile(ReturnPower(), database.returnTruePath(),
                                   need);
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
      Cache::add(table);
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
      Cache::add(table);
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
  Cache::add(table);
  menuOutput::printShowTable(ReturnPower(), ReturnUserName(), table,
                             _super::stringToInt(data[2]), need);
  Log::LogForShowDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                               data[1]);
}
void shell::toSet() {
  if (command.size() < 2 || data.size() == 0) {
    menuOutput::printCommandError(ReturnPower(), need);
    Log::LogForError(ReturnUserName(), ReturnPower(), command, data, 编译错误);
		return;
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
  Table table(data[0] + "/" + data[1], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printNotExistsTable(ReturnPower(), need);
    Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                     data[1], data[2],
                                     已选择的数据库中不存在目标表);
    return;
  }
  TablePCB* tmpPCB = new TablePCB(data[0], data[1]);
  BackTracking::BackTrackingForSetIndexDatabaseTable(
      data[0], data[1], std::to_string(tmpPCB->returnIndex()));
  delete tmpPCB;
  Cache::add(table);
  TablePCB::setIndex(data[0] + "/" + data[1], INDEX(atoi(data[2].c_str())));
  Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), data[0],
                                   data[1], data[2]);
  menuOutput::printSetACK(ReturnPower(), need);
  Index::update(data[0] + "/" + data[1]);
}
void shell::toSetIndexTable() {
  Table table(pwd[1] + "/" + data[0], type::_TYPE_TABLE);
  if (!table.isExist()) {
    menuOutput::printDatabaseNotHaveTable(ReturnPower(), need);
    Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                     data[0], data[1],
                                     已选择的数据库中不存在目标表);
    return;
  }
  TablePCB* tmpPCB = new TablePCB(pwd[1], data[0]);
  BackTracking::BackTrackingForSetIndexDatabaseTable(
      pwd[1], data[0], std::to_string(tmpPCB->returnIndex()));
  delete tmpPCB;
  Cache::add(table);
  TablePCB::setIndex(pwd[1] + "/" + data[0], INDEX(atoi(data[1].c_str())));
  Log::LogForSetIndexDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                   data[0], data[1]);
  menuOutput::printSetACK(ReturnPower(), need);
  Index::update(pwd[1] + "/" + data[0]);
}
void shell::toSetIndexDefault() {
  TablePCB* tmpPCB = new TablePCB(pwd[1], pwd[2]);
  BackTracking::BackTrackingForSetIndexDatabaseTable(
      pwd[1], pwd[2], std::to_string(tmpPCB->returnIndex()));
  delete tmpPCB;
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
  std::set<int> allowCol_tmp =
      View::returnAllowColumn(data[2], data[0], data[1]);
  vstring allowColToStr;
  for (auto& t : allowCol_tmp) {
    allowColToStr.push_back(std::to_string(t));
  }
  BackTracking::BackTrackingForSetViewDatabaseTable(data[0], data[1], data[2],
                                                    allowColToStr);
  Cache::add(table);
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
  std::set<int> allowCol_tmp =
      View::returnAllowColumn(data[1], pwd[1], data[0]);
  vstring allowColToStr;
  for (auto& t : allowCol_tmp) {
    allowColToStr.push_back(std::to_string(t));
  }
  BackTracking::BackTrackingForSetViewDatabaseTable(pwd[1], data[0], data[1],
                                                    allowColToStr);
  Cache::add(table);
  View::setAllowShowColumn(data[1], allowCol, pwd[1], data[0]);
  Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                  data[0], data[1], allowCol);
  menuOutput::printSetACK(ReturnPower(), need);
}
void shell::toSetViewDefault() {
  std::set<int> allowCol_tmp = View::returnAllowColumn(data[0], pwd[1], pwd[2]);
  vstring allowColToStr;
  for (auto& t : allowCol_tmp) {
    allowColToStr.push_back(std::to_string(t));
  }
  BackTracking::BackTrackingForSetViewDatabaseTable(pwd[1], pwd[2], data[0],
                                                    allowColToStr);
  vstring allowCol(data.begin() + 1, data.end());
  Table table(pwd[1] + "/" + pwd[2], type::_TYPE_TABLE);
  Cache::add(table);
  View::setAllowShowColumn(data[0], allowCol, pwd[1], pwd[2]);
  Log::LogForSetViewDatabaseTable(ReturnUserName(), ReturnPower(), pwd[1],
                                  pwd[2], data[0], allowCol);
  menuOutput::printSetACK(ReturnPower(), need);
}
void shell::addHistory(std::string& str) {
  this->history.push_back(str);
  ++this->historyIndex;
}
std::string shell::prevHistory() {
  if (this->historyIndex > 0) {
    --this->historyIndex;
  }
  return this->history[historyIndex];
}
std::string shell::nextHistory() {
  if (this->historyIndex < this->history.size()) {
    ++this->historyIndex;
  }
  return this->history[this->historyIndex];
}
bool shell::hasHistory() { return this->historyIndex; }
