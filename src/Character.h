/*
 * @Description  : 单例模式字符集获取
 * @Autor        : TMD
 * @Date         : 2022-12-18 10:35:56
 * @LastEditTime : 2022-12-19 17:03:43
 */
#ifndef _CHARACTER_
#define _CHARACTER_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _MAP_
#define _MAP_
#include <unordered_map>
#endif

class Character {
 private:
  //单例模式
  static Character charObj;
  // CID
  static std::unordered_map<std::string, int> HashMapCID;
  /**
   * @brief 构造函数
   * @return
   */
  Character();
  Character(const Character& obj) = delete;
  Character& operator=(const Character& obj) = delete;
 public:
  /**
   * @brief 单例模式的构造函数
   * @return
   */
  static Character& Create();
};
#endif