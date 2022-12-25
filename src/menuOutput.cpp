/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2022-12-25 21:57:23
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
    case TYPE_POWER::ROOT:
      print("(超级管理员) -=> ");
    case TYPE_POWER::Manager:
      print("(管理员) -=> ");
    case TYPE_POWER::NORMAL:
      print("(用户) -=> ");
    case TYPE_POWER::NONE:
      print("(未登录) -=> ");
  }
}
void menuOutput::printExit(TYPE_POWER power) {
  printPower(power);
  printl("已退出!");
}
void menuOutput::printNotLogin(TYPE_POWER power) {
  printPower(power);
  printl("未登录,请登录后操作!");
}
void menuOutput::printPowerNoEnough(TYPE_POWER power) {
  printPower(power);
  printl("您没有执行该指令的权限!");
}
void menuOutput::printCommandError(TYPE_POWER power) {
  printPower(power);
  printl("该指令输入错误，请重新输入!");
}
void menuOutput::printLoginOrNot(bool Login,TYPE_POWER power,std::string ID){
  printPower(power);
  if(Login){
    printl("登录成功，欢迎您 " + ID + " !");
  }else{
    printl("登录失败!");
  }
}
void menuOutput::printl(std::string _str){
  std::cout << _str << std::endl;
}
 void menuOutput::print(std::string _str){
  std::cout << _str;
}