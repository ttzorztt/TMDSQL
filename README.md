
# TMDSQL_1.2(ing)

## 版本更替

- V(1.0)
  > 弱鸡版本，实现对数据库和表的简要增删查，和权限管理，前端自定义中文shell脚本编程。
  - bug记录: 对选择表指令作用不明显。
    - V1.1:已解决。添加若干结合pwd的指令。做到省略参数
- V(1.1)
  > 菜鸟版本,添加若干指令,对上一个版本的BUG进行修复，同时新增日志管理，更为详细记录shell的报错信息。
  - bug记录: 日志显示有bug，没做到实时显示到文件里。
    - 操作系统中有个概念是内存何时写回磁盘。出现bug的原因就是没有实时写回磁盘，导致同时打开日志文件显示总比指令慢半拍。
    - V1.2:已解决。每写完一行，就强制写回磁盘
- V(1.2)
  > 吗卡巴卡版本,添加若干指令,对上一个版本的BUG进行修复，目标实现用户视图层，允许设置索引列(之前版本默认第一个字段是索引)
  > 顺便吐槽一下，加点新功能真的是要把我整服，逻辑不难，犄角旮旯的细节改到吐

## 实现功能简要概述

- 对数据库的增删查功能的实现
- 对表的增删查的功能实现
- windows平台和linux下载对应的版本均可执行
- 权限管理
  - 用户数据记录在./data/User/pd文件内,每行包含用户名，用户密码，权限等级三项,而权限分为四类
  - 未登录
  - 用户
  - 管理员
  - 超级管理员Root
  > 不同的权限可以执行不同的操作。上级用户可以对下级用户进行增删，也就是说Root可以增删管理员和用户，管理员可增删用户，普通用户只能查询，增删需要管理员以及ROOT才可执行。显然限制用户行为是程序员唯一的乐趣。
- 前端shell编写
  - 实现简单的解释，Shell是按照解释型语言编写，大概是31条中文指令，分为10类。不同指令执行会在终端输出是否成功以及简要错误原因。同时会在日志中记录更为详细的原因。
    - 退出系
      > 只有一条指令，执行就会bye-bye
    - 选择系
      > 如果选择了数据库，后期建表或删表等操作的指令可以省略数据库参数，同样如果选择了表，后期对表的指令同样可以省略表对应的参数,但如果你非要说，哎，我就不选，就是玩，那我只有大喊一身，靓仔。
    - 显示系
      > 对数据库所存储的表，或表的内容进行显示。话说，我还没想好还能显示什么。
    - 登录系
      > 系统权限划分很严格，不同权限下允许执行的指令不同。不登录你只能含泪说bye-bye
    - 执行系
      > 主要为了实现脚本化编程，另外建立一个txt文件，包含若干指令，使用执行系指令可以直接执行脚本，那不得高大上起来，别的小孩都有脚本，咱们也得安排上
    - 创建系
      > 对数据库，表，用户，管理员的创建，emmm，你配吗？先看看自己的权限再说
    - 删除系
      > 对数据库，表，用户，管理员的删除，emmm，我不配，一个路过的普通用户说
    - 插入系
      > 对表内容插入，emmmm，起名恐惧症
    - 查询系
      > 根据索引进行搜索，查询优化算法？纯纯纯纯暴力好吧。
    - 设置系
      > 高级boy，索引，视图的设置
- 日志系统
  - **日志系统中的运行错误与终端输出不同，是两套显示集，日志记录的更为详细**
  - 日志按照日期划分，会自动记录当前的时间和日期，按照日期建立日志文件，在底层实现的时候，对不同的错误情况进行了详细分类，分为31种不同的错误情况。(在文章后面有详细情况划分)
- 查找逻辑(菜鸡大四毕设，误喷)
  - 查找逻辑很简单，简单做了一个索引，在C++中又一个参数是文件指针(其他语言不太了解名词)，逻辑上文件是二维的，底层实际上是一维存储，那么文件指针就是一维的下标。接下来我从逻辑上解释，假设我们现在表内有很多行数据(每行第一个字段是索引)，我重新建立index文件夹，其文件结构与dadabasae文件结构相同，内容分为两个字段，一个是索引，一个是表中该行开头的文件指针。查询指令执行的时候，就会直接访问index文件系统，查找对应的行的文件指针，重新打开对应的表，直接跳转到该行。
  - 这种查找逻辑，适合每行数据很多的情况，如果一行数据并不多，其实效率也不高。
