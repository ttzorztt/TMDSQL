/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2022-12-22 10:35:36
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
int menuOutput::printPower(const User& user) {
  switch (user.ReturnPower()) {
    case TYPE_POWER::ROOT:
      std::cout <<"(超级管理员) -=> ";
      return 16;
    case TYPE_POWER::Manager:
      std::cout <<"(管理员) -=> ";
      return 12;
    case TYPE_POWER::NORMAL:
      std::cout <<"(用户) -=> ";
      return 11;
    case TYPE_POWER::NONE:
        std::cout << "(未登录) -=> ? ";
  }
}
void menuOutput::printExit(const User& user) {
  menuOutput::printPower(user);
  std::cout << "已退出!" << std::endl;
}