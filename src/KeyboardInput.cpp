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
#ifndef _LOG_H_
#define _LOG_H_
#include "Log.h"
#endif
#ifndef _MENUOUTPUT_H_
#define _MENUOUTPUT_H_
#include "menuOutput.h"
#endif
#ifndef _IOSTREAM_
#define _IOSTREAM_
#include <iostream>
#endif
KeyboardInput::KeyboardInput(){
#ifdef __linux__
	tcgetattr(0, &tms_old);
	tms_new = tms_old;
	tms_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tms_new);
#endif

}
KeyboardInput::~KeyboardInput(){
#ifdef __linux__
	tcsetattr(0, TCSANOW, &tms_old);
#endif
}
std::string KeyboardInput::read(shell& sh){
	std::string ret;
	std::string tmp = "执行 @SQL";
	int count = 2;
	unsigned char ch;
	termios tms_old,tms_new;
	tcgetattr(0, &tms_old);
	tms_new = tms_old;
	tms_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tms_new);
#ifdef __linux__
	while(1){
		ch = getchar();
		if(ch == '\n'){
			menuOutput::printPower(sh.ReturnPower());
			break;
		}else if(ch == 0x7F){
			/* std::cout << "\b\b\b"; */
		}else if(ch >= 0x80 && count){ //输入中文中的一部分，输出会乱码，跳过输出
			ret += ch;
			--count;
			continue;
		}
		for(int a = 0; a < ret.size(); ++a){
			std::cout << '\b' << ' ' <<'\b';
		}
		ret += ch;
		
		if(count == 0){
			count = 2;
		}
		std::cout << ret;
	}
	std::cout << "TMD" << std::endl;
	tcsetattr(0, TCSANOW, &tms_old);
#endif
	return ret;
}
