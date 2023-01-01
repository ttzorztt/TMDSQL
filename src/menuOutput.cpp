/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2023-01-01 17:00:31
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
  printl("无法执行该指令，目标数据库已存在");
  printPower(power,need);
}
void menuOutput::printPower(TYPE_POWER power, bool need) {
  if (!need) {
    return;
  }
  switch (power) {
    case TYPE_POWER::ROOT: {
      print("(超级管理员) -=> ");
      break;
    }
    case TYPE_POWER::Manager: {
      print("(管理员) -=> ");
      break;
    }
    case TYPE_POWER::NORMAL: {
      print("(用户) -=> ");
      break;
    }
    case TYPE_POWER::NONE: {
      print("(未登录) -=> ");
      break;
    }
  }
}
void menuOutput::printTableIsExists(TYPE_POWER power,bool need){
  printPower(power,need);
  printl("无法执行该指令，目标表已存在");
  printPower(power,need);
}
void menuOutput::printNotFindSQL(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("无法执行该指令，目标脚本不存在!");
  printPower(power, need);
}
void menuOutput::printExit(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("已退出!");
  printPower(power, need);
}
void menuOutput::printNotLogin(bool need) {
  printPower(TYPE_POWER::NONE, need);
  printl("未登录,请登录后操作!");
  printPower(TYPE_POWER::NONE, need);
}
void menuOutput::printNotChooseDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("无法执行该指令，请先选择数据库!");
  printPower(power, need);
}
void menuOutput::printNotExistsDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("该数据库不存在!");
  printPower(power, need);
}
void menuOutput::printPWD(vstring& pwd, TYPE_POWER power, bool need) {
  printPower(power, need);
  print("当前路径为: ");
  if (pwd.size() == 0) {
    print("[]");
  }
  for (std::string& str : pwd) {
    print("[" + str + "]");
  }
  printl("");
  printPower(power, need);
}
void menuOutput::printPowerNoEnough(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("您没有执行该指令的权限!");
  printPower(power, need);
}
void menuOutput::printDatabaseNotHaveTable(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("无法执行该指令，该数据库中不存在此表");
  printPower(power, need);
}
void menuOutput::printCommandError(TYPE_POWER power, bool need) {
  printPower(power, need);
  printl("无法执行该指令,该指令输入错误，请重新输入!");
  printPower(power, need);
}
void menuOutput::printLoginOrNot(bool Login,
                                 TYPE_POWER power,
                                 std::string ID,
                                 bool need) {
  printPower(power, need);
  if (Login) {
    printl("登录成功，欢迎您，" + ID + "!");
  } else {
    printl("登录失败!");
  }
  printPower(power, need);
}
void menuOutput::printl(std::string _str) {
  std::cout << _str << std::endl;
}
void menuOutput::print(std::string _str) {
  std::cout << _str;
}