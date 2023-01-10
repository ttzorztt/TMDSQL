# TMDSQL(正在更新ing)
## 运行须知
### 编码
#### Windows(Windows 10专业版)
  > 本项目的windows版本采取GBK的编码方式，您需要查看您所使用的终端的编码方式,使用如下代码:
  ```cmd
  chcp
  ```
  >如果返回 `936`,则说明您当前系统所采取的编码方式是GBK。那么就不需要进行修改。但如果您返回的是其他编码方式，则需要进行编码设置，您可以使用如下命令:
  ```cmd
  chcp 936
  ```
  >来暂时设置，以便于使用该数据库。至于我采取GBK作为windows版本的编码，是因为windows默认采取的编码方式是GBK，但还是需要进行验证，以便于执行时出现乱码。
#### Linux(Debain 11)

- 本项目采用UTF-8的编码方式，而在UTF-8的编码方式中，一个汉字是三个字节。而项目编写时采取的环境是`gcc version 10.2.1 20210110 (Debian 10.2.1-6)`,linux中默认采取UTF-8的编码方式。
## 总体设计思路
- 无界面全终端操作方式,前端具有shell解析。并直接运行TMDSQL语句。
- 自定义中文TMDSQL语言,并实现该语言的语法检查,语义检查,转化为底层的C++代码并操作数据库。
- 创建数据库和数据库表,增删改查更新基本操作。
- 多用戶登录,读写上锁,视图层实现。
- 使用双级缓存进行数据读取。使得读取速度加快。
- 主键采取聚簇索引的底层形式。并采取缓冲形式进行查询速度的优化。
## 总体思路
> 对数据库的数据，我采取目录对应数据库，文件对应表的方式。除了数据库目录和表文件以外，我仿照Linux对于锁的建立，用'.'开头的隐藏文件同名文件建立锁，对于文件的读取，我采取字符型存取，大量数据的文件读取速度如果仅仅采取按行存取则会很慢，那么我借助文件指针的思想，建立索引文件，用来保存索引字段与文件指针的对于关系，以便于后期直接根据文件指针的位置随机存取。而索引文件本身很大，借助操作系统中的段页式文件，于是我建立二级索引文件以加快查询。而索引文件本身是有序的，采取二分折半查找的方式查询。


## src目录及其主要功能介绍
### `dir.h && dir.cpp`
  > 主要实现目录操作，在内核中，目录对应于数据库，封装_dir类。
### `file.h && file.cpp`
  > 封装文件操作类_file,在内核中，文件对应表。
### `DataBase.h && DataBase.cpp` 
  > 保护继承_dir类，调用一些_file的静态函数以辅助实现对数据库本身的操作
### `table.h && table.cpp`
  > 保护继承_file类，封装一些对表本身的操作 
### `shell.h && shell.cpp`
  > 对中文TMDsql语句的封装
### `super.h && super.cpp`
  > 对所有公有函数，枚举量以及全局静态const常量的声明与定义。
### `Index.h && Index.cpp`
  > 封装对表索引操作的声明与定义
### `TablePCB.h && TablePCB.cpp`
  > 封装对表PCB操作的声明与定义
### `DataBase.h && DataBase.cpp`
  > 封装对数据库PCB操作的声明和定义
## data目录的结构
### database
  > 数据库存放路径，其子文件夹为各个数据库文件夹，文件夹名即为数据库名，而该文件夹内，为表名，不含后缀，可以拿记事本以UTF-8的编码方式打开，内置数据存放方式是以CSV方式存放。
### index
  > 索引文件存储路径，其子文件夹为各个数据库文件夹，而在数据库文件夹中，并非存放表，而存放表的索引文件，命名方式与表名相同。
### PCB
  > PCB文件存储路径，其子文件夹为各个数据库文件夹，而在数据库文件夹中，存放表PCB文件。命名方式与表名相同。
### log
  > 日志文件存储路径，其内容为总日志记录
## 数据文件存储方式
![tree](ohter/svg/dataTree.svg)
## tablePCB的内容
1. name
2. nextIndex
  > 下一行的起始文件指针
3. length
  > 行数