- 脚本系统
  > 支持脚本编程，即不需要用户在终端中一条一条执行，将指令写在一个文件中，每行存储一条指令，主要中间不允许空行(会认为文件结束)。把该文件放在./data/SQL/路径下，使用指令 `执行 @SQLName`执行。emmm，当然要提醒一下靓仔，你需要放在./data/SQL路径下才能使用，别说为什么不能用相对路径或绝对路径，如果你要听假话的话，我可以告诉你，是因为TMD(没有骂人，回到标题你就会发现名字就叫这个)数据库是支持linux和windows双系统的，你要是绝对路径就很麻烦，而且我怕你傻了吧唧删我别的路径的文件。但你要是想听实话的话，哎，其实这些都不是问题，解决的话也不难，就是懒，毕竟折腾用户才是最快乐的。
- PCB记录
  > 所有表项均有对应PCB文件，存放在./data/PCB/中，该文件夹和database分布相同。记录一些需要的表属性。emmm，毕竟要展示一下是学过OS滴。(不好，让他装到了。)

## 运行须知

> 根据系统版本划分为两个，Linux(Debain11)版本，Windows(Windows10专业版)两个版本，下载前请先查看Readme，获得TMDSQL所支持的语法。该可执行文件首先会生成一些辅助文件，会在当前目录生成data文件夹，存放一些辅助文件。(linux需要管理员权限),系统预置超级管理员，帐号为:root,密码为root,具体可见User文件夹下的pd文件。所支持的语句或功能需要查看备注，特别标出的是最新功能，上一个版本可能不支持。如需要最新版本，需要下载源码进行make编译。(放心吧，这段话可以跳过，下载源码？能将readme看到现在的人估计都没几个)

- 编译系统环境是在linux(Debain)中，gcc的版本是:`gcc version 10.2.1 20210110 (Debian 10.2.1-6)`,进入源码后，使用

  ```bash
  make
  ```
  
  指令可以生成linux版本的TMDSQL
- 附带版本windows，是在linux(Debain)采取交叉编译的方式，需要首先下载交叉编译链:

  ```bash
  sudo apt install mingw-w64*
  ```

  进入源码后，使用

    ```bash
    make TMDSQL.exe
    ```

  即可得到windows版本的TMDSQL.exe

### 编码

#### Windows版本(Windows 10专业版)

  > 本项目的windows版本采取GBK的编码方式，您需要查看您所使用的终端的编码方式,使用如下代码:(如果你是python用户，你确实需要查看一下)

  ```cmd
  chcp
  ```

  >如果返回 `936`,则说明您当前系统所采取的编码方式是GBK。那么就不需要进行修改。但如果您返回的是其他编码方式，则需要进行编码设置，您可以使用如下命令:

  ```cmd
  chcp 936
  ```

  >来暂时设置，以便于使用该数据库。至于我采取GBK作为windows版本的编码，是因为windows默认采取的编码方式是GBK，但还是需要进行验证，以便于执行时出现乱码。emmmm，出现bug再说
  
#### Linux版本(Debain 11)

- 本项目采用UTF-8的编码方式，而在UTF-8的编码方式中，一个汉字是三个字节。而项目编写时采取的环境是`gcc version 10.2.1 20210110 (Debian 10.2.1-6)`,linux中默认采取UTF-8的编码方式。(需要管理员权限)

## data目录的结构

> 系统运行前会调用初始化函数，so这是初始化之后的结果

### database

  > 数据库存放路径，其子文件夹为各个数据库文件夹，文件夹名即为数据库名，而该文件夹内，为表名，不含后缀，可以拿记事本以UTF-8的编码方式打开，内置数据存放方式是以CSV方式存放。但不建议你自己写一个UTF-8的文件放进去冒充表，因为系统没有你想象的那么简单，pcb记录文件数据，index记录每行索引，你直接放进去，必将查询不到。

### index

  > 索引文件存储路径，其子文件夹为各个数据库文件夹，而在数据库文件夹中，并非存放表，而存放表的索引文件，命名方式与表名相同。建议不要瞎改，会出bug的

### PCB

  > PCB文件存储路径，其子文件夹为各个数据库文件夹，而在数据库文件夹中，存放表PCB文件。命名方式与表名相同。听这名字，势必就是学过操作系统的

### Log

  > 日志文件存储路径，其内容为总日志记录，本来想着要不就整一个文件，但是想着万一发扬光大，还是按照时间存储

### SQL

  > 存放需要执行SQL脚本，不需要后缀名

### User

  > 只有一个文件pd，存放帐号密码信息。当然是明码了，你个锁黑，没事搞什么加密算法干嘛。

## tablePCB的内容

1. name
2. nextIndex：下一行的起始文件指针
3. length：行数
   > 实际上这个参数再代码逻辑内没有意义，但暂时记录着，万一之后有什么说法呢？

