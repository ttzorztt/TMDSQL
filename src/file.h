#ifndef _VECTOR_
#define _VECTOR_
#include <vector>
#endif
#ifndef _STRING_
#define _STRING_
#include <string>
#endif
#ifndef _FSTREAM_
#define _FSTREAM_
#include <fstream>
#endif
#ifndef _DIRENT_H_
#define _DIRENT_H_
#include <dirent.h>
#endif
#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_
#include <sys/types.h>
#endif

using namespace std;
/**
 * @author TMD
 * @brief 封装一些对于文件或者目录操作的函数的类。包括创建删除文件或目录。文件的读写。以及读写锁的实现
 */
class _file{
public:
/**
 * @brief 构造函数，传入文件路径
 * @param name 文件路径
 */
  _file(string& name);
/**
 * @brief 析构函数，释放并关闭文件 
 */
  ~_file();
/**
 * @brief 判断指定文件是否存在
 * @param name 文件路径
 * @return 若文件存在则返回True，否则返回False;
 */ 
bool static isExist(string name);
/**
 * @brief 判断_file默认文件是否存在
 * @return 若文件存在则返回True，否则返回False;
*/
bool isExist();
/**
 * @brief 以App的方式写入字符串
 * @param str 写入的字符串
 * @return True写入正确,False 写入失败
 */
bool writeFile(const string& str);
/**
 * @brief 以App的方式写入字符串
 * @param Path 路径
 * @param array vector<string>的类型数据写入数据库
 * @return True写入正确,False 写入失败
*/
bool static writeFile(string Path, const vector<string>& array);
/**
 * @brief 以App的方式写入字符串
 * @param Path 路径
 * @param str 写入的字符串
 * @return True写入正确,False 写入失败
 */
bool static writeFile(string Path, const string& str);
/**
 * @brief 以App的方式写入字符串
 * @param array vector<string>的类型数据写入数据库
 * @return True写入正确,False 写入失败
*/
bool writeFile(const vector<string>& array);
/**
 * @brief 以行的形势读出数据
 * @return 将一行数据以空格的形式分开，并存储在vector中，然后返回。
*/
vector<string> readline();
/**
 * @brief 创建指定文件
 * @param path 需要创建的文件名字
 * @return True表示文件创造成功，False表示文件创造失败
*/
bool static createFile(string name);
/**
 * @brief 创建_file默认的文件
 * @return True表示文件创造成功，False表示文件创造失败
*/
bool createFile();

// private:
  // filePath是_file超类的文件路径
  string name;
  // writeFileBuff是写文件buff指针
  ofstream writeFileBuff;
  // readFileBuff是读文件buff指针
  ifstream readFileBuff;
  // lockPath是加锁文件
string lockPath;

  /**
   * @brief 加锁
   * @return 加锁成功则返回True，并意味着当前没有读写冲突， 加锁失败则返回False，并意味着当前存在读写冲突。
   */
  bool addLock();
  /**
   * @brief 删锁
   * @return 删锁成功则返回True，否则返回False。
   */
  bool removeLock();

  /**
   * @brief 判断文件是否存在并打开writebuff,若没有打开则打开，若已经打开，则啥也不干
   * @param need 希望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
  */
  bool writeBuffOpen(bool need);
  /**
   * @brief 判断文件是否存在打开readbuff,若没有打开则打开，若已经打开，则啥也不干
   * @param need 期望文件状态，True期望文件存在，False期望文件不存在
   * @return 文件状态为need，则返回True
  */
  bool readBuffOpen(bool need);

  /**
   * @brief 创建目录
   * @param dirName 创建目录名
   * @return 创建正常则返回True,否则返回False
   * 
  */
  bool static createDir(string dirName);
  /**
   * @brief 返回目录中所有文件名字，即数据库中表名
   * @param dirPath dir的路径
   * @return 以vector的形式返回
  */
  vector<string> static openDirReturnFileName(string dirPath);
    /**
   * @brief 返回目录(当前_file的name)中所有文件名字，即数据库中表名
   * @return 以vector的形式返回
  */
  vector<string> openDirReturnFileName();
  /**
   * @brief 删除文件
   * @param Path 删除文件所在路径
   * @return 如果正常删除，则返回True，否则返回False
  */
  bool static deleteFile(string Path);
  /**
   * @brief 删除_filezh中的默认文件
   * @return 如果删除正常，则返回True，否则返回False
  */
  bool deleteFile();
  bool deleteDir();
  bool static deleteDir(string Path);
};