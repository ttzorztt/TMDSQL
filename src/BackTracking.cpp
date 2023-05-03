/**
 * @file BackTracking.cpp
 * @brief 回溯类,第一个字符是上一行的指针，第二个字符是序号。
 * @author TMD
 * @date 2023-04-29
 */
#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_
#include "BackTracking.h"

#include <algorithm>
#include <cstdlib>
#include <string>

#include "DataBase.h"
#include "Table.h"
#include "super.h"
#endif
#ifndef _FILE_H_
#define _FILE_H_
#include "file.h"
#endif
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
_file* BackTracking::backTrackingFile =
    new _file(Log::nowData(), type::_TYPE_BACK);
BackTracking::BackTracking() {}
BackTracking::~BackTracking() { delete backTrackingFile; }
void BackTracking::backTrackingFileState() {
  if (Log::nowData() == backTrackingFile->returnName()) {
    return;
  } else {
    delete backTrackingFile;
    backTrackingFile = new _file(Log::nowData(), type::_TYPE_BACK, true);
    BackTracking::init();
  }
}
void BackTracking::add(std::string value, int ptr) {
  _file* tmpBT = new _file(backTrackingFile->returnName(), type::_TYPE_BACK);
  vstring tmpdata;
  tmpBT->readline(tmpdata);
  int newNumber = std::atoi(tmpdata[2].c_str());  //< part 3>
  std::string newNumbertoString = std::to_string(newNumber);
  std::string str_inputPtr =
      std::to_string(std::atoi(tmpdata[1].c_str()) + tmpdata[0].size() + ptr +
                     tmpdata[2].size());  //下一行的文件指针
  backTrackingFile->write(tmpdata[0] + " " + value + " " + newNumbertoString,
                          type_mode::WRITEBUFF_MODE_APP);
  tmpBT->setWriteSeek(-1);
  tmpBT->write(
      tmpdata[1] + " " + str_inputPtr + " " + std::to_string(newNumber + 1),
      type_mode::WRITEBUFF_MODE_IN_OUT);
  delete tmpBT;
}
void BackTracking::BackTrackingForRecoverDatabase(std::string DBID) {
  backTrackingFileState();
  DataBase tmpdatabase(DBID);
  vstring tableName;
  vstring tableline;
  vstring saveTheFirstLine;
  tmpdatabase.openDirReturnFileName(tableName);
  for (auto& table : tableName) {
    Table tmp(DBID + "/" + table, type::_TYPE_TABLE);
    tmp.readline(tableline);
    saveTheFirstLine = tableline;
    while (tmp.readline(tableline)) {
      BackTracking::BackTrackingForInsertDatabaseTable(DBID, table, tableline);
    }
    BackTracking::BackTrackingForInsertDatabaseTable(DBID, table,
                                                     saveTheFirstLine);
    std::vector<std::string>().swap(saveTheFirstLine);
    BackTrackingForCreateDatabaseTable(DBID, table);
  }
  BackTrackingForCreateDatabase(DBID);
}
void BackTracking::BackTrackingForCreateDatabase(std::string DBID) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::创建数据库) + " " + DBID,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::创建数据库] +
          DBID.size() + 4);  //三个空格一个\n
}
void BackTracking::BackTrackingForCreateDatabaseTable(std::string DBID,
                                                      std::string TBID) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::创建数据库表) + " " + DBID +
          " " + TBID,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::创建数据库表] +
          DBID.size() + TBID.size() + 5);  // 4个空格一个\n
}
void BackTracking::BackTrackingForCreateUser(std::string UserName,
                                             std::string Password) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::创建用户) + " " + UserName +
          " " + Password,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::创建用户] +
          UserName.size() + Password.size() + 5);  // 4个空格一个\n
}
void BackTracking::BackTrackingForCreateManager(std::string UserName,
                                                std::string Password) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::创建管理员) + " " + UserName +
          " " + Password,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::创建管理员] +
          UserName.size() + Password.size() + 5);  // 4个空格一个\n
}
void BackTracking::BackTrackingForRecoverDatabaseTable(std::string DBID,
                                                       std::string TBID) {
  backTrackingFileState();
  Table table(DBID + "/" + TBID, type::_TYPE_TABLE);
  vstring tableline;
  table.readline(tableline);
  vstring tableTheFirstLine = tableline;
  while (table.readline(tableline)) {
    BackTracking::BackTrackingForInsertDatabaseTable(DBID, TBID, tableline);
  }
  BackTracking::BackTrackingForInsertDatabaseTable(DBID, TBID,
                                                   tableTheFirstLine);
  BackTracking::BackTrackingForCreateDatabaseTable(DBID, TBID);
}
void BackTracking::BackTrackingForDeleteDatabase(std::string DBID) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::删除数据库) + " " + DBID,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::删除数据库] +
          DBID.size() + 4);  //三个空格一个\n
}
void BackTracking::BackTrackingForDeleteDatabaseTable(std::string DBID,
                                                      std::string TBID) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::删除数据库表) + " " + DBID +
          " " + TBID,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::删除数据库表] +
          DBID.size() + TBID.size() + 5);  //四个空格一个\n
}
void BackTracking::BackTrackingForDeleteUser(std::string UserName) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::删除用户) + " " + UserName,
      BackTrackingCommandToInt[删除用户] + UserName.size() +
          4);  //两个空格一个\n
}
void BackTracking::BackTrackingForDeleteManager(std::string UserName) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::删除管理员) + " " + UserName,
      BackTrackingCommandToInt[删除管理员] + UserName.size() +
          4);  //三个空格+一个\n
}
void BackTracking::BackTrackingForInsertColDatabaseTable(std::string DBID,
                                                         std::string TBID,
                                                         vstring ColData) {
  backTrackingFileState();
  std::string data;
  int spaceAndDataSize = -1;
  for (auto& tmp : ColData) {
    data += " " + tmp;
    spaceAndDataSize += tmp.size() + 1;
  }
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::插入列数据库表) + " " + DBID +
          " " + TBID + data,
      BackTrackingCommandToInt[插入列数据库表] + DBID.size() + TBID.size() +
          spaceAndDataSize + 6);
}
void BackTracking::BackTrackingForDeleteRowDatabaseTable(std::string DBID,
                                                         std::string TBID,
                                                         std::string Row) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::删除行数据库表) + " " + DBID +
          " " + TBID + " " + Row,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::删除行数据库表] +
          DBID.size() + TBID.size() + Row.size() + 6);
}
void BackTracking::BackTrackingForInsertDatabaseTable(std::string DBID,
                                                      std::string TBID,
                                                      vstring insertData) {
  backTrackingFileState();
  std::string data;
  int spaceAndDataSize = -1;
  for (auto& tmp : insertData) {
    data += " " + tmp;
    spaceAndDataSize += tmp.size() + 1;
  }
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::插入数据库表) + " " + DBID +
          " " + TBID + data,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::插入数据库表] +
          DBID.size() + TBID.size() + spaceAndDataSize + 6);
}
void BackTracking::BackTrackingForSetViewDatabaseTable(std::string DBID,
                                                       std::string TBID,
                                                       std::string User,
                                                       vstring viewData) {
  backTrackingFileState();
  std::string data;
  int spaceAndDataSize = -1;
  for (auto& tmp : viewData) {
    data += " " + tmp;
    spaceAndDataSize += tmp.size() + 1;
  }
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::设置视图数据库表) + " " + DBID +
          " " + TBID + " " + User + data,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::设置视图数据库表] +
          DBID.size() + TBID.size() + User.size() + spaceAndDataSize + 7);
}
void BackTracking::BackTrackingForSetIndexDatabaseTable(std::string DBID,
                                                        std::string TBID,
                                                        std::string index) {
  backTrackingFileState();
  add(std::to_string(TYPE_BACKTRACKING_COMMAND::设置索引数据库表) + " " + DBID +
          " " + TBID + " " + index,
      BackTrackingCommandToInt[TYPE_BACKTRACKING_COMMAND::设置索引数据库表] +
          DBID.size() + TBID.size() + index.size() + 6);
}
void BackTracking::BackTrackingForShow(std::string data) {
  _file BackFile(data, type::_TYPE_BACK);
  vstring tmpbuff;
  BackFile.readline(tmpbuff);
  if (tmpbuff.size() != 3) {
    return;
  }
  int number = std::atoi(tmpbuff[2].c_str());
  //测试回溯指令集
  /* { */
  /*   std::cout << BackFile.returnReadFileBuff().tellg() << "is "; */
  /*   while (BackFile.readline(tmpbuff)) { */
  /*     for (auto& x : tmpbuff) { */
  /*       std::cout << " " << x; */
  /*     } */
  /*     std::cout << std::endl; */
  /*     std::cout << BackFile.returnReadFileBuff().tellg() << "is "; */
  /*   } */
  /*   return; */
  /* } */
  vvstring tmp;
  BackFile.setReadSeek(std::atoi(tmpbuff[0].c_str()));
  std::cout << "回溯点 回溯指令\n";
  while (BackFile.readline(tmpbuff)) {
    if (tmpbuff[0] == "-1") {
      break;
    }
    if (!dataClear(tmpbuff, tmp)) {
      return;
    }
    std::cout << number - std::atoi(tmp[3][0].c_str()) << " "
              << BackTrackingCommandToString[(
                     TYPE_BACKTRACKING_COMMAND)std::atoi(tmp[1][0].c_str())]
              << " ";
    for (auto& str : tmp[2]) {
      std::cout << " " << str;
    }
    std::cout << std::endl;
    if (BackFile.returnWriteFileBuff().eof()) {
      break;
    }
    BackFile.setReadSeek(std::atoi(tmpbuff[0].c_str()));
  }
}
bool BackTracking::dataClear(revstring data, vvstring& returnData) {
  if (data.size() < 4) {
    return false;
  }
  std::vector<std::vector<std::string>>().swap(returnData);
  returnData.push_back({data[0]});  //上一行的文件行指针
  returnData.push_back({data[1]});  //指令
  int size = data.size() - 1;
  vstring partdata;
  for (int a = 2; a < size; ++a) {
    partdata.push_back(data[a]);
  }
  returnData.push_back(partdata);      //数据
  returnData.push_back({data[size]});  // 回溯点
  return true;
}
void BackTracking::init() {
  _file BackFile(Log::nowData(), type::_TYPE_BACK);
  BackFile.write(回溯文件初始化首行字符串, type_mode::WRITEBUFF_MODE_APP);
  BackFile.write(回溯文件初始化次行字符串, type_mode::WRITEBUFF_MODE_APP);
}
void BackTracking::Clear() {
  backTrackingFile->remove();
  backTrackingFile = new _file("TMD", type::_TYPE_BACK);
}

void BackTracking::BackTrackingForExecute(std::string date,
                                          int backTrackingPoint) {
  _file backTrackingFile(date, type::_TYPE_BACK);
  if (!backTrackingFile.isExist()) {
    return;
  }
  vstring readlineData;
  vvstring clearData;
  backTrackingFile.readline(readlineData);
  int max_number = std::atoi(readlineData[2].c_str());
  backTrackingFile.setReadSeek(std::atoi(readlineData[0].c_str()));
  while (backTrackingFile.readline(readlineData)) {
    dataClear(readlineData, clearData);
    if (backTrackingPoint > max_number - std::atoi(clearData[1][0].c_str())) {
      break;
    }
    aidForExecute(std::atoi(clearData[1][0].c_str()), clearData[2]);
    backTrackingFile.setReadSeek(
        std::atoi(readlineData[readlineData.size() - 1].c_str()));
  }
}
void BackTracking::aidForExecute(int command,vstring executeData){

}
