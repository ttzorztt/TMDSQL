#ifndef _BACKTRACKING_
#define _BACKTRACKING_
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
class BackTracking {
 private:
	 void static add(std::string value,int ptr);
	 void static backTrackingFileState();
	 static _file* backTrackingFile;
 public:
  BackTracking();
  ~BackTracking();
  BackTracking(const BackTracking& copy) = delete;
  void static BackTrackingForCreateUser(std::string UserName, std::string Password);
  void static BackTrackingForCreateManager(std::string UserName, std::string Password);
  void static BackTrackingForCreateDatabase(std::string DBID);
  void static BackTrackingForCreateDatabaseTable(std::string DBID, std::string TBID);
  void static BackTrackingForDeleteDatabase(std::string DBID);
  void static BackTrackingForDeleteDatabaseTable(std::string DBID, std::string TBID);
  void static BackTrackingForDeleteUser(std::string UserName);
  void static BackTrackingForDeleteManager(std::string UserName);
  void static BackTrackingForDeleteColDatabaseTable(std::string DBID, std::string TBID,
                                     int Col, revstring ColData);
  void static BackTrackingForDeleteRowDatabaseTable(std::string DBID, std::string TBID,
                                     int Row, revstring RowData);
  void static BackTrackingForInsertDatabaseTable(std::string DBID, std::string TBID,
                                  revstring insertData);
  void static BackTrackingForSetViewDatabaseTable(std::string DBID, std::string TBID,
                                   revstring viewData);
  void static BackTrackingForSetIndexDatabaseTable(std::string DBID, std::string TBID,
                                    int index);
};
#endif