# shell语言解释器
## 字段解释
`ID` 是该指令的一个编号
### CID
`CID`是每个关键字的编号
### PWD
- pwd = `[]`,默认状态，说明当前未选择数据库，且未登录。此种状态不可以执行除去<span data-color=“red”>登录</span>外的任何指令,均会输出: <br>
>(未登录) -=> 未登录,请登录后操作! 
- pwd = ["/"],说明当前已经登录，并未知帐号信息，且没有选择数据库
- pwd = ["/"]["测试数据库1"]， 说明当前已经登录，且已经选择一个名叫测试数据库的数据库。
- pwd = ["/"]["测试数据库1"]["测试表1"]， 说明当前已经登录，且当前已经选择测试数据库1下的测试表1
## 用户权限管理
`OP` 为权限值，分为四种权限
- `OP`=0 为Root权限 <br>
  > pwd = []
- `OP`=1 为管理员权限 <br>
  > pwd = ["/"]
- `OP`=2 为普通用户权限 <br>
  > pwd = ["/"]
- `OP`=3 为未登录权限 <br>
  > pwd = ["/"]
> 权限显而易见是ROOT > 管理员权限 > 普通用户权限,而不同权限，可以做不同的操作，简单来说，普通用户只有查询和一些查看内容的操作，一切对于数据库的修改，比如数据库的创建，数据库的删除，表的创建，表的删除等必须具有管理员或超越管理员的权限，同时管理员具有添加普通用户的权限。而ROOT作为超级管理员，可以添加管理员帐号。

## 用户提示符
### 未登录
  >(未登录) -=> 
### 普通用户
  >(用户) -=> 
### 管理员
  >(管理员) -=> 
### 超级管理员
  >(超级管理员) -=> 
## 支持语句
  > 总体来说，TMDSQL支持中文，且关键字之间用`空格`隔开，结尾没有封号，每条指令必读独立占据一行。
- **以下对于指令介绍，由于未知用户权限，将未知用户的用户提示符改为`(?) -=>`**
- **加粗字体为关键字，斜体为用户输入随意字符串,需要使用@开头，后面的则不需要**
### **`选择`**
- 使用 `选择`指令，首先判断是否登录，如果没有登录，无法操作，登录后根据登录帐号的权限，使用该指令会让当前shell的pwd改变，但是需要先选择数据库，然后选择表. <br>
如果使用选择类指令的时候，pwd.size() == 0,也就是没有登录，则会输出: <br>
  >(未登录) -=> 未登录,请登录后操作!
- **选择** &nbsp; **数据库** &nbsp; _@测试数据库1_ <br> 
    pwd.size() > 0，不管当前pwd到达那一步，都可以直接修改pwd
- **选择** &nbsp; **表** &nbsp; _@测试表1_
  - pwd.size() == 1,表示当前没有选择数据库，则无法选择，提示: <br>
      >(?) -= > 无法执行该指令，请先选择数据库!
  - pwd.size() == 2 表示已经选择数据库，且已经选择的数据库中有没有测试表1,提示: <br>
      >(?) -= > 无法执行该指令，该数据库中不存在此表

- **选择** &nbsp; **数据库** &nbsp; **表** &nbsp; _@测试数据库1_ &nbsp; _测试表1_ <br>
如果测试数据库1中没有测试表1，则显示: <br>
  >(?) -= > 无法执行该指令，该数据库中不存在此表
### **`显示`**
- **显示**
  - 使用`显示`指令，根据当前的pwd分为四种情况：
    - pwd = [] &nbsp; 
    >(未登录) -=> 未登录,请登录后操作!
    - pwd = ["/"]
    >(?) -= > 当前路径为: /
    - pwd = ["/"]["测试数据库1"]
    >(?) -= > 当前路径为: /测试数据库1
    - pwd = ["/"]["测试数据库1"]["测试表1"]
    >(?) -= > 当前路径为: /测试数据库1/测试表1
- **显示** &nbsp; **数据库**
  - 该指令需要登录后可使用。显示当前系统中所有数据库。
- **显示** &nbsp; **数据库**  &nbsp; _@DBID_(=pwd[1]) <br>
  - 该指令需要登录后使用，可以选择到表，效果可以显示指定数据库中所存的表。
- **显示** &nbsp; **表** &nbsp; _@TBID_ 
  - 该指令需要首先选择数据库，然后默认在该数据库下查询表的内容，默认显示前五行，也就是说`pwd.size() >= 2`
- **显示** &nbsp; **表** &nbsp; _@TBID_ &nbsp; _showNumber_
  - 该指令是上一条指令的扩充，同样需要先选择数据库，然后默认在指定数据库下查询表的内容，而参数 _showNumber_ 是显示的行数，注意该参数存储类型是int，不能超过数据大小。
