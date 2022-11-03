#include "file.h"
using namespace std;

class DateBase: public _file{
  public:
  /**
   * @author TMD
   * @brief 构造创建数据库对象
   * @param path 数据库路径
  */
  DateBase(string path);
  private:

};






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
  void readStatus();
private:
  enum status = {"创建","数据库","删除","选择","表"};
}