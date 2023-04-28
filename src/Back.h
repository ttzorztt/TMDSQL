#ifndef _BACK_
#define _BACK_
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
class Back {
 private:
 public:
  Back();
  ~Back();
  Back(const Back& copy) = delete;
  void BackForCreateUser(std::string UserName, std::string Password);
  void BackForCreateManager(std::string UserName, std::string Password);
  void BackForCreateDatabase(std::string DBID);
  void BackForCreateDatabaseTable(std::string DBID, std::string TBID);
  void BackForDeleteDatabase(std::string DBID);
  void BackForDeleteDatabaseTable(std::string DBID, std::string TBID);
  void BackForDeleteUser(std::string UserName);
  void BackForDeleteManager(std::string UserName);
  void BackForDeleteColDatabaseTable(std::string DBID, std::string TBID,
                                     int Col, revstring ColData);
  void BackForDeleteRowDatabaseTable(std::string DBID, std::string TBID,
                                     int Row, revstring RowData);
  void BackForInsertDatabaseTable(std::string DBID, std::string TBID,
                                  revstring insertData);
  void BackForSetViewDatabaseTable(std::string DBID, std::string TBID,
                                   revstring viewData);
  void BackForSetIndexDatabaseTable(std::string DBID, std::string TBID,
                                    int index);
};
#endif
