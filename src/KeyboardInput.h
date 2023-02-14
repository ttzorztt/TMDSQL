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
#ifdef __WIN32__
#ifndef _CONIO_
#define _CONIO_
#include <conio.h>
#endif
#endif
#ifdef __linux__
#ifndef _TERMIO_
#define _TERMIO_
#include <termio.h>
#endif
#endif
#ifndef _SHELL_H_
#define _SHELL_H_
#include "shell.h"
#endif
/**
 * @brief 键盘输入
 */
class KeyboardInput{
	private:
		termios tms_old,tms_new;
	public:
		KeyboardInput();
		~KeyboardInput();
		/**
		 * @brief 读入入口
		 *
		 * @param sh shell对象
		 *
		 * @Return 按下'\n'后的全部字符
		 */
		std::string static read(shell& sh);

		KeyboardInput(const KeyboardInput& copy) = delete;
};
