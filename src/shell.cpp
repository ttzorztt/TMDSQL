/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-12-21 21:56:34
 */
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
/**

一、数据库的基本操作

3、显示数据库版本
6、查看创建数据库的语句
7、查看当前使用的数据库
8、查看当前用户
9、使用某个数据库
10、删除数据库
二、数据表的基本操作
3、查看表结构
4、查看创建表的语句
5、向表中插入，更新，删除数据
6、查看表中数据
7、修改表名字
8、修改表字段信息
9、删除表
三、mysql查询操作
1、基本查询
2、条件
3、排序
4、聚合函数
5、分组
6、连接查询
6.1、内连接查询
6.2、外连接查询
6.2.1、左连接查询
6.2.2、右连接查询
7、自关联
8、子查询和联合查询
*/

/***

Tip: 将代码放在前部，将用户输入自定义字符放在后端，以@开头，并以';'结尾。
方便状态机检测

创建 数据库 @XXX;  ----->         status : 1
删除 数据库 @XXX;  ----->         status : 3
创建 表  @XXX;      ----->         status : 5
删除 表  @XXX;      ----->         status : 6
添加 数据 表 @xxx; ----->
添加 表 数据库 @xxx;
显示 数据库;
显示 表;

*/
std::unordered_map<std::string, int> shell::HashMapCID = {
    {"退出", 0},   {"创建", 1},      {"数据库", 2}, {"删除", 3}, {"选择", 4},
    {"重命名", 5}, {"登录", 6},      {"显示", 7},   {"插入", 8}, {"查询", 9},
    {"表", 10},    {"普通用户", 11}, {"管理员", 12}};
shell::shell() {}
shell::~shell() {}
bool shell::read(std::string str) {
  _super::stringToVector(str, vecBuff);
  if (!HashMapCID.count(vecBuff[0])) {
    return false;
  }
  switch (HashMapCID[vecBuff[0]]) {
    case 退出:
      break;
    case 创建:
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