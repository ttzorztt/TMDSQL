#include <set>
#include <map>
#include <vector>
#include <string>
using namespace std;
/***
创建 数据库 XXX;
选择 数据库 XXX;
删除 数据库 XXX;
选择 表 XXX;
创建 表 XXX;
删除 表 XXX;
*/
class shell{
public:
  shell();
  int readStatus();
private:
  set<string> _GBKstatus;
  map <string,int> _binaryStatus;
  string strBuff;
  vector<vector<string>> arraybuff;
};