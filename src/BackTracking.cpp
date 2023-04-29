#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_
#include "BackTracking.h"
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
_file* BackTracking::backTrackingFile = new _file(
    Log::nowData(), type::_TYPE_BACK, true, "0                     ");
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
    backTrackingFile = new _file(Log::nowData(), type::_TYPE_BACK,true,"0                     ");
  }
}
void BackTracking::add(std::string value, int ptr) {
  vstring tmpdata;
  backTrackingFile->readline(tmpdata);
  std::cout << tmpdata.size() << std::endl;
}
void BackTracking::BackTrackingForCreateDatabase(std::string DBID) {
  /* backTrackingFileState(); */
  /* add("删除 数据库 @" + DBID, 回溯删除数据库); */
}
