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
    backTrackingFile =
        new _file(Log::nowData(), type::_TYPE_BACK, true, 回溯文件初始化字符串);
  }
}
void BackTracking::add(std::string value, int ptr) {
	_file * tmpBT = new _file(backTrackingFile->returnName(),type::_TYPE_BACK);
  vstring tmpdata;
  tmpBT->readline(tmpdata);
	delete tmpBT;
  int newNumber = std::atoi(tmpdata[tmpdata.size() - 1].c_str()) + 1;
  int oldptr = std::atoi(tmpdata[0].c_str());
	std::string inputString = "";
	inputString += std::to_string(oldptr + ptr);//oldptr是回溯文件首行所记录的最新下标，而ptr是该行指令正儿八经需要多大内存
	backTrackingFile->write({value},type_mode::WRITEBUFF_MODE_APP);
	backTrackingFile->write("TMD",type_mode::WRITEBUFF_MODE_APP);
}
void BackTracking::BackTrackingForCreateDatabase(std::string DBID) {
  backTrackingFileState();
  add("删除 数据库 @" + DBID, 回溯删除数据库);
}
