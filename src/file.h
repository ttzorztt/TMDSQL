#include <string>
#include <vector>
#include <fstream>
using namespace std;
class _file{
public:
  _file(string& Path);
  ~_file();
bool isExists(string filePath);
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