# shell语言解释器

## 字段解释

`ID` 是该指令的一个编号

### CID

`CID`是每个关键字的编号

### PWD

- pwd = `[]`,默认状态，说明当前未选择数据库，且未登录。此种状态不可以执行除去登录外的任何指令,均会输出:
  
  ```txt
  (未登录) -=> 未登录,请登录后操作!
  ```
  
- pwd = \["/"\],说明当前已经登录，并未知帐号信息，且没有选择数据库
- pwd = \["/"\]\["测试数据库1"\]， 说明当前已经登录，且已经选择一个名叫测试数据库的数据库。
- pwd = \["/"\]\["测试数据库1"\]\["测试表1"\]，说明当前已经登录，且当前已经选择测试数据库1下的测试表1

## 用户权限管理

`OP` 为权限值，分为四种权限

- `OP`=0 为Root权限

    ```txt
    pwd = ["/]
    ```

- `OP`=1 为管理员权限
  
  ```txt
  pwd = ["/"]
  ```
  
- `OP`=2 为普通用户权限
  
  ```txt
  pwd = ["/"]
  ```
  
- `OP`=3 为未登录权限
  
  ```txt
  pwd = []
  ```

> 权限显而易见是ROOT > 管理员权限 > 普通用户权限,而不同权限，可以做不同的操作，简单来说，普通用户只有查询和一些查看内容的操作，一切对于数据库的修改，比如数据库的创建，数据库的删除，表的创建，表的删除等必须具有管理员或超越管理员的权限，同时管理员具有添加删除普通用户的权限。而ROOT作为超级管理员，可以添加删除管理员帐号。

## 用户提示符

### 未登录
  
  ```txt
  (未登录) -=>
  ```
  
### 普通用户
  
  ```txt
  (用户) -=>
  ```
  
### 管理员
  
  ```txt
  (管理员) -=>
  ```
  
### 超级管理员
  
  ```txt
  (超级管理员) -=>
  ```
  
## 支持语句

  > 总体来说，TMDSQL支持中文，且关键字之间用`空格`隔开，结尾没有封号，每条指令必读独立占据一行。
  
- **以下对于指令介绍，由于未知用户权限，将未知用户的用户提示符改为`(?) -=>`**
- **加粗字体为关键字，斜体为用户输入随意字符串,需要使用@开头，后面的则不需要**
- 未登录用户只允许执行`登录`、`退出`和`执行`指令，其余指令均会拒绝执行并输出：
  
  ```txt
  (未登录) -=> 未登录,请登录后操作!
  ```
  
### **`退出`**

- 使用`退出`指令，会结束SQL执行。并输出:
  
  ```txt
  已退出!
  ```

### **`选择`**

- **选择** **数据库** _@测试数据库1_
  - 若数据库不存在

    ```txt
     目标数据库不存在!
    ```

- **选择** **表**  _@测试表1_
  - 没有选择数据库，则无法选择，提示:

    ```txt
    该指令无法执行，没有选择数据库!
    ```

  - 已经选择数据库，且已经选择的数据库中有没有测试表1,提示:

    ```txt
    无法执行该指令，该数据库中不存在此表
    ```

- **选择**  **数据库**  **表**  _@测试数据库1_  _测试表1_
  - 若测试数据库1不存在，则提示:

    ```txt
    目标数据库不存在!
    ```

  - 如果测试数据库1中没有测试表1，则显示:

    ```txt
    无法执行该指令，该数据库中不存在此表
    ```

### **`显示`**

- **显示**
  - 使用`显示`指令，根据当前的pwd分为四种情况：
    - pwd = []  

      ```txt
      (未登录) -=> 未登录,请登录后操作!
      ```

    - pwd = ["/"]
  
      ```txt
      (?) -= > 当前路径为: /
      ```

    - pwd = \["/"]\["测试数据库1"]

      ```txt
      (?) -= > 当前路径为: /测试数据库1
      ```

    - pwd = \["/"]\["测试数据库1"]\["测试表1"]

      ```txt
      (?) -= > 当前路径为: /测试数据库1/测试表1
      ```

- **显示**  **数据库**
  - 该指令需要登录后可使用。显示当前系统中所有数据库。假设当前数据库内有DB1,DB2,DB3三个数据库，则使用该指令后显示:

    ```txt
     #######
     ? DB1 ?
     ? DB2 ?
     ? DB3 ?
     #######
    ```

