/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-12-22 15:27:59
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
shell::shell(): user(){}
shell::~shell() {}
bool shell::read(std::string str) {
  vstring vectorbuff;
  _super::stringToVector(str, vectorbuff);
  if (!HashMapCID.count(vectorbuff[0])) {
    return false;
  }
  switch (HashMapCID[vectorbuff[0]]) {
    case 退出:
      menuOutput::printExit(user);
      break;
    case 创建:
      toCreate(vectorbuff);
      break;
    case 删除:
      break;
    case 重命名:
      break;
    case 登录:
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