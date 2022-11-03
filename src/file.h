#include <string>
#include <vector>
#include <fstream>
using namespace std;
/**
 * @author TMD
 * @brief 文件处理类
 */
class _file{
public:
/**
 * @brief 构造函数，传入文件路径
 * @param Path 文件路径
 */
  _file(string& Path);
/**
 * @brief 析构函数，释放并关闭文件 
 */
  ~_file();
/**
 * @brief 判断文件是否存在
 * @param filePath 文件路径
 * @return 若文件存在则返回True，否则返回False;
 */ 
bool static isExists(string filePath);
/**
 * @brief 以App的方式写入字符串
 * @param str 写入的字符串
 */
void writeFile(const string& str);
/**
 * @brief 以App的方式写入字符串
 * @param array vector<string>的类型数据写入数据库
*/
void  writeFile(const vector<string>& array);
/**
 * @brief 以行的形势读出数据
 * @return 将一行数据以空格的形式分开，并存储在vector中，然后返回。
*/
vector<string> readline();

private:
  // filePath是_file超类的文件路径
  string filePath;
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
};