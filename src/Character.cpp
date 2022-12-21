/*
 * @Description  : 字符集获取
 * @Autor        : TMD
 * @Date         : 2022-12-18 10:36:09
 * @LastEditTime : 2022-12-20 17:05:17
 */
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "Character.h"
#endif

Character Character::charObj;
std::unordered_map<std::string, int> Character::HashMapCID = {
    {"退出", 1},   {"创建", 2},      {"数据库", 3}, {"删除", 4}, {"选择", 5},
    {"重命名", 6}, {"登录", 7},      {"显示", 8},   {"插入", 9}, {"查询", 10},
    {"表", 11},    {"普通用户", 12}, {"管理员", 13}};
Character::Character() {}
Character& Character::Create() {
  return charObj;
}