/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:43
 * @LastEditTime : 2022-11-09 19:04:27
 */
#ifndef _INDEX_
#define _INDEX_
class index
{
private:
  //当前打开的索引文件的数量
  static int count;
public:
    index(/* args */);
    ~index();
    virtual int returnCount();
}; 
#endif