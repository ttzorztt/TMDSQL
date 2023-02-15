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
#include "super.h"
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
KeyboardInput::KeyboardInput(){}
KeyboardInput::~KeyboardInput(){}
void KeyboardInput::complexChar(std::string& str,std::string& ret,shell& sh){
	if(str[0] == 0x1B && str[1] == 0x5B){
		if(str[2] == 0x41 && sh.hasHistory()){ //UP
			/* ret = sh.prevHistory(); */
		}else if(str[2] == 0x42 && sh.hasHistory()){ //DOWN
			/* ret = sh.nextHistory(); */
		}else if(str[2] == 0x44){ //Left
		}else if(str[2] == 0x43){ //Right
}
		return;
	}
	ret += str;
}
/**
 * @name 待处理,代码混乱
 * @{ */
/**  @} */

std::string KeyboardInput::read(shell& sh){
	std::string ret;
<<<<<<< HEAD
	std::string complexch;
=======
	ret.resize(100);
>>>>>>> bda89eab628a63a865c02419b4d09cfa0a93fd4d
	int count = 2;
	bool add = false;
	char ch;
	termios tms_old,tms_new;
	tcgetattr(0, &tms_old);
	tms_new = tms_old;
	tms_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tms_new);
#ifdef __linux__
	while(1){
		add = true;
		ch = getchar();
<<<<<<< HEAD
		if(ch == '\n'){
=======
		if(ch == 0x38){ // UP
			ret = sh.prevHistory();
			add = false;
		}else if(ch == 0x40){ // DOWM
			ret = sh.nextHistory();
			add = false;
		}else 
			if(ch == '\n'){
>>>>>>> bda89eab628a63a865c02419b4d09cfa0a93fd4d
			break;
		}else if(ch == 0x7F && ret.size()){ //输入backspace
			add = false;
			if((unsigned int)ret[ret.size() - 1] >= 0x8000){ // 说明是中文
				ret.pop_back();
				ret.pop_back();
				ret.pop_back();
			}else{
				ret.pop_back();
			}
		}else if((unsigned int)ch >= 0x8000){ //输入中文中的一部分，输出会乱码，跳过输出
			complexch += ch;
			--count;
			if(count == 0){
				KeyboardInput::complexChar(complexch, ret, sh);
				count = 3;
				complexch = "";
				add = false;
			}else{
				continue;
			}
		}
<<<<<<< HEAD
		std::cout << "\r";
		std::cout << std::string(ret.size() + 20,' ');
		std::cout << "\r";
=======
		/* std::cout << "\r"; // 使得光标回到行首 */
		/* std::cout << std::string(ret.size() + 20,' '); */
		/* std::cout << "\r"; // 使得光标回到行首 */
		std::cout << "\033c";
>>>>>>> bda89eab628a63a865c02419b4d09cfa0a93fd4d
		menuOutput::printPower(sh.ReturnPower());
		if(add){
			ret += ch;
		}
		std::cout << ret;
	}
	tcsetattr(0, TCSANOW, &tms_old);
<<<<<<< HEAD
=======
	std::cout << "\033[?25h"; //显示光标
>>>>>>> bda89eab628a63a865c02419b4d09cfa0a93fd4d
#endif
	sh.addHistory(ret);
	return ret;
}
