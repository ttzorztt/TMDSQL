/**
 * @file super.h
 * @brief 维护一些公共静态函数和变量
 * @author TMD
 * @date 2022-11-07
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
#include <unordered_map>
#endif
#ifndef _UNORDERED_SET_
#define _UNORDERED_SET_
#include <unordered_set>
#endif
typedef std::vector<std::string> vstring;
typedef std::vector<std::string>& revstring;
typedef std::vector<std::vector<std::string>> vvstring;
typedef std::vector<std::vector<std::string>>& revvstring;
typedef std::vector<int> vint;
typedef std::vector<int>& revint;
typedef int POINTER;
typedef int MODE;
typedef int INDEX;
#define _databaseAndTablePath "./data/database/"
#define _indexPath "./data/index/"
#define _PCBPath "./data/PCB/"
#define _PathForUserData "./data/User/"
#define _PathForLog "./data/Log/"
#define _SQLPath "./data/SQL/"
#define _ViewPath "./data/view/"
#define _TruePathForUserData "/data/User/pd"
#define _BackPath "./data/Back/"
#define CACHEPOLL 10

#define 回溯文件初始化首行字符串 \
  "41 46 1                                 "  //留有空格的目的是为了给此处修改留有字节
#define 回溯文件首行字符数 40
#define 回溯文件初始化次行字符串 "-1 0"  //结束位

enum TYPE_BACKTRACKING_COMMAND {
  创建用户,          // 0
  创建管理员,        // 1
  删除数据库,        // 2
  删除数据库表,      // 3
  删除用户,          // 4
  删除管理员,        // 5
  删除行数据库表,    // 6
  插入列数据库表,    // 7
  插入数据库表,      // 8
  设置视图数据库表,  // 9
  设置索引数据库表,  // 10
  创建数据库,        // 11
  创建数据库表       // 12
};
std::unordered_map<TYPE_BACKTRACKING_COMMAND,
                   int> static BackTrackingCommandToInt = {
    {创建用户, 1},         {创建管理员, 1},       {删除数据库, 1},
    {删除用户, 1},         {删除数据库表, 1},     {删除管理员, 1},
    {删除行数据库表, 1},   {插入列数据库表, 1},   {插入数据库表, 1},
    {设置视图数据库表, 1}, {设置索引数据库表, 2}, {创建数据库, 2},
    {创建数据库表, 2}};
std::unordered_map<TYPE_BACKTRACKING_COMMAND,
                   std::string> static BackTrackingCommandToString = {
    {创建用户, "创建 用户"},
    {创建管理员, "创建 管理员"},
    {删除数据库, "删除 数据库"},
    {删除用户, "删除 用户"},
    {删除数据库表, "删除 数据库 表"},
    {删除管理员, "删除 管理员"},
    {删除行数据库表, "删除 行 数据库 表"},
    {插入列数据库表, "插入 列 数据库 表"},
    {插入数据库表, "插入数据库表"},
    {设置视图数据库表, "设置 视图 数据库 表"},
    {设置索引数据库表, "设置 索引 数据库 表"},
    {创建数据库, "创建 数据库"},
    {创建数据库表, "创建 数据库 表"}};
// 权限
enum TYPE_POWER {
  ROOT,     // 超级管理员
  Manager,  // 管理员
  NORMAL,   // 普通用户
  NONE      //未登录
};
enum keyboard { UP, DOWN, Chinese };
enum TYPE_CID {
  退出,
  创建,
  数据库,
  删除,
  选择,
  登录,
  显示,
  插入,
  查询,
  表,
  用户,
  管理员,
  执行,
  设置,
  索引,
  视图,
  行,
  列,
  回溯,
  清理
};
typedef std::vector<TYPE_CID> vCID;
std::unordered_map<std::string, TYPE_CID> static HashMapStringToCID = {
    {"退出", 退出}, {"创建", 创建}, {"数据库", 数据库}, {"删除", 删除},
    {"选择", 选择}, {"登录", 登录}, {"显示", 显示},     {"插入", 插入},
    {"查询", 查询}, {"表", 表},     {"用户", 用户},     {"管理员", 管理员},
    {"执行", 执行}, {"设置", 设置}, {"索引", 索引},     {"视图", 视图},
    {"列", 列},     {"行", 行},     {"回溯", 回溯},     {"清理", 清理}};
std::unordered_map<TYPE_CID, std::string> static HashMapCIDToString = {
    {退出, "退出"}, {创建, "创建"}, {数据库, "数据库"}, {删除, "删除"},
    {选择, "选择"}, {登录, "登录"}, {显示, "显示"},     {插入, "插入"},
    {查询, "查询"}, {表, "表"},     {用户, "用户"},     {管理员, "管理员"},
    {执行, "执行"}, {设置, "设置"}, {索引, "索引"},     {视图, "视图"},
    {列, "列"},     {行, "行"},     {回溯, "回溯"},     {清理, "清理"}};
//无法登录原因
enum TYPE_LOGIN_ERROR { 密码错误, 帐号不存在, 未登录 };
enum type {
  _TYPE_NONE,                   // 默认，留给传入真实路径的type
  _TYPE_TABLE,                  //普通文件，即表
  _TYPE_DATABASE,               //目录，即数据库
  _TYPE_CREATE_INDEX_DATABASE,  // 创建index目录下的数据库文件夹
  _TYPE_INDEX_TABLE,            // 索引下的表
  _TYPE_CREATE_LOCK_DATABASE,   //创建lock下的数据库文件夹
  _TYPE_PCB,                    // PCB的地址
  _TYPE_CREATE_PCB_DATABASE,    // 创建PCB下的数据库文件
  _TYPE_USERDATA,               //用户数据
  _TYPE_LOG,                    // LOG文件
  _TYPE_VIEW,                   //视图文件
  _TYPE_BACK                    //回溯文件
};
// 模式
enum type_mode {
  READBUFF_MODE,  //每次写入前寻位到流结尾
  WRITEBUFF_MODE_TRUNC,
  WRITEBUFF_MODE_APP,
  WRITEBUFF_MODE_IN_OUT,
  DEFAULT
};
// 执行错误的原因
enum TYPE_ERROR_CASE {
  顺利执行,
  键入不存在的关键字,
  键入违规字符,
  登录帐号错误,
  登录密码错误,
  无法选择不存在的数据库,
  未登录拒绝执行,
  普通用户违规操作,
  未选择数据库越级选择表,
  已选择的数据库中不存在目标表,
  第一个关键字错误,
  第二个关键字错误,
  SQL文件未找到,
  编译错误,
  创建已存在的用户,
  创建已存在的管理员,
  管理员违规操作,
  表已存在无法创建,
  数据库已存在无法创建,
  表不存在无法删除,
  数据库不存在无法删除,
  目标用户不存在无法删除,
  目标管理员不存在无法删除,
  输入非确定指令取消,
  数据库不存在无法插入数据,
  表不存在无法插入数据,
  表不存在无法查找数据,
  数据库不存在无法查找数据,
  表不存在无法显示数据,
  数据库不存在无法显示数据,
  未选择表,
  不存在该列,
  不存在该行,
  回溯文件不存在
};
static std::unordered_set<char> checkErrorName{
    '`', '~', '!',  '@',  '#', '$', '%', '^', '&', '*', '(',
    ')', '_', '-',  '=',  '+', '[', ']', '{', '}', '|', '\\',
    ':', ';', '\'', '\"', ',', '<', '>', '?', '/'};

/**
 * @brief 维护一些基础静态函数
 */
