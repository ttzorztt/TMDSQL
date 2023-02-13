/**
 * @file KeyboardInput.cpp
 * @brief 键盘读入
 * @author TMD
 * @version 1.3
 * @date 2023-02-12
 */
#ifndef _KEYBOARDINPUT_H_
#define _KEYBOARDINPUT_H_
#include "KeyboardInput.h"
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
std::string KeyboardInput::read(){
	std::string ret;
	std::vector<char> vchar;
	std::string tmp = "执行 @SQL";
	int count = 0;
	char ch;
#ifdef __linux__
	termios tms_old, tms_new;
	tcgetattr(0, &tms_old);
	tms_new = tms_old;
	tms_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tms_new);
#endif
	return ret;
}
