/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2022-12-21 21:54:06
 */
#ifndef _SHELL_
#define _SHELL_
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _UNORDERED_MAP_
#define _UNORDERED_MAP_
#include <unordered_map>
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
/***
创建 数据库 XXX;
选择 数据库 XXX;
删除 数据库 XXX;
选择 表 XXX;
创建 表 XXX;
删除 表 XXX;
*/
enum TYPE_CID {
  退出,
  创建,
  数据库,
  删除,
  选择,
  重命名,
  登录,
  显示,
  插入,
  查询,
  表,
  普通用户,
  管理员
};
class shell {
 public:
  
  shell();
  ~shell();
  /**
   * @brief 读入数据
   * @param  string data 数据
   * @return 符合语法返回True，否则返回False
   */
  bool read(std::string data);
 private:
 // CID
  static std::unordered_map<std::string, int> HashMapCID;
  // vecBuff
  static std::vector<std::string> vecBuff;
};
#endif