- **显示**  **数据库**   _@DBID_(=pwd[1])
  - 该指令需要登录后使用，可以选择到表后使用该指令，效果可以显示指定数据库中所存的表。
    - 当该数据库不存在时:

    ```txt
    数据库不存在!
    ```
  
    - 当该数据库为空的时候:

    ```txt
    这个数据库是空的!
    ```

    - 当这个数据库有TB1,TB2,TB3三张表的时候：

      ```txt
      *******
      | TB1 |
      | TB2 |
      | TB3 |
      *******
      ```

- **显示** **表** _showNumber_
  - 该指令需要首先选择数据库且选择表，显示showNumber行，也就是说`pwd.size() ==  3`

- **显示**  **表**  _@TBID_ _showNumber_
  - 该指令需要首先选择数据库，然后默认在该数据库下查询表的内容，_showNumber_ 是显示的行数，也就是说`pwd.size() >= 2`
  - 如果执行这条语句之前没有`选择`数据库，那会提示:

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 如果已经选择数据库，但选择的数据库内没有该表，

  ```txt
  无法执行该指令，该数据库中不存在此表!
  ```

  - 如果一切顺利，已选择数据库，且选择的数据库内有该表，则会正常输出。

- **显示**  **数据库**  **表**  _@DBID_ _TBID_ _showNumber_
  > 显示DBID下的TBID的前showNumber行

- **显示**  **表**  _@TBID_  _showNumber_ （已废弃)
- **显示**  **数据库**  **表**  _@DBID_ _TBID_ (已废弃)

### **`登录`**

- **登录**  _@帐号_  _密码_
  - 登录成功:

    ```txt
    (?) -= > 登录成功，欢迎您,帐号!
    ```

  - 登录失败:
    - 帐号不存在:

      ```txt
      帐号不存在,登录失败!
      ```

    - 密码错误:

      ```txt
      密码错误,登录失败!
      ```

### **`执行`**

- **执行**    _@脚本名_
  > path是执行SQL语句的脚本文件。编码格式无论是windows系统版本还是linux版本，均需要采取UTF-8的编码格式。

  - 如果当前目录不存在该脚本,则会输出:

    ```txt
    无法执行该指令，目标脚本不存在!
    ```

- **注意: 需要将脚本放置于./data/SQL目录下，然后使用如上指令，脚本名需要是放置在SQL的全称，带后缀的那种。如果代码中间存在空行，会跳过空行后的内容，结束执行**

### **`创建`**

- **创建**  **用户**  _@ID_  _Password_

  > 该指令需要OP < 2,也就是需要管理员权限或者超级管理员ROOT权限才能执行。该指令会添加密码为Password的普通用户ID
  - 当用户ID存在时，提示:

  ```txt
  该用户已存在，无法添加!
  ```

  - 创建成功后提示:

  ```txt
  创建成功!
  ```

- **创建**   **管理员**   _@ID_ _password_
  > 该指令需要OP < 1,也就是需要超级管理员ROOT权限才能执行。会添加密码为password的管理员ID。
  - 当用户ID存在时，提示:

  ```txt
  该用户已存在，无法添加!
  ```

  - 创建成功后提示:

  ```txt
  创建成功!
  ```

- **创建**  **数据库**  _@DBID_
  > 该指令需要OP < 2,也就是管理员或超级管理员ROOT权限才可以执行。会创建名为DBID的数据库。
  - 如果DBID存在，则提示:

  ```txt
  无法执行该指令，目标数据库已存在!
  ```

  -如果DBID不存在，则执行成功，提示:

  ```txt
  创建成功!
  ```

- **创建** **数据库** **表** _@DBID_ _TBID_(V1.2)

- **创建**  **表**  _@TBID_
  > 该指令需要OP < 2，也就是管理员或超级管理员权限才可执行。但在此之前需要选定数据库。
  - 如果没有选择数据库的话会输出:

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 如果已经选择数据库，但表TRID已存在，那会提示:

  ```txt
  无法执行该指令，目标表已存在!
  ```

  - 如果一切顺利，则显示:

  ```txt
  创建成功!
  ```

### **`删除`**

> 该指令需要管理员或者超级管理员权限才可执行。谨慎使用！针对不同的指令，系统将变着花样提示。

- **删除**  **数据库**  _@DBID_
  >该指令会删除名为DBID的数据库。执行首先会判断DBID存在与否，如果存在，系统将首先输出该数据库中存在的所有表，然后需要用户键入"确认"才可删除。
  - 如果数据库DBDI不存在，则会提示:

  ```txt
  目标数据库不存在!
  ```

  - 如果DBID是一个空数据库，那么就直接删除，并不需要输入确认:

  ```txt
  删除成功!
  ```

  - 如果DBID是一个非空数据库，且其中有表TB1，TB2，TB3和TT三张表，如果执行指令，则显示:

  ```txt
  数据库并不为空，以下为当前存在的表项
  *******
  | TB1 |
  | TB2 |
  | TB3 |
  | TT  |
  *******
  如果您仍然执意删除，请键入 "确定" :
  ```

  - 此时你需要在':'后键入确定。
    - 如果你没有输入`确定`而输出别的(包括只输入回车)，则会提示:

      ```txt
      该指令已取消!
      ```

    - 如果你输入`确定`,则会提示:

      ```txt
      删除成功!
      ```

