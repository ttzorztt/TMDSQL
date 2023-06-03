/**
 * @file view.cpp
 * @brief 视图层的实现
 * @author TMD
 * @date 2023-01-18
 */
#ifndef _VIEW_H_
#define _VIEW_H_
#include "view.h"

#include "file.h"
#include "super.h"
#endif

#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
void View::setAllowShowColumn(std::string UserName,
                              std::vector<std::string> allowColumn,
                              std::string viewDBID, std::string viewTBID) {
  vstring tmp;
  allowColumn.insert(allowColumn.begin(), UserName);
  _file table(viewDBID + "/" + viewTBID, type::_TYPE_VIEW);
  if (table.isExist()) {
    table.setOpenBuff(0);
    while (table.readline(tmp)) {
      if (tmp[0] == UserName) {
        table.deleteFileLine(UserName);
        break;
      }
    }
  } else {
    table.create();
  }
  table.write(allowColumn, type_mode::WRITEBUFF_MODE_APP);
}
std::set<int> View::returnAllowColumn(std::string UserName,
                                      std::string DatabaseAndTableName) {
  _file table(DatabaseAndTableName, type::_TYPE_VIEW);
  return returnAllowColumn(UserName, table);
}
std::set<int> View::returnAllowColumn(std::string& UserName, _file& table) {
  if (!table.isExist()) {
    return {};
  } else {
    std::set<int> ret;
    vstring tmp;
    table.setOpenBuff(0);
    while (table.readline(tmp)) {
      if (tmp[0] == UserName) {
        for (int a = tmp.size() - 1; a > 0; --a) {
          ret.insert(std::atoi(tmp[a].c_str()));
        }
      }
    }
    return ret;
  }
}
std::set<int> View::returnAllowColumn(std::string UserName, std::string DBID,
                                      std::string TBID) {
  _file table(DBID + "/" + TBID, type::_TYPE_VIEW);
  return returnAllowColumn(UserName, table);
}
void View::deleteColUpdate(std::string DatabaseAndTableName,
                           std::string colnumber) {
  _file* tmpViewFIle =
      new _file(DatabaseAndTableName + "tmp", type::_TYPE_VIEW);
  if (tmpViewFIle->isExist()) {
    tmpViewFIle->remove();
  }
  tmpViewFIle->create();
  _file* viewFile = new _file(DatabaseAndTableName, type::_TYPE_VIEW);
  vstring tmp;
  vstring newView;
  while (viewFile->readline(tmp)) {
    for (auto& t : tmp) {
      if (t == colnumber) {
        continue;
      } else {
        newView.push_back(t);
      }
    }
    if (newView.size() > 0) {
      tmpViewFIle->write(newView, type_mode::WRITEBUFF_MODE_APP);
    }
	std::vector<std::string>().swap(newView);
  }
  delete viewFile;
  tmpViewFIle->rename(
      _super::returnTruePath(DatabaseAndTableName, type::_TYPE_VIEW));
  delete tmpViewFIle;
}
