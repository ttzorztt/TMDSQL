/*
 * @Description  : TMDSQL语句的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 20:51:20
 * @LastEditTime : 2022-11-09 19:11:04
 */
#include "shell.h"
#include <iostream>

/**

一、数据库的基本操作 
1、数据库的登录及退出
2、查看所有数据库
3、显示数据库版本
4、显示时间
5、创建数据库
6、查看创建数据库的语句
7、查看当前使用的数据库
8、查看当前用户
9、使用某个数据库
10、删除数据库
二、数据表的基本操作
1、查看当前数据库中的所有表
2、创建表
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
选择 数据库 @XXX;  ----->         status : 2
删除 数据库 @XXX;  ----->         status : 3
选择 表  @XXX;      ----->         status : 4
创建 表  @XXX;      ----->         status : 5
删除 表  @XXX;      ----->         status : 6
添加 数据 表 @xxx; ----->
添加 表 数据库 @xxx;
显示 数据库;
显示 表;
*/

shell::shell() {
  _GBKstatus.insert("创");
  _GBKstatus.insert("建");
  _GBKstatus.insert("数");
  _GBKstatus.insert("据");
  _GBKstatus.insert("库");
  _GBKstatus.insert("选");
  _GBKstatus.insert("择");
  _GBKstatus.insert("表");
  _GBKstatus.insert("添");
  _GBKstatus.insert("加");
  _GBKstatus.insert("显");
  _GBKstatus.insert("示");

  _binaryStatus["创"] = 1;
  _binaryStatus["建"] = 2;
  _binaryStatus["数"] = 3;
  _binaryStatus["据"] = 4;
  _binaryStatus["库"] = 5;
  _binaryStatus["选"] = 6;
  _binaryStatus["择"] = 7;
  _binaryStatus["表"] = 8;
  _binaryStatus["添"] = 9;
  _binaryStatus["加"] = 10;
  _binaryStatus["显"] = 11;
  _binaryStatus["示"] = 12;
}

int shell::readStatus() {
  std::string strbuff;
  std::cin >> strbuff;
  std::vector<std::string> ret;
  int size = strbuff.size();
  if (size % 2 == 0)
    return;
  else {
    int tmp = 0;
    while (tmp < size) {
      tmp += 2;
      if (_GBKstatus.count(strbuff.substr(tmp, 2))) {
      } else {
      }
    }
  }
}