- **删除**  **表**  _@TBID_
  > 该指令会删除名为TBID的表，当然执行该指令的前提是你首先得选择到数据库，系统会判断当前pwd的路径，如果pwd.size() > 2,且pwd[1]中有该表，系统会输出该表当前的前五行，然后同样需要用户键入"确认"才可删除。
  - 如果你没有选择数据库，则会提示：

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 如果已选数据库，但pwd[1]中没有表TBID,则会提示：

  ```txt
  目标表不存在!
  ```

  - 如果存在，但表为空，执行会提示:

  ```txt
  删除成功!
  ```

  - 如果存在，且不为空的情况下，执行后提示:

  ```txt
  表不为空，以下是该表的一部分内容:
  测试1 测试2 测试3 
  测试1 测试2 测试3 
  如果您仍然执意删除，请键入 "确定" :
  ```

  - 此时你需要在':'后键入确定。
    - 如果你没有输入`确定`而输出别的(包括只输入回车)，则会提示:

      ```txt
      该指令已取消!
      ```

    - 如果你输入`确定`,则会提示:

      ```txt
      删除成功!
      ```

- **删除**  **数据库**  **表**  _@DBID_  _TBID_
  > 该指令会删除DBID下的TBID，首先判断DBID是否存在，且是否有TBID这张表，其实和上一个指令差不多，是将上一个指令中默认的pwd[1]修改为DBID执行而已。
  - 和上一条指令类似。
- **删除**  **用户**  _@UserName_
  > 该指令会删除名字为UserName的普通用户。
  - 当UserName不存在时，提示:

  ```txt
  该用户不存在!
  ```

  - 当与用户存在的时候，提示:

  ```txt
  删除成功!
  ```

- **删除**  **管理员**  _@managerID_
  > 该指令需要超级管理员ROOT权限才能执行。
  - 当managerID不存在时，提示:

  ```txt
  该管理员不存在!
  ```

  - 当与用户存在的时候，提示:

  ```txt
  删除成功!
  ```

### **`插入`**(3)

  > 该指令同样需要管理员权限或超级管理员权限

- **插入** _[value1_ _value2_ _...]_
  > 该条指令需要用户选择到表，一切顺利的情况下，尾插value1，value2等数据。
  - 当未选择数据库的时候，会提示:

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 当选择数据库但没有选择表的时候，
- **插入** **表** _@TBID_ _[value1_ _value2_ _...]_
  > 该条指令会在选择数据库，且该数据库内有TBID后可执行，尾插value1，value2等数据。
  - 当未选择数据库的时候，会提示:

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 当已选择数据库，但pwd[1]中没有该表，则会显示:

  ```txt
  目标表不存在!
  ```

  - 当一切顺利，则会显示:

  ```txt
  插入成功!
  ```

- **插入** **数据库** **表** _@DBID_ _TBID_ _[value1 value2 ...]_
  > 该指令是上一条的扩展，无需先选择数据库，只要参数正确，指定数据库下的表尾插入指定集合即可。
  - 当数据库DBID不存在时，会提示:

  ```txt
  目标数据库不存在!
  ```

  - 当表不存在的时候,会提示:

  ```txt
  无法执行该指令，该数据库中不存在此表!
  ```

  - 当一切顺利，则会显示:

  ```txt
  插入成功!
  ```

### **`查询`**(3)

> 仅需登录，不查询权限等级

- **查询**  _index_
  > 需要选择数据库，选择表，即pwd.size() > 2

- **查询** **表** _@TBID_ _index_
  > 需要选择数据库，即pwd.size() > 1,pwd[1]中有表TBID，查询索引为index的内容。
  - 如果执行前没有选择数据库，则会显示:

  ```txt
  该指令无法执行，没有选择数据库!
  ```

  - 如果选择数据库后，但目标数据库内没有表TBID，则会显示：

  ```txt
  目标表不存在!
  ```

  - 如果TBID存在，但index并不在表TBID中，则会显示:

  ```txt
  搜索结束，没有搜到目标值!
  ```

  - 如果index存在，则会返回搜索到的值。

