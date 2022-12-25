/*
 * @Description  : TMDSQL语言的设计与实现
 * @Autor        : TMD
 * @Date         : 2022-11-01 09:02:00
 * @LastEditTime : 2022-12-25 16:05:41
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

class shell : public User {
 public:
 /**
  * @brief 登录
  * @param  string ID 帐号
  * @param  string password 密码
  * @return  
  */
 bool logn(std::string ID,std::string password);
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
  /**
   * @brief 输入删除后的操作
   * @param  revstring value value<string>数组
   * @return  
   */
  void toDelete(revstring value);
  /**
   * @brief 输入重命名后的操作
   * @param  revstring value value[string]数组
   * @return  
   */
  void toRename(revstring value);
  
 private:
 User user;
 // CID
  static std::unordered_map<std::string, int> HashMapCID;
};
#endif