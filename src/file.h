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
 * @brief 
 */
void writeFile(const string& str);
void  writeFile(const vector<string>& array);
vector<string> readline();

private:
  string filePath;
  ofstream writeFileBuff;
  ifstream readFileBuff;
  string lockPath;

  bool addLock();
  bool removeLock();
};