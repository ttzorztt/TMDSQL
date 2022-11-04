#include "file.h"
#include <set>
#include <map>
using namespace std;

class DateBase: public _file{
  public:
  /**
   * @author TMD
   * @brief 构造创建数据库对象
   * @param name 数据库路径
  */

  DateBase(string name);
  /**
   * @brief 创建数据库(底层就是创建文件夹)
  */
  bool create();
  private:
  // status = 1为正常状态
  // status = 0为非正常状态
  int status;
};