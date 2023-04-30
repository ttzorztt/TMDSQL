/**
 * @file BackTracking.cpp
 * @brief 回溯类,第一个字符是上一行的指针，第二个字符是序号。
 * @author TMD
 * @date 2023-04-29
 */
#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_
#include "BackTracking.h"

#include <cstdlib>
#include <string>

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
BackTracking::BackTracking() {
  if (!backTrackingFile->isExist()) {
    backTrackingFile->create();
  }
}
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
  /* int oldptr = std::atoi(tmpdata[0].c_str());  //上一条指令的行索引 */
  std::string str_inputPtr =
      std::to_string(std::atoi(tmpdata[1].c_str()) + tmpdata[0].size() + ptr +
                     tmpdata[2].size());  //下一行的文件指针
  backTrackingFile->write(tmpdata[0] + " " + value + " " + newNumbertoString,
                          type_mode::WRITEBUFF_MODE_APP);
  tmpBT->setWriteSeek(-1);
  std::cout << tmpBT->returnWriteTell() << std::endl;
  tmpBT->write(
      tmpdata[1] + " " + str_inputPtr + " " + std::to_string(newNumber + 1),
      type_mode::WRITEBUFF_MODE_APP);
  delete tmpBT;
}
void BackTracking::BackTrackingForCreateDatabase(std::string DBID) {
  backTrackingFileState();
  add("删除 数据库 @" + DBID, 回溯删除数据库 + DBID.size() + 2);  //加两个空格
}
void BackTracking::test_Read() {
  _file BackFile(Log::nowData(), type::_TYPE_BACK);
  vstring tmpbuff;
  BackFile.readline(tmpbuff);
}
void BackTracking::init() {
  _file BackFile(Log::nowData(), type::_TYPE_BACK);
  BackFile.write(回溯文件初始化首行字符串, type_mode::WRITEBUFF_MODE_APP);
  BackFile.write(回溯文件初始化次行字符串, type_mode::WRITEBUFF_MODE_APP);
}
