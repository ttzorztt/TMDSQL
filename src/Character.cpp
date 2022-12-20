/*
 * @Description  : 字符集获取
 * @Autor        : TMD
 * @Date         : 2022-12-18 10:36:09
 * @LastEditTime : 2022-12-20 10:59:00
 */
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "Character.h"
#endif
Character::Character() {
  HashMapCID["退出"] = 1;
  HashMapCID["创建"] = 2;
  HashMapCID["数据库"] = 3;
  HashMapCID["删除"] = 4;
  HashMapCID["选择"] = 5;
  HashMapCID["重命名"] = 6;
  HashMapCID["登录"] = 7;
  HashMapCID["显示"] = 8;
  HashMapCID["插入"] = 9;
  HashMapCID["查询"] = 10;
  HashMapCID["表"] = 11;
  HashMapCID["普通用户"] = 12;
  HashMapCID["管理员"] = 13;
}
Character Character::charObj; 
Character& Character::Create() {
  return charObj;
}
int main(int argc, char const* argv[]) {
  return 0;
}
