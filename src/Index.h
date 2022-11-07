/*
 * @Description  : 封装索引操作
 * @Autor        : TMD
 * @Date         : 2022-11-07 22:13:43
 * @LastEditTime : 2022-11-07 22:47:58
 */
class _index
{
private:
  //当前打开的索引文件的数量
  static int count;
public:
    _index(/* args */);
    ~_index();
    virtual int returnCount();
}; 