- **查询** **数据库** **表** _@DBID_ _TBID_ _index_
  > 不需要选择数据库，属于权限最小的一系列指令，只需登录即可执行。查询DBID下的TBID中索引为index的内容。
  - 数据库DBID不存在,则会输出:
  
  ```txt
  目标数据库不存在!

  ```

  - 数据库DBID存在，但是表TBID不存在，则会输出:

  ```txt
  目标表不存在!
  ```

  - 数据库DBID存在且表TBID存在，但是没有搜到Index，则会输出：

  ```txt
  搜索结束，没有搜到目标值!
  ```

  - 如果搜到，则会正常显示搜索内容。

### **`设置`**(6)

> 该系指令是用来设置一些表特性，比如设置索引，或约束用户建立视图层，该系指令只允许管理员以上权限执行

- **设置** **视图** **数据库** **表** _@DBID_ _TBID_ _UserName_ _[value...]_
- **设置** **视图** **表** _@TBID_ _UserName_ _[value...]_
- **设置** **视图** _@UserName_ _[value...]_
- **设置** **索引** **数据库** **表** _@DBID_ _TBID_ _indexColumn_
- **设置** **索引** **表** _@TBID_ _indexColumn_
- **设置** **索引** _indexColumn_

## 日志系统

  > 建立Log类，实现日志的记录。
  
- 按照日期划分文件
- 任何调用记录，均会在log文件夹内显示。log文件夹内存储LOG文件，记录所有操作内容，以及执行结果，包括但不限于:
  - 系统登录时间以及登出时间
  - 用户操作内容以及成功与否

- 日志内容(三行)：
  - 是否执行成功("V" or "X"),时间(包括日期和时间)
  - 失败原因(如果成功则输出顺利执行)
  - 执行人:执行指令(对一些缩写指令进行扩充。避免查看上下文)

- 日志记录项
  - 系统初始化(系统初次使用)
  - 登入系统(打开系统)
  - **指令记录**
  - 登出系统(关闭系统)

- 指令记录详解
  
  ```txt
  < 1 > [2] (3)
  4
  5{6} -=> 7
  ```

  1. 执行是否顺利(V或X)
  2. 日期
  3. 时间
  4. 执行细则(是否顺利，顺利的话显示"顺利执行"，否则显示错误内容)
  5. 权限等级
  6. 用户名
  7. 执行内容(包括指令和数据)
  
  - 比如:
    - 使用指令`执行 @SQL`,而SQL中的内容为:

      ```txt
      登录 表 @root root
      选择 数据库 @DB1
      ```

    - 那么日志记录内容将类似于:
  
      ```txt

      [2023.1.15] (15:5:26) 登录系统

      < V > [2023.1.15] (15:5:26)
      顺利执行
      未登录{未登录} => 执行 "SQL"

      < X > [2023.1.15] (15:5:26)
      未知指令
      未登录{未登录} => 登录 表 root root 

      < X > [2023.1.15] (15:5:26)
      未登录拒绝执行
      未登录{未登录} => 选择 数据库 DB1 

      [2023.1.15] (15:5:26) 登出系统

      ```

    - 而如果SQL中记录的是:

      ```txt
      登录 @root root
      选择 数据库 @DB1
      ```

    - 那么Log中将会记录:

      ```txt
      
      [2023.1.15] (15:6:5) 登录系统

      < V > [2023.1.15] (15:6:5)
      顺利执行
      未登录{未登录} => 执行 "SQL"

      < V > [2023.1.15] (15:6:5)
      顺利执行
      未登录{未登录} => 登录 用户"root" 密码"root"

      < V > [2023.1.15] (15:6:5)
      顺利执行
      超级管理员{root} => 选择 数据库"DB1"

      [2023.1.15] (15:6:5) 登出系统

      ```

    - 由于是SQL文件中的语句，所以时间是连续的，如果不执行`执行 @SQL`改为一条一条输入，那么时间将会不连续。
