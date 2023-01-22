/*
 * @Description  : 视图层的实现
 * @Autor        : TMD
 * @Date         : 2023-01-18 17:00:47
 * @LastEditTime : 2023-01-22 17:23:53
 */
#ifndef _VIEW_H_
#define _VIEW_H_
#include "view.h"
#endif

#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
void View::setAllowShowColumn(std::string UserName,
                              std::vector<std::string> allowColumn,
                              std::string viewDBID,
                              std::string viewTBID) {
  vstring tmp;
  allowColumn.insert(allowColumn.begin(), UserName);
  Table table(viewDBID + "/" + viewTBID, type::_TYPE_VIEW);
  if (table.isExist()) {
    table.setOpenBuff(0);
    while (table.readline(tmp)) {
      if (tmp[0] == UserName) {
        table.deleteLine(UserName);
        break;
      }
    }
  } else {
    table.create();
  }
  table.append(allowColumn);
}
std::set<int> View::returnAllowColumn(std::string UserName, Table& table) {
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
std::set<int> View::returnAllowColumn(std::string UserName,
                                      std::string DBID,
                                      std::string TBID) {
  Table table(DBID + TBID, type::_TYPE_VIEW);
  return returnAllowColumn(UserName, table);
}