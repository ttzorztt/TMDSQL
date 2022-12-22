/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2022-12-22 10:30:36
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
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _USER_H_
#define _USER_H_
#include "User.h"
#endif
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
  /**
   * @brief 输入创建后的操作
   * @param  revstring value string的数组
   * @return  
   */
  void toCreate(revstring value);
 private:
 User user;
 // CID
  static std::unordered_map<std::string, int> HashMapCID;
};
#endif