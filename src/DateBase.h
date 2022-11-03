#include "file.h"
#include <set>
#include <map>
using namespace std;

class DateBase: public _file{
  public:
  /**
   * @author TMD
   * @brief 构造创建数据库对象
   * @param path 数据库路径
  */

  DateBase(string path,string databasename);
  void Create();
  private:
  // status = 1为正常状态
  // status = 0为非正常状态
  int status;
  string datebasename;
};