- 日志报错类型
  - **日志记录报错与终端输出是两套内容，日志更为详细**
  - 顺利执行
    > 默认值，表示一切正常执行。
  - 键入不存在的关键字
    > 系统是按照解释型设计，区分是否为关键字，是按照@符号区分，在@前面所出现的字符，均为关键字，而在@之后的内容，都是用户自定义的内容。
  - 键入违规字符
    - 违规字符集:

      ```c++
      static std::unordered_set<char> checkErrorName{
      '`', '~', '!',  '@',  '#', '$', '%', '^', '&', '*', '(',')', '_', '-',  '=',  '+', '[', ']', '{', '}', '|', '\\',':', ';', '\'', '\"', ',', '<', '>', '.', '?', '/'};
      ```

    - 故用户需要避开这些非法字符
  - 登录帐号错误
    > 顾名思义，使用登录指令`登录 @ID Password`的时候，ID必须是在./data/User/pd文件内保存的ID，如果需要新建登录用户，可以使用系统默认的超级管理员帐号ID:root,Passoword::root登录，然后使用`新建 用户 @ID password`指令。或建造管理员用户，使之新建用户。
  - 登录密码错误
    > 使用登录指令的时候，密码输入错误。
  - 无法选择不存在的数据库
    > 这里的不存在其实有两种意思，一种是选择了不存在，一种是没有选择
    - `创建 表 @TBID`
      > 没有选择数据库
    - `选择 数据库 @DBID`
      > DBID不存在
    - `选择 数据库 表 @DBID TBID`
      > DBID不存在
    - `设置 索引 数据库 表 @DBID @TBID index`
  - 未登录拒绝执行
    > 刚进入系统的时候，系统处于`未登录`的状态，在这个状态下，用户只能使用`登录`,`退出`,`执行`三类指令。其余指令不允许执行，一旦执行就会报错。
  - 普通用户违规操作
    - `创建`
      > 创建系列指令普通用户无权执行。管理员和超级管理员有权限执行，但注意的是，管理员没有权限添加管理员用户等，不允许平级操作
    - `删除`
      > 删除系列指令普通用户无权执行。管理员和超级管理员有权限执行，但注意的是，管理员没有权限删除管理员用户等，不允许平级操作
    - `设置`
      > 设置系指令是属于高级指令，如果你是普通用户的话，emmm，bye了个bye
  - 未选择数据库越级选择表
    - `选择 表 @TBID`
      > 使用该指令之前没有选择数据库
    - `创建 表 @TBID`
      > 使用该指令之前没有选择数据库
    - `删除 表 @TBID`
      > 使用该指令之前没有选择数据库
    - `插入 表 @TBID`
      > 使用该指令之前没有选择数据库
    - `查询 @index`
      > 使用该指令之前没有选择数据库
    - `查询 表 @TBID index`
      > 使用该指令之前没有选择数据库
    - `显示 表 @TBID showNumber`
      > 使用该指令之前没有选择数据库
  - 已选择的数据库中不存在目标表
    - `选择 表 @TBID`
      > pwd[1]中没有TBID
    - `删除 数据库 表 @DBID TBID`
      > DBID中没有TBID
  - 第一个关键字错误
    > 指令所包含的第一个关键字，虽然是关键字但并非合法开头关键字，比如`用户`开头，虽然是关键字，但不允许开头。
  - 第二个关键字错误
    > 类比于上一个，第二个关键字虽然是关键字，但语义不通，比如: 正常的:`创建 数据库 @DBID`，如果你写成`创建 登录 @DBID`,那就会触发这个
  - SQL文件未找到
    - `执行 @SQLname`
      > SQLname在`./data/SQL/`内不存在，会触发这个
  - 编译错误
    > 这是纯纯瞎写，比如正常的`登录 @root root`,你给写成 `@root root`,说实话我猜也猜不出来你要干嘛。
  - 创建已存在的用户
    - `创建 用户 @UID UPassword`
      > UID在`./data/User/pd`文件内已存在，但这里并不区分该ID是管理员ID还是用户ID
  - 创建已存在的管理员
    - `创建 管理员 @UID UPassword`
      > UID在`./data/User/pd`文件内已存在，但这里并不区分该ID是管理员ID还是用户ID
  - 管理员违规操作
    > 管理员同级操作会触发这个BUG
    - `创建 管理员 @UID UPassword`
      > 管理员权限不允许执行该操作
    - `删除 管理员 @UID`
      > 管理员权限不允许执行该操作
  - 表已存在无法创建
    - `创建 表 @TBID`
      > 表都已经有了自然不让你瞎搞了
  - 数据库已存在无法创建
    - `创建 数据库 @DBID`
      > 说实话，这个的原因就和前一个一样一样的
  - 表不存在无法删除
    - `删除 表 @TBID`
      > 这个原因，emmm，其实你也懂。
    - `删除 数据库 表 @DBID TBID`
      > 这个就不用我解释了吧
  - 数据库不存在无法删除
    - `删除 数据库 表 @DBID TBID`
      > 如果连DBID都不存在，你准备要干嘛
    - `删除 数据库 @DBID`
      > 发挥一下你没什么用的脑袋，应该知道这是啥意思
  - 目标用户不存在无法删除
    - `删除 用户 @UID`
      > 删除空气?
  - 目标管理员不存在无法删除
    - `删除 管理员 @UID`
      > 你准备要干嘛？二刷空气?
  - 输入非确定指令取消
    > 这个有必要解释一下，就是如果你删除的数据库或者表是非空的，那么就需要你输入`确认`来防止你眼瞎误删，同时会输出当前对象内存在的东西，如果你还是不懂是什么意思的话，那就联系厂家，换号重开吧。
    - `删除 数据库 @DBID`
    - `删除 表 @TBID`
    - `删除 数据库 表 @DBID TBID`
  - 数据库不存在无法插入数据
    - `插入 数据库 表 @DBID TBID value...`
      > 这个就很明了了。数据库都不存在自然表都是瞎扯，你准备往哪插数据
  - 表不存在无法插入数据
    - `插入 数据库 表 @DBID TBID value...`
      > 这次数据库存在，但数据库里面没有该表，等等，这个好像在哪见过。。。就决定是你了，出来吧：`已选择的数据库中不存在目标表`，虽然这俩似乎一样，其实就是一样，但懒得改了。
    - `插入 表 @TBID value...`
      > 这个其实，emm好像这俩都可以放入`已选择的数据库中不存在目标表`这一栏中，但。。似乎这么写会不会更明了。
  - 表不存在无法查找数据
    - `查询 表 @TBID index`
    - `查询 @index`
    - `查询 数据库 表 @DBID TBID index`
    > 受难三兄弟集齐了，如果表TBID不存在的话，会触发这个BUG，如果你还在好奇指令`查询 @index`中怎么没有TBID的话，你知道一句好奇为什么没有TBID对一个22多岁的孩子会造成多大的心理伤害吗？
  - 数据库不存在无法查找数据
    - `查询 数据库 表 @DBID TBID index`
      > 如果，我是说如果，数据库不存在，你会不会觉得你很搞笑。
  - 表不存在无法显示数据
    - `显示 表 @TBID showNumber`
    - `显示 表 showNumber`
    - `显示 数据库 表 @DBID @TBID showNumber`
    > 都不存在了，扑盖啊，
  - 数据库不存在无法显示数据
    - `显示 数据库 表 @DBID @TBID showNumber`
    > 鸡毛? 数据库都选错了
  - 未选择表
    - `查询 index`
    - `显示 表 @showNumber`
    > 嘿，叼毛，你忘记选表了。
    >
    > LZTM千里迢迢从云南坐火车过来，2000公里啊，来了为了听你们叫我一声靓仔，你TM居然叫我叼毛？
- 日志记录指令集
  > 缩写类指令按照对应pwd进行补全后记录在日志中,所以还是花了一些心思的
  - 退出(不修改)
  - 选择
    - **选择** **数据库** _@DBID_
    - **选择** **数据库** **表** _@DBID_ _TBID_
  - 显示
    - **显示**
    - **显示** **数据库**
    - **显示** **数据库** _@DBID_
    - **显示** **数据库** **表** _@DBID_ _TBID_
  - 登录(不修改)
  - 创建
    - **创建** **用户** _@ID_ _Password_
    - **创建** **管理员**   _@ID_ _password_
    - **创建**  **数据库**  _@DBID_
    - **创建**  **数据库** **表**  _@DBID_ _TBID_
  - 删除
    - **删除**  **数据库**  _@DBID_
    - **删除** **数据库**  **表**  _@DBID_ _TBID_
    - **删除**  **用户**  _@UserName_
    - **删除**  **管理员**  _@managerID_
  - 插入
    - **插入** **数据库** **表** _@DBID_ _TBID_ _[value1 value2 ...]_
  - 查询
    - **查询** **数据库** **表** _@DBID_ _TBID_ _index_

## 视图层(正在实现)

- 综述
  > 视图层是在view中建立与database相同的文件建构，在对应表中记录允许的列，以及用户名，以实现对用户的视图进行限制
- 默认视图(全视图)
  > 默认状态下，管理员创建表，但并未对用户添加视图，也就是说./data/view下并未有视图记录，则会显示全部内容。其实也可以改成默认视图为空。本来想着要不在_super里放一个静态的开关，但又觉得没必要。反正代码估计只有我会看。也不存在复用。

## BUG记录

### linux下交叉编译windows程序

> 安装Mingw，CV大法:命令如下：

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

> 在读取文件的时候，读取到文件结尾后尝试使用seekg设置指针重新指向-1，但无法使用readline读取，诡异的是使用tellg返回的居然是设置后的-1。这使得我一脸蒙蔽

- 尝试1: 使用clear函数，无效。如果没有查询到eof重新设置seek有效，但并不知道是否到了eof。
- 尝试2: 既然最开始可以使用，那么不如关闭后重新打开。成功。如此每次setseek的时候，查看一下eof的状态。如果达到文件尾的时候，就close后重新open