- **显示** &nbsp; **数据库** &nbsp; **表** &nbsp; _@DBID_ _TBID_
  - 该指令不需要选择数据库，效果是按照默认参数5行显示指定TBID的 内容
- **显示** &nbsp; **数据库** &nbsp; **表** &nbsp; _@DBID_ _TBID_ _showNumber_
  - 是上一条的扩充，将默认显示行数设置为 _showNumber_ 行
### **`登录`**
- **登录** &nbsp; _@帐号_ &nbsp; _密码_ <br>
  - 登录失败显示:
  >(?) -= > 登录失败!
  - 登录成功:
  >(?) -= > 登录成功，欢迎您,帐号!

### **`执行`**
- **执行**  &nbsp;  _@脚本名_
  > path是执行SQL语句的脚本文件。编码格式无论是windows系统版本还是linux版本，均需要采取UTF-8的编码格式。 <br>

- **注意: 需要将脚本放置于./data/SQL目录下，然后使用如上指令，脚本名需要是放置在SQL的全称，带后缀的那种。**

### **`创建`**
-  **创建** &nbsp; **普通用户**  _@ID_ &nbsp; _Password_  
> 该指令需要OP < 2,也就是需要管理员权限或者超级管理员ROOT权限才能执行。该指令会添加密码为Password的普通用户ID
-  **创建** &nbsp;  **管理员** &nbsp;  _@ID_ &nbsp;_password_
> 该指令需要OP < 1,也就是需要超级管理员ROOT权限才能执行。会添加密码为password的管理员ID。
-  **创建** &nbsp; **数据库** &nbsp; _@DBID_
> 该指令需要OP < 2,也就是管理员或超级管理员ROOT权限才可以执行。会创建名为DBID的数据库。
- **创建** &nbsp; **表** &nbsp; _@TBID_
> 该指令需要OP < 2，也就是管理员或超级管理员权限才可执行。但在此之前需要选定数据库。如果没有选择数据库的话会输出:
>(?) -= > 该指令无法执行，没有选择数据库!

### **`删除`**
> 该指令需要管理员或者超级管理员权限才可执行。谨慎使用！针对不同的指令，系统将变着花样提示。
- **删除** &nbsp; **数据库** &nbsp; _@DBID_
>该指令会删除名为DBID的数据库。执行首先会判断DBID存在与否，如果存在，系统将首先输出该数据库中存在的所有表，然后需要用户键入"确认"才可删除。
- **删除** &nbsp; **表** &nbsp; _@TBID_
> 该指令会删除名为TBID的表，当然执行该指令的前提是你首先得选择到数据库，系统会判断当前pwd的路径，如果pwd.size() > 2,且pwd[1]中有该表，系统会输出该表当前的前五行，然后同样需要用户键入"确认"才可删除。
- **删除** &nbsp; **数据库** &nbsp; **表** &nbsp; _@DBID_ &nbsp; _TBID_
> 该指令会删除DBID下的TBID，首先判断DBID是否存在，且是否有TBID这张表，其实和上一个指令差不多，是将上一个指令中默认的pwd[1]修改为DBID执行而已。
- **删除** &nbsp; **用户** &nbsp; _@UserName_
> 该指令会删除名字为UserName的普通用户。
- **删除** &nbsp; **管理员** &nbsp; _@managerID_
> 该指令需要超级管理员ROOT权限才能执行。
## BUG记录
### linux下交叉编译windows程序
> 安装Mingw，命令如下：
```bash
sudo apt install mingw-w64*
```
安装后`x86_64-w64-mingw32-g++`进行编译和链接
### 不同操作系统下使用不同的命令
使用如下预处理:
```c++
#ifndef __WIN32__
#endif
#ifndef __linux__
#endif
```
### windows下执行缺少动态库libxxx.dll
> 使用g++的使用采取动态编译的方式。需要采取静态方式，添加如下参数：
```bash
x86_64-w64-mingw32-g++ -static -c xxx.cpp -o xxx.o
```

### ifstream 的seekg失效
> 在读取文件的时候，读取到文件结尾后尝试使用seekg设置指针重新指向-1，但无法使用readline读取，诡异的是使用tellg返回的居然是设置后的-1。
- 尝试1: 使用clear函数，无效。如果没有查询到eof重新设置seek有效，但并不知道是否到了eof。
- 尝试2: 既然最开始可以使用，那么不如关闭后重新打开。成功。如此每次setseek的时候，查看一下eof的状态。如果达到文件尾的时候，就close后重新open。