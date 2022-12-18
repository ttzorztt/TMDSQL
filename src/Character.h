/*
 * @Description  : 单例模式字符集获取
 * @Autor        : TMD
 * @Date         : 2022-12-18 10:35:56
 * @LastEditTime : 2022-12-18 19:28:20
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
  static std::vector<std::string> value;
  static Character charObj;
  static int count;
  static std::unordered_map<std::string,int> HashMap;
  Character();
  Character(const Character& obj) = delete;
  Character& operator=(const Character& obj) = delete;
  void readData();
 public:
  static Character& Create();
  void static print();
  void static add(std::string x);
};
#endif