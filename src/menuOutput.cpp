/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2022-12-27 21:36:31
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
void menuOutput::printPower(TYPE_POWER power) {
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
void menuOutput::printExit(TYPE_POWER power) {
  printPower(power);
  printl("已退出!");
}
void menuOutput::printNotLogin() {
  printPower();
  printl("未登录,请登录后操作!");
}
void menuOutput::printNotChooseDatabase(TYPE_POWER power) {
  printPower(power);
  printl("无法执行该指令，请先选择数据库!");
}
void menuOutput::printNotExistsDatabase(TYPE_POWER power) {
  printPower(power);
  printl("该数据库不存在!");
}
void menuOutput::printPWD(vstring& pwd, TYPE_POWER power) {
  printPower(power);
  print("当前路径为: ");
  for (std::string& str : pwd) {
    print(str);
  }
  printl("");
}
void menuOutput::printPowerNoEnough(TYPE_POWER power) {
  printPower(power);
  printl("您没有执行该指令的权限!");
}
void menuOutput::printDatabaseNotHaveTable(TYPE_POWER power) {
  printPower(power);
  printl("无法执行该指令，该数据库中不存在此表");
}
void menuOutput::printCommandError(TYPE_POWER power) {
  printPower(power);
  printl("无法执行该指令,该指令输入错误，请重新输入!");
}
void menuOutput::printLoginOrNot(bool Login, TYPE_POWER power, std::string ID) {
  printPower(power);
  if (Login) {
    printl("登录成功，欢迎您，" + ID + "!");
  } else {
    printl("登录失败!");
  }
}
void menuOutput::printl(std::string _str) {
  std::cout << _str << std::endl;
}
void menuOutput::print(std::string _str) {
  std::cout << _str;
}