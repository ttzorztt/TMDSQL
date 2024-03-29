/**
 * @file menuOutput.cpp
 * @brief 菜单输出类
 * @author TMD
 * @date 2022-12-22
 */
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
#ifndef _CACHE_H_
#define _CACHE_H_
#include "cache.h"
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
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _VIEW_H_
#define _VIEW_H_
#include "view.h"
#endif
#ifndef _TABLEPCB_H_
#define _TABLEPCB_H_
#include "TablePCB.h"
#endif
menuOutput::menuOutput() {}
menuOutput::~menuOutput() {}

void menuOutput::printChooseACK(TYPE_POWER power, bool need) {
  std::cout << "选择成功!" << std::endl;
  printPower(power, need);
}
void menuOutput::printCreateACK(TYPE_POWER power, bool need) {
  std::cout << "创建成功!" << std::endl;
  printPower(power, need);
}
void menuOutput::printSetACK(TYPE_POWER power, bool need) {
  std::cout << "设置成功!" << std::endl;
  printPower(power, need);
}
void menuOutput::printDeleteACK(TYPE_POWER power, bool need) {
  std::cout << "删除成功!" << std::endl;
  printPower(power, need);
}
void menuOutput::printInsertACK(TYPE_POWER power, bool need) {
  std::cout << "插入成功!" << std::endl;
  printPower(power, need);
}
void menuOutput::printUserExists(TYPE_POWER power, bool need) {
  std::cout << "该用户已存在，无法添加!" << std::endl;
  printPower(power, need);
}
void menuOutput::printManagerExists(TYPE_POWER power, bool need) {
  std::cout << "该管理员已存在，无法添加!" << std::endl;
  printPower(power, need);
}
void menuOutput::printShowDatabase(TYPE_POWER power, bool need) {
  vstring ans;
  _dir::openDirReturnFileName("./data/database/", ans);
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "暂时还没有建立数据库" << std::endl;
    menuOutput::printPower(power, need);
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
void menuOutput::openDirPrintFile(TYPE_POWER power, std::string truePath, bool need) {
  vstring ans;
	_dir::openDirReturnFileName(truePath,ans);
  int maxtablename = 0;
  if (ans.size() == 0) {
    std::cout << "这个数据库是空的!" << std::endl;
    menuOutput::printPower(power, need);
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
  menuOutput::printPower(power, need);
}
void menuOutput::printDatabaseIsExists(TYPE_POWER power, bool need) {
  std::cout << "无法执行该指令，目标数据库已存在!" << std::endl;
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
void menuOutput::printTableNotEmptyAndDeleteTip(TYPE_POWER power, bool need) {
  std::cout << "表不为空，以下是该表的一部分内容:" << std::endl;
  printPower(power, need);
}
void menuOutput::printTableIsExists(TYPE_POWER power, bool need) {
  std::cout << "无法执行该指令，目标表已存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotFindSQL(TYPE_POWER power, bool need) {
  std::cout << "无法执行该指令，目标脚本不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printExit(TYPE_POWER power, bool need) {
  std::cout << "已退出!" << std::endl;
}
void menuOutput::printNotLogin(bool need) {
  std::cout << "未登录,请登录后操作!" << std::endl;
  printPower(TYPE_POWER::NONE, need);
}
void menuOutput::printNotExistsTable(TYPE_POWER power, bool need) {
  std::cout << "目标表不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotExistsDatabase(TYPE_POWER power, bool need) {
  std::cout << "目标数据库不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotChooseDatabase(TYPE_POWER power, bool need) {
  std::cout << "该指令无法执行，没有选择数据库!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotChooseTable(TYPE_POWER power, bool need) {
  std::cout << "该指令无法执行，没有选择表!" << std::endl;
  printPower(power, need);
}
void menuOutput::printPWD(vstring& pwd, TYPE_POWER power, bool need) {
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
  std::cout << "您没有执行该指令的权限!" << std::endl;
  printPower(power, need);
}
void menuOutput::printDatabaseNotHaveTable(TYPE_POWER power, bool need) {
  std::cout << "无法执行该指令，该数据库中不存在此表!" << std::endl;
  printPower(power, need);
}
void menuOutput::printCommandError(TYPE_POWER power, bool need) {
  std::cout << "无法执行该指令,该指令输入错误，请重新输入!" << std::endl;
  printPower(power, need);
}
void menuOutput::printLoginOrNot(bool Login, TYPE_LOGIN_ERROR typeError,
                                 TYPE_POWER power, std::string ID, bool need) {
  if (Login) {
    std::cout << "登录成功，欢迎您，" + ID + "!" << std::endl;
  } else {
    switch (typeError) {
      case 帐号不存在:
        std::cout << "帐号不存在,";
        break;
      case 密码错误:
        std::cout << "密码错误,";
        break;
    }
    std::cout << "登录失败!" << std::endl;
  }
  printPower(power, need);
}
void menuOutput::printUserNotExists(TYPE_POWER power, bool need) {
  std::cout << "该用户不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printShowFindTable(TYPE_POWER power, std::string UserName,
                                    Table& table, std::string index,
                                    bool need) {
  vstring data;
  if (Cache::Count(table)) {
    data = Cache::find(table, index);
  } else {
    data = table.find(index);
  }
  if (power == 2) {
    std::set<int> allowCol =
        View::returnAllowColumn(UserName, table.returnName());
    if (data.size() != 0) {
      int size = data.size();
      for (int a = 0; a < size; ++a) {
        if (!allowCol.count(a)) {
          continue;
        }
        std::cout << data[a] << " ";
      }
      std::cout << std::endl;
    } else {
      std::cout << "搜索结束，没有搜到目标值!" << std::endl;
    }
  } else {
    if (data.size() != 0) {
      int size = data.size();
      for (int a = 0; a < size; ++a) {
        std::cout << data[a] << " ";
      }
      std::cout << std::endl;
    } else {
      std::cout << "搜索结束，没有搜到目标值!" << std::endl;
    }
  }
  printPower(power, need);
  if (!Cache::Count(table)) {
    Cache::add(table);
  }
}
void menuOutput::printDatabaseNotEmptyAndDeleteTip(TYPE_POWER power,
                                                   bool need) {
  std::cout << "数据库并不为空，以下为当前存在的表项:" << std::endl;
  printPower(power, need);
}
void menuOutput::printCommandBackout(TYPE_POWER power, bool need) {
  std::cout << "该指令已取消!" << std::endl;
  printPower(power, need);
}
void menuOutput::printManagerNotExists(TYPE_POWER power, bool need) {
  std::cout << "该管理员不存在!" << std::endl;
  printPower(power, need);
}
void menuOutput::printShowTable(TYPE_POWER power, std::string User,
                                Table& table, int number, bool need) {
  if (number < 0) {
    menuOutput::printCommandError(power, need);
    return;
  } else if (number > 0) {
    if (TablePCB(table).returnEndLineIndex() == 0) {
      std::cout << "表为空!" << std::endl;
      printPower(power, need);
      return;
    }
    if (power == 2) {
      std::set<int> allowColumn =
          View::returnAllowColumn(User, table.returnName());
      if (allowColumn.size() == 0) {
        std::cout << "表为空!" << std::endl;
        printPower(power, need);
        return;
      }
      vstring tmp;
      while (table.readline(tmp) && number) {
        int size = tmp.size();
        for (int a = 0; a < size; ++a) {
          if (!allowColumn.count(a)) {
            continue;
          }
          std::cout << tmp[a] << " ";
        }
        std::cout << std::endl;
        --number;
      }
    } else {
      vstring tmp;
      while (table.readline(tmp) && number) {
        int size = tmp.size();
        for (int a = 0; a < size; ++a) {
          std::cout << tmp[a] << " ";
        }
        std::cout << std::endl;
        --number;
      }
    }
    printPower(power, need);
  }
}
void menuOutput::printNotExistsTableRow(TYPE_POWER power, bool need) {
  std::cout << "不存在该行!" << std::endl;
  printPower(power, need);
}
void menuOutput::printNotExistsTableCol(TYPE_POWER power, bool need) {
  std::cout << "不存在该列!" << std::endl;
  printPower(power, need);
}
void menuOutput::printBackTrackingACK(TYPE_POWER power, bool need) {
  std::cout << "回溯成功" << std::endl;
  printPower(power, need);
}
void menuOutput::printBackTrackingClearACK(TYPE_POWER power, bool need) {
  std::cout << "回溯文件清理成功" << std::endl;
  printPower(power, need);
}
