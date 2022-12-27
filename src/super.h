/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:08
 * @LastEditTime : 2022-12-27 16:15:36
 */
#ifndef _SUPER_
#define _SUPER_
#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <dirent.h>
#endif
#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_
#include <sys/stat.h>
#endif
#ifndef _UNISTD_H_
#define _UNISTD_H_
#include <unistd.h>
#endif
#ifndef _UNORDERED_MAP_
#define _UNORDERED_MAP_
#include "unordered_map"
#endif
#ifndef _UNORDERED_SET_
#define _UNORDERED_SET_
#include <unordered_set>
#endif
typedef std::vector<std::string> vstring;
typedef std::vector<std::string>& revstring;
typedef std::vector<int> vint;
typedef std::vector<int>& revint;
typedef int POINTER;
typedef int MODE;
#define UserVectorBuff vstring vectorbuff(4);
//"../data/database/"
const static std::string _tablePath = "../data/database/";
//"../data/database/"
const static std::string _databasePath = "../data/database/";
//"../data/index/"
const static std::string _indexPath = "../data/index/";
//"../data/lock/"
const static std::string _tableLockPath = "../data/lock/";
//"../data/lock/"
const static std::string _databaseLockPath = "../data/lock/";
//"../data/log/"
const static std::string _logPath = "../data/log/";
//"../data/PCB/"
const static std::string _PCBPath = "../data/PCB/";
// 封装一些文件或目录类型
const static std::string _TruePathForUserData = "../data/User/pd";
// 权限
enum TYPE_POWER {
  ROOT,     // 超级管理员
  Manager,  // 管理员
  NORMAL,   // 普通用户
  NONE      //未登录
};
static std::unordered_map<TYPE_POWER, int> powerPR{{TYPE_POWER::NORMAL, 11},
                                                   {TYPE_POWER::Manager, 12},
                                                   {TYPE_POWER::ROOT, 16},
                                                   {TYPE_POWER::NONE, 13}};
static std::unordered_set<char> checkErrorName{
    '`', '~', '!',  '@',  '#', '$', '%', '^', '&', '*', '(',
    ')', '_', '-',  '=',  '+', '[', ']', '{', '}', '|', '\\',
    ':', ';', '\'', '\"', ',', '<', '>', '.', '?', '/'};
enum TYPE_CID {
  退出,
  创建,
  数据库,
  删除,
  选择,
  重命名,
  登录,
  显示,
  插入,
  查询,
  表,
  普通用户,
  管理员
};
typedef std::vector<TYPE_CID> vCID;
enum type {
  _TYPE_TABLE,                  //普通文件，即表
  _TYPE_DATABASE,               //目录，即数据库
  _TYPE_CREATE_INDEX_DATABASE,  // 创建index目录下的数据库文件夹
  _TYPE_INDEX_TABLE,            // 索引下的表
  _TYPE_TABLE_LOCK,             // 表锁
  _TYPE_DATABASE_LOCK,          //数据库锁
  _TYPE_CREATE_LOCK_DATABASE,   //创建lock下的数据库文件夹
  _TYPE_PCB,                    // PCB的地址
  _TYPE_CREATE_PCB_DATABASE,    // 创建PCB下的数据库文件
  _TYPE_USERDATA,
};
enum type_mode {
  READBUFF_MODE,  //每次写入前寻位到流结尾
  WRITEBUFF_MODE_TRUNC,
  WRITEBUFF_MODE_APP,
  DEFAULT
};

/**
 * @brief 维护一些基础静态函数
 */
class _super {
 protected:
  /**
   * 名字
   * 如果是表则需要加数据库名
   * 根据名字中是否有 '/'判断是数据库名或表名
   */
  std::string name;

 public:
  virtual bool create();
  virtual bool remove();
  virtual int returnCount();
  virtual bool isExist();
  /**
   * @brief 返回类型
   * @return 返回类型
   */
  type returnType();
  /**
   * @brief 返回名字
   * @return 返回名字
   */
  std::string returnName();
  /**
   * @brief 拷贝构造函数
   * @param  super& copy 拷贝值
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   * @return
   */
  _super(_super& copy);
  /**
   * @brief 构造函数
   * @param  string name 名字
   * @return
   */
  _super(std::string name);
  /**
   * @brief 析构函数
   */
  ~_super();

  /**
   * @brief 用空格或逗号分割开的 string 转换为 vector，
   * @param  string str 字符串
   * @param  revstring vec 数组
   * @return
   */
  void static stringToVector(const std::string& str, revstring vec);
  /**
   * @brief <static> 返回目录中所有文件名字，即数据库中表名
   * @param string truePath 路径
   * @return 以vector的形式返回
   */
  vstring static openDirReturnFileName(std::string truePath);
  /**
   * @brief <static> 以App的方式写入字符串
   * @param string name 路径+名字
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(std::string Name, const std::string& str);
  /**
   * @brief 分离数据库名和表名
   * @param  string TableName 待分离的表名
   * @return vstring[0] 是数据库名，vstring[1]是表名
   */
  vstring static dispartDatabaseNameAndTableName(std::string TableName);
  /**
   * @brief <static> 判断指定文件或目录是否存在
   * @param string Name 路径
   * @param type style 类型
   * @return 若存在则返回True，否则返回False;
   */
  bool static isExist(std::string Name, type style);
  /**
   * @brief <static> 判断是否存在
   * @param string truePath 真实路径
   * @return 若存在则返回True，否则返回False
   */
  bool static isExist(std::string truePath);
  /**
   * @brief <static> 返回真实路径
   * @param string name 名称
   * @param  type style 类型
   * @return  底层路径
   */
  std::string static returnTruePath(std::string name, type style);
};
#endif