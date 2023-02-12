/**
 * @file KeyboardInput.h
 * @brief 实时显示，解决中文显示问题
 * @author TMD
 * @version 1.3
 * @date 2023-02-12
 */
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
/**
 * @brief 键盘输入
 */
class KeyboardInput{
private:
public:
KeyboardInput();
~KeyboardInput();
/**
 * @brief 读入入口
 *
 * @Return 按下'\n'后的全部字符
 */
std::string static read();

KeyboardInput(const KeyboardInput& copy) = delete;
};
