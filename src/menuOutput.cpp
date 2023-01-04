/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2023-01-04 16:58:27
 */
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
menuOutput::menuOutput() {}
menuOutput::~menuOutput() {}
void menuOutput::printDatabaseIsExists(TYPE_POWER power, bool need) {
  printPower(power,need);
  std::cout << "无法执行该指令，目标数据库已存在" << std::endl;
  printPower(power,need);
}
void menuOutput::printPower(TYPE_POWER power, bool need) {
  if (!need) {
    return;
  }
  switch (power) {
    case TYPE_POWER::ROOT: {
      std::cout << "(超级管理员) -=> ";
      break;
    }
    case TYPE_POWER::Manager: {
      std::cout << "(管理员) -=> ";
      break;
    }
    case TYPE_POWER::NORMAL: {
      std::cout << "(用户) -=> ";
      break;
    }
    case TYPE_POWER::NONE: {
      std::cout << "(未登录) -=> ";
      break;
    }
  }
}
void menuOutput::printTableIsExists(TYPE_POWER power,bool need){
  printPower(power,need);
  std::cout << "无法执行该指令，目标表已存在" << std::endl;
  printPower(power,need);
}
void menuOutput::printNotFindSQL(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，目标脚本不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printExit(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "已退出!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotLogin(bool need) {
  printPower(TYPE_POWER::NONE, need);
  std::cout << "未登录,请登录后操作!" << std::endl;
  printPower(TYPE_POWER::NONE, need);
}
void menuOutput::printNotExistsTable(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "目标表不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotExistsDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "目标数据库不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotChooseDatabase(TYPE_POWER power, bool need){
  printPower(power,need);
  std::cout << "该指令无法执行，没有选择数据库!" << std::endl;
   printPower(power,need);
}
void menuOutput::printPWD(vstring& pwd, TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "当前路径为: ";
  if (pwd.size() == 0) {
    std::cout << "[]";
  }
  for (std::string& str : pwd) {
    std::cout << "[" + str + "]";
  }
  std::cout << std::endl;
  printPower(power, need);
}
void menuOutput::printPowerNoEnough(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "您没有执行该指令的权限!" << std::endl;
  printPower(power, need);
}
void menuOutput::printDatabaseNotHaveTable(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，该数据库中不存在此表" << std::endl;
  printPower(power, need);
}
void menuOutput::printCommandError(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令,该指令输入错误，请重新输入!" << std::endl;
  printPower(power, need);
}
void menuOutput::printLoginOrNot(bool Login,
                                 TYPE_POWER power,
                                 std::string ID,
                                 bool need) {
  printPower(power, need);
  if (Login) {
    std::cout << "登录成功，欢迎您，" + ID + "!" << std::endl;
  } else {
    std::cout << "登录失败!" << std::endl;
  }
  printPower(power, need);
}