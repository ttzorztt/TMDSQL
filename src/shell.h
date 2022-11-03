
/***
创建 数据库 XXX;
选择 数据库 XXX;
删除 数据库 XXX;
选择 表 XXX;
创建 表 XXX;
删除 表 XXX;
*/

class shell{
publc:
  shell();
  int readStatus();

private:
  set<string> _GBKstatus;
  map<string,string> _binaryStatus;
  string strBuff;
  vector<vector<string>> arraybuff;
}