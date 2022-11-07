# TMDSQL
## 总体设计思路
- 无界面全终端操作方式,前端具有shell解析。并直接运行TMDSQL语句。
- 自定义中文TMDSQL语言,并实现该语言的语法检查,语义检查,转化为底层的C++代码并操作数据库。
- 创建数据库和数据库表,增删改查更新基本操作。
- 多用戶登录,读写上锁,视图层实现。
- 使用双级缓存进行数据读取。使得读取速度加快。
- 主键采取聚簇索引的底层形式。并采取缓冲形式进行查询速度的优化。

## src目录及其主要功能介绍
### `dir.h && dir.cpp`
  > 主要实现目录操作，在内核中，目录对应于数据库，封装_dir类。
  ```c++
  class _dir {
  public:
  /**
  * @brief dir类中的构造函数，
  * @param string dirPath 目录路径
  * @return
  */
  _dir(string dirPath);
  /**
  * @brief 拷贝构造函数
  * @param  _dir& copy 拷贝值
  * @return  
  */
  _dir(_dir& copy);
  /**
  * @brief <static> 返回目录中所有文件名字，即数据库中表名
  * @param string dirPath dir的路径
  * @return 以vector的形式返回
  */
  vector<string> static openDirReturnFileName(string dirPath);
  /**
  * @brief <static>创建目录
  * @param  string dirName 创建目录名
  * @return 正确创建则返回true，否则返回false
  */
  bool static createDir(string dirName);
  /**
  * @brief <static>删除目录
  * @param string Path 删除目录的路径
  * @return 如果删除正常，则返回True，否则返回False
  */
  bool static deleteDir(string Path);
  /**
  * @brief 返回路径
  * @return 返回DirPath
  */
  string returnDirPath();
  /**
  * @brief <static> 判断指定文件是否存在
  * @param string name 文件路径
  * @return 若文件存在则返回True，否则返回False;
  */
  bool static isExist(string name);
  string dirPath;
  /**
  * @brief 删除默认目录 dirPath
  * @return 如果删除正常，则返回True，否则返回False
  */
  bool deleteDir();
  /**
  * @brief 返回默认目录中所有文件名字，即数据库中表名
  * @return 以vector的形式返回
  */
  vector<string> openDirReturnFileName();
  };
  ```
### `file.h && file.cpp`
  > 封装文件操作类_file,在内核中，文件对应表。
  ```c++
  /**
  * @brief
  * 封装一些对于文件的函数的类。包括创建删除文件。文件的读写。以及读写锁的实现
  */
  class _file {
  protected:
  /**
  * @brief 以App的方式写入字符串
  * @param vector<string>& array vector<string>的类型数据写入数据库
  * @return True写入正确,False 写入失败
  */
  bool writeFile(const vector<string>& array);

  /**
  * @brief 创建_file默认的文件
  * @return True表示文件创造成功，False表示文件创造失败
  */
  bool createFile();
  /**
  * @brief 删除_filezh中的默认文件
  * @return 如果删除正常，则返回True，否则返回False
  */
  bool deleteFile();
  /**
  * @brief 加锁
  * @return 加锁成功则返回True，并意味着当前没有读写冲突，
  * 加锁失败则返回False，并意味着当前存在读写冲突。
  */
  bool addLock();
  /**
  * @brief 删锁
  * @return 删锁成功则返回True，否则返回False。
  */
  bool removeLock();
  /**
  * @brief
  * 判断文件是否存在打开,若没打开或者希望关闭则返回False，若文件打开则判断writebuff是否打开,若没有打开则打开，若已经打开，则啥也不干
  * @param bool need 希望文件状态，True期望文件存在，False期望文件不存在
  * @return 文件状态为need，则返回True
  */
  bool writeBuffOpen(bool need);
  /**
  * @brief
  * 判断文件是否存在打开,若没打开或者希望关闭则返回False，若文件打开则判断readbuff是否打开,若没有打开则打开，若已经打开，则啥也不干
  * @param bool need 期望文件状态，True期望文件存在，False期望文件不存在
  * @return 文件状态为need，则返回True
  */
  bool readBuffOpen(bool need);

  // filePath是_file超类的文件路径
  string name;
  // path 是_file的文件路径
  string path;
  // writeFileBuff是写文件buff指针
  ofstream writeFileBuff;
  // readFileBuff是读文件buff指针
  ifstream readFileBuff;
  // lockPath是加锁文件
  string lockPath;
  
  public:
  /**
  * @brief 返回类中默认的writeFileBuff，用来操作
  * @return <const ofstream&> 返回writeFileBuff
  */
  const ofstream& returnWriteFileBuff();
  /**
  * @brief 返回类中默认的readFileBuff，用来操作
  * @return <const ifstream&> 返回readFileBuff
  */
  const ifstream& returnReadFileBuff();
  /**
  * @brief 以App的方式写入字符串
  * @param string& str 写入的字符串
  * @return True写入正确,False 写入失败
  */
  bool writeFile(const string& str);
  /**
  * @brief 以行的形势读出数据
  * @param vector<string>& ret 保存的方式
  * @return 读完或文件不存在返回False，否则返回True
  */
  bool readline(vector<string>& ret);
  /**
  * @brief 判断_file默认文件是否存在
  * @return 若文件存在则返回True，否则返回False;
  */
  virtual bool isExist();
  /**
  * @brief <static> 删除指定文件
  * @param string Path 删除文件所在路径
  * @return 如果正常删除，则返回True，否则返回False
  */
  bool static deleteFile(string Path);

  /**
  * @brief 构造函数，传入文件路径
  * @param string name 文件路径
  */
  _file(string name);

  /**
  * @brief 拷贝构造函数
  * @param  _file& _copy 拷贝数据
  * @return
  */
  _file(_file& _copy);
  /**
  * @brief 析构函数，释放并关闭文件
  */
  ~_file();
  /**
  * @brief <static> 以App的方式写入字符串
  * @param string Path 路径
  * @param vector<string>& array 数据写入数据库
  * @return True写入正确,False 写入失败
  */
  bool static writeFile(string Path, const vector<string>& array);
  /**
  * @brief <static> 以App的方式写入字符串
  * @param string Path 路径
  * @param string& str 写入的字符串
  * @return True写入正确,False 写入失败
  */
  bool static writeFile(string Path, const string& str);
  /**
  * @brief <static> 判断指定文件是否存在
  * @param string name 文件路径
  * @return 若文件存在则返回True，否则返回False;
  */
  bool static isExist(string name);
  /**
  * @brief <static> 创建指定文件
  * @param string path 需要创建的文件名字
  * @return True表示文件创造成功，False表示文件创造失败
  */
  bool static createFile(string name);
  /**
  * @brief 返回文件的相对路径
  * @return 返回文件的相对路径
  */
  const string& returnFilePath();
  /**
  * @brief 返回文件的名字
  * @return  返回文件的名字
  */
  const string& returnFileName();
  };
  ```
