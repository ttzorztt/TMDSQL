/*
 * @Description  : 维护一些公共静态函数和变量
 * @Autor        : TMD
 * @Date         : 2022-11-07 10:28:08
 * @LastEditTime : 2022-11-09 22:05:36
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
const static std::string _tablePath = "../data/database/";
const static std::string _databasePath = "../data/database/";
const static std::string _indexPath = "../data/index/";
const static std::string _tableLockPath = "../data/lock/database/";
const static std::string _databaseLockPath = "../data/lock/";
// 封装一些文件或目录类型
enum type {
  _TYPE_TABLE,           //普通文件，即表
  _TYPE_DADABASE,            //目录，即数据库
  _TYPE_INDEX,          // 索引文件
  _TYPE_TABLE_LOCK,      // 表锁
  _TYPE_TADABLASE_LOCK  //数据库锁
};
/**
 * @brief 维护一些基础静态函数
 */
class _super {
 protected:
  //名字 
  //如果是表则需要加数据库名
  // 根据名字中是否有 '/'判断是数据库名或表名
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
  virtual type returnType();
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
   * @brief <static> 返回目录中所有文件名字，即数据库中表名
   * @param string truePath 路径
   * @return 以vector的形式返回
   */
  std::vector<std::string> static openDirReturnFileName(std::string truePath);
  /**
   * @brief <static> 以App的方式写入字符串
   * @param string name 路径+名字
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(std::string Name, const std::string& str);

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
  std::string static returnTruePath(std::string name,type style);
};
#endif