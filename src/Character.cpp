/*
 * @Description  : 字符集获取
 * @Autor        : TMD
 * @Date         : 2022-12-18 10:36:09
 * @LastEditTime : 2022-12-18 19:30:38
 */
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "Character.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
Character Character::charObj;
int Character::count = 0;
std::vector<std::string> Character::value;
Character::Character() {
  
}
Character Character::charObj;
int Character::count = 0;
std::vector<std::string> Character::value;
Character& Character::Create() {
  return charObj;
}
void Character::add(std::string x){
  value.push_back(x);
}
void Character::print(){
  std::cout << value.size();
}

void maa(){
  Character::add("xxx");
  Character::print();
}
int main(int argc, char const* argv[]) {
  return 0;
}
