/*
 * @Description: TMDSQL语言的设计与实现
 * @Autor: TMD
 * @Date: 2022-11-01 09:02:00
 * @LastEditTime: 2022-11-05 17:51:09
 */
#ifndef _SET_
#define _SET_
#include <set>
#endif
#ifndef _MAP_
#define _MAP_
#include <map>
#endif      
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif

using namespace std;
/***
创建 数据库 XXX;
选择 数据库 XXX;
删除 数据库 XXX;
选择 表 XXX;
创建 表 XXX;
删除 表 XXX;
*/
class shell{
public:
  shell();
  int readStatus();
private:
  set<string> _GBKstatus;
  map <string,int> _binaryStatus;
  string strBuff;
  vector<vector<string>> arraybuff;
};