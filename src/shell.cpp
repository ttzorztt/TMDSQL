/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-12-25 16:47:18
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
std::unordered_map<std::string, int> shell::HashMapCID = {
    {"退出", 0},   {"创建", 1},      {"数据库", 2}, {"删除", 3}, {"选择", 4},
    {"重命名", 5}, {"登录", 6},      {"显示", 7},   {"插入", 8}, {"查询", 9},
    {"表", 10},    {"普通用户", 11}, {"管理员", 12}};
shell::shell() : user() {}
shell::~shell() {}
bool shell::logn(std::string ID, std::string password) {
  return this->user.login(ID, password);
}
bool shell::read(std::string str) {
  if (!this->user.ReturnLoginStatus()) {
    menuOutput::printExit(user.ReturnPower());
  }
  vstring vectorbuff;
  _super::stringToVector(str, vectorbuff);
  if (!HashMapCID.count(vectorbuff[0])) {
    return false;
  }
  switch (HashMapCID[vectorbuff[0]]) {
    case 退出:
      if (vectorbuff.size() == 1) {
        menuOutput::printExit(user.ReturnPower());
      } else {
        menuOutput::printCommandError(user.ReturnPower());
      }
      break;
    case 创建:
      if (user.ReturnPower() < 2) {  // 管理员和超级管理员权限
        toCreate(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(
            user.ReturnPower());  // 普通用户或未登录没有权限创建
      }
      break;
    case 删除:
      if (user.ReturnPower() < 2) {
        toDelete(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(user.ReturnPower());
      }
      break;
    case 重命名:
      if (user.ReturnPower() < 2) {
        toRename(vectorbuff);
      } else {
        menuOutput::printPowerNoEnough(user.ReturnPower());
      }
      break;
    case 登录:
      if (vectorbuff.size() != 3) {
        menuOutput::printCommandError(user.ReturnPower());
      } else {
        bool Login = this->login(vectorbuff[1],vectorbuff[2]);
        menuOutput::printLoginOrNot(Login);
      }
      break;
    case 插入:
      break;
    case 查询:
      break;
    case 显示:
      break;
    default:
      break;
  }
  return false;
}
void shell::toCreate(revstring value){}
void shell::toDelete(revstring value){}
void shell::toRename(revstring value){}