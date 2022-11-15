/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:43
 * @LastEditTime : 2022-11-15 17:43:33
 */
#ifndef _INDEX_
#define _INDEX_
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _TABLE_H_
#define _TABLE_H_
#include "Table.h"
#endif
class Index 
{
private:
  //当前打开的索引文件的数量
  static int count;
public:
    /**
     * @brief 
     * @return  
     */
    Index(); 
    /**
     * @brief 
     * @return  
     */
    ~Index();
    /**
     * @brief 
     * @return  
     */
    virtual int returnCount();
    /**
     * @brief 更新索引
     * @param  string tableName 表名
     * @return  
     */
    void static update(std::string tableName);
    /**
     * @brief 更新索引
     * @param  Table table 表对象
     * @return  
     */
    void static update(Table table);
    
}; 
#endif