### `DataBase.h && DataBase.cpp` 
  > 保护继承_dir类，调用一些_file的静态函数以辅助实现对数据库本身的操作
  ```c++
  /**
  * @brief 封装对数据库的操作，比如创建，删除。建立表等函数。
  */
  class DataBase : public _dir {
  public:
  /**
  * @brief 判断数据库是否存在
  * @return True为存在，False为不存在
  */
  virtual bool isExist();

  /**
  * @brief 判断指定数据库是否存在
  * @param  string DataBaseName 数据库名字
  * @return True为存在，False为不存在
  */
  bool static isExist(string DataBaseName);
  /**
  * @brief  构造创建数据库对象
  * @param string name 数据库路径
  * @return 
  */
  DataBase(string name);

  /**
  * @brief 拷贝构造函数
  * @param  DataBase& copy
  * @return 
  */
  DataBase(DataBase& copy);
  /**
  * @brief 创建数据库(底层就是创建文件夹)
  * @return 创建成功返回True，否则返回False
  */
  bool create();
  /**
  * @brief 显示数据库内表项
  * @return
  */
  void showDataBaseTable();

  /**
  * @brief 显示所有数据库
  * @return
  */
  void static showDataBase();
  /**
  * @brief 向数据库内插入表
  * @param string tableName 表名字
  * @param vector<string>& tableItem 表头项
  * @return 插入正常则返回True,否则返回False
  */
  bool insertTable(string tableName, const vector<string>& tableItem);
  /**
  * @brief 向数据库内插入表
  * @param string tableName 表名字
  * @return 插入正常则返回True,否则返回False
  */
  bool insertTable(string tableName);
  /**
  * @brief 删除数据库中tableName表项
  * @param string tableName 表名
  * @return 删除正常则返回True，否则返回False
  */
  bool deleteTable(string tableName);
  /**
  * @brief 删除默认数据库
  * @return  正常返回
  */
  bool removeDataBase();
  /**
  * @brief <static>删除指定数据库
  * @param string DataBaseName
  * @return 删除正常则返回True，否则返回False
  */
  bool static removeDataBase(string DataBaseName);
  private:
  };
  ```
### `table.h && table.cpp`
  > 保护继承_file类，封装一些对表本身的操作 
	```c++
	/**
	 * @brief 封装表操作
	 */
	class _table : protected _file {
	private:
	public:
		/**
		 * @brief 构造函数
		 * @param string databaseName 数据库名
		 * @param  string stableName 表名
		 * @return
		 */
		_table(string datablaseName, string stableName);
		/**
		 * @brief 构造函数
		 * @param  DataBase database 数据库对象
		 * @param  string stableName 表名
		 * @return
		 */
		_table(DataBase database, string stableName);
		/**
		 * @brief 构造函数
		 * @param  DataBase database 数据库对象
		 * @param  _file tableName 表文件对象
		 * @return
		 */
		_table(DataBase database, _file tableName);
		~_table();
	};
	```
### `shell.h && shell.cpp`
  > 对中文TMDsql语句的封装
	```c++
	class shell {
	public:
		shell();
		int readStatus();

	private:
		set<string> _GBKstatus;
		map<string, int> _binaryStatus;
		string strBuff;
		vector<vector<string>> arraybuff;
	};
	```
## 数据文件存储方式
- `data`目录
	>  