/**
 * @file TablePCB.h
 * @brief 表PCB的声明
 * @author TMD
 * @version 1.3
 * @date 2022-11-20
 */
#ifndef _TABLEPCB_
#define _TABLEPCB_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _SUPER_H_
#define _SUPER_H_
#include "super.h"
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
// 文件指针
#define POINTER int
/**
 * @brief 对于表的一些TCB数据
 */
class TablePCB {
	public:
		// 文件
		_file file;
		// 指向文件结尾的文件指针
		POINTER endLineIndex;
		//行数
		int length;
		//索引
		int index;
		/**
		 * @brief 从文件中读取
		 */
		void readData();
		/**
		 * @brief 写入文件
		 */
		void writeData();
		/**
		 * @brief 初始化
		 */
		void init();

	public:
		/**
		 * @brief 文件名
		 *
		 * @return  返回文件名
		 */
		std::string returnName();
		/**
		 * @brief 设置文件结束指针
		 *
		 * @param  POINTER fileIndex 文件指针值
		 */
		void setEndLineIndex(POINTER fileIndex);

		/**
		 * @brief 设置文件结束指针
		 *
		 * @param  Table table 表对象
		 * @param  POINTER fileIndex 待设置的文件指针
		 */
		void static setEndLineIndex(Table table, POINTER fileIndex);
		/**
		 * @brief 设置索引
		 *
		 * @param  string tableName 表名
		 * @param  INDEX fileIndex 索引
		 */
		void static setIndex(std::string tableName, INDEX fileIndex);
		/**
		 * @brief 设置索引
		 *
		 * @param  INDEX fileIndex 索引
		 */
		void setIndex(INDEX fileIndex);
		/**
		 * @brief 文件结束指针
		 *
		 * @return 文件结束指针的值
		 */
		INDEX returnEndLineIndex();
		/**
		 * @brief 文件大小
		 *
		 * @return  文件大小的值
		 */
		std::string returnFileSize();
		/**
		 * @brief 返回索引
		 *
		 * @return  索引
		 */
		INDEX returnIndex();
		/**
		 * @brief 构造函数
		 *
		 * @param  string DBID 数据库名
		 * @param  string TBID 表名
		 */
		TablePCB(std::string DBID, std::string TBID);
		/**
		 * @brief 构造函数
		 *
		 * @param  string DBIDAndTBID 数据库+表名
		 */
		TablePCB(std::string DBIDAndTBID);
		/**
		 * @brief 构造函数
		 *
		 * @param  Table& table 表对象
		 */
		TablePCB(Table& table);
		/**
		 * @brief 析构函数
		 */
		~TablePCB();
		/**
		 * @brief 添加行数
		 */
		void addLength();
};
#endif
