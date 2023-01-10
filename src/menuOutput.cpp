/*
 * @Description  : 菜单输出类
 * @Autor        : TMD
 * @Date         : 2022-12-22 08:16:13
 * @LastEditTime : 2023-01-10 19:02:19
 */
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
#ifndef _IOMANIP_
#define _IOMANIP_
#include <iomanip>
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
#ifndef _DIR_H_
#define _DIR_H_
#include "dir.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
menuOutput::menuOutput() {}
menuOutput::~menuOutput() {}
void menuOutput::printShowDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  vstring ans;
  _dir::openDirReturnFileName("../data/database/", ans);
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "暂时还没有建立数据库" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  maxtablename += 2;
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "?";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "?";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "#";
  }
  std::cout << std::endl;
  printPower(power, need);
}
void menuOutput::printShowDatabase(TYPE_POWER power,
                                   DataBase& database,
                                   bool need) {
  if (!database.isExist()) {
    std::cout << "数据库不存在!" << std::endl;
    return;
  }
  vstring ans;
  database.openDirReturnFileName(ans);
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "这个数据库是空的!" << std::endl;
    return;
  }
  for (std::string& str : ans) {
    maxtablename = std::max(maxtablename, (int)str.size() + 2);
  }
  maxtablename += 2;
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
  for (std::string& str : ans) {
    int strnamesize = str.size();
    int left = (maxtablename - strnamesize) / 2;
    std::cout << "|";
    for (int a = 1; a < left; ++a) {
      std::cout << " ";
    }
    std::cout << str;
    for (int a = maxtablename - strnamesize - left - 1; a > 0; --a) {
      std::cout << " ";
    }
    std::cout << "|";
    std::cout << std::endl;
  }
  for (int a = 0; a < maxtablename; ++a) {
    std::cout << "*";
  }
  std::cout << std::endl;
}
void menuOutput::printDatabaseIsExists(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，目标数据库已存在" << std::endl;
  printPower(power, need);
}
void menuOutput::printPower(TYPE_POWER power, bool need) {
  if (!need) {
    return;
  }
  switch (power) {
    case TYPE_POWER::ROOT: {
      std::cout << "(超级管理员) -=> ";
      break;
    }
    case TYPE_POWER::Manager: {
      std::cout << "(管理员) -=> ";
      break;
    }
    case TYPE_POWER::NORMAL: {
      std::cout << "(用户) -=> ";
      break;
    }
    case TYPE_POWER::NONE: {
      std::cout << "(未登录) -=> ";
      break;
    }
  }
}
void menuOutput::printTableIsExists(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，目标表已存在" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotFindSQL(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，目标脚本不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printExit(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "已退出!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotLogin(bool need) {
  printPower(TYPE_POWER::NONE, need);
  std::cout << "未登录,请登录后操作!" << std::endl;
  printPower(TYPE_POWER::NONE, need);
}
void menuOutput::printNotExistsTable(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "目标表不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotExistsDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "目标数据库不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotChooseDatabase(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "该指令无法执行，没有选择数据库!" << std::endl;
  printPower(power, need);
}
void menuOutput::printPWD(vstring& pwd, TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "当前路径为: ";
  if (pwd.size() == 0) {
    std::cout << "[]";
  }
  for (std::string& str : pwd) {
    std::cout << "[" + str + "]";
  }
  std::cout << std::endl;
  printPower(power, need);
}
void menuOutput::printPowerNoEnough(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "您没有执行该指令的权限!" << std::endl;
  printPower(power, need);
}
void menuOutput::printDatabaseNotHaveTable(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令，该数据库中不存在此表" << std::endl;
  printPower(power, need);
}
void menuOutput::printCommandError(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "无法执行该指令,该指令输入错误，请重新输入!" << std::endl;
  printPower(power, need);
}
void menuOutput::printLoginOrNot(bool Login,
                                 TYPE_POWER power,
                                 std::string ID,
                                 bool need) {
  printPower(power, need);
  if (Login) {
    std::cout << "登录成功，欢迎您，" + ID + "!" << std::endl;
  } else {
    std::cout << "登录失败!" << std::endl;
  }
  printPower(power, need);
}
void menuOutput::printUserNotExists(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "该用户不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printShowFindTable(TYPE_POWER power, vstring data, bool need) {
  printPower(power, need);
  if (data.size() != 0) {
    if (need) {
      std::cout << std::setw(powerPR[power]);
    }
    for (std::string& str : data) {
      std::cout << str << " ";
    }
    std::cout << std::endl;
  }
  printPower(power, need);
}
void menuOutput::printInsertNoValue(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "拒绝执行，指令中缺乏待插入数据!" << std::endl;
  printPower(power, need);
}
void menuOutput::printManagerNotExists(TYPE_POWER power, bool need) {
  printPower(power, need);
  std::cout << "该管理员不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printShowTable(TYPE_POWER power,
                                Table& table,
                                int number,
                                bool need) {
  if (number < 0) {
    menuOutput::printCommandError(power, need);
    return;
  } else if (number > 0) {
    printPower(power, need);
    vstring tmp;
    while (table.readline(tmp) && number) {
      for (std::string& str : tmp) {
        std::cout << str << " ";
      }
      std::cout << std::endl;
      --number;
    }
    printPower(power, need);
  }
}
