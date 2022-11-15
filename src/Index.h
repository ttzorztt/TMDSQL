/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:43
 * @LastEditTime : 2022-11-15 14:02:19
 */
#ifndef _INDEX_
#define _INDEX_
class Index 
{
private:
  //当前打开的索引文件的数量
  static int count;
public:
    Index(); 
    ~Index();
    virtual int returnCount();
}; 
#endif