class _super {
 protected:
  //名字如果是表则需要加数据库名根据名字中是否有 '/'判断是数据库名或表名
  std::string name;

 public:
  virtual bool create();
  virtual bool remove();
  virtual int returnCount();
  virtual bool isExist();
  /**
   * @brief 不同操作系统下创建文件夹
   *
   * @param  string path 路径
   *
   * @return 创建成功返回True，否则返回false
   */
  bool static createDir(std::string path);
  /**
   * @brief 返回类型
   *
   * @return 返回类型
   */
  type returnType();
  /**
   * @brief 返回名字
   *
   * @return 返回名字
   */
  std::string returnName();
  /**
   * @brief 拷贝构造函数
   *
   * @param  super& copy 拷贝值
   * @param type style 类型 {file:表,dir:数据库,index:索引,lock:锁}
   */
  _super(_super& copy);
  /**
   * @brief 构造函数
   *
   * @param  string name 名字
   */
  _super(std::string name);
  /**
   * @brief 析构函数
   */
  ~_super();

  /**
   * @brief 用空格或逗号分割开的 string 转换为 vector，
   *
   * @param  string str 字符串
   * @param  revstring vec 数组
   */
  void static stringToVector(const std::string& str, revstring vec);

  /**
   * @brief <static> 以App的方式写入字符串
   *
   * @param string name 路径+名字
   * @param string& str 写入的字符串
   * @return True写入正确,False 写入失败
   */
  bool static writeFile(std::string Name, const std::string& str);
  /**
   * @brief 分离数据库名和表名
   *
   * @param  string TableName 待分离的表名
   * @return vstring[0] 是数据库名，vstring[1]是表名
   */
  vstring static dispartDatabaseNameAndTableName(std::string TableName);
  /**
   * @brief <static> 判断指定文件或目录是否存在
   *
   * @param string Name 路径
   * @param type style 类型
   *
   * @return 若存在则返回True，否则返回False;
   */
  bool static isExist(std::string Name, type style);
  /**
   * @brief <static> 判断是否存在
   *
   * @param string truePath 真实路径
   *
   * @return 若存在则返回True，否则返回False
   */
  bool static isExist(std::string truePath);
  /**
   * @brief <static> 返回真实路径
   *
   * @param string name 名称
   * @param  type style 类型
   *
   * @return  底层路径
   */
  std::string static returnTruePath(std::string name, type style);
  /**
   * @brief 判断是否为数字
   *
   * @param  string& str 待检测字符串
   *
   * @return  返回真伪
   */
  int static stringToInt(std::string& str);
};
#endif
