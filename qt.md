
# QT

- `QWidget`是一个通知框，没有没有最上面的类似文件、编辑框，且只有关闭按钮，没有初始化按钮。
  - 在QT中，和vue等框架类似，需要在指定的地方编写代码，在一个框架搭好的地方调用框架。

    ```c++
        #include <QPushButton> 
        QPushButton *button = new QPushButton; // 按钮对象
        button->show(); // show函数默认用顶层的方式弹出，就会独立一个创建弹出
        button->setParent(this);  // 设置在哪个窗口上显示
        button->move(100,100);// 移动位置
        button->setText("测试文本");
        button->resize(100,60); //设置按钮大小
        this->resize(1000,2000); // 设置窗口大小
        this->setWindowTitle("df"); // 设置标题
        this->setFixedSize(1000,1000); // 设置固定窗口
        // 信号和槽的链接，四个参数：发送者，发送的信号，信号的接受者，处理槽函数：
        // 而这就将关闭按钮集合到了button中
        connect(button,&QPushButton::clicked,this,&QWidget::close); 
    ```

- 信号和槽
  - 信号
  
    ```c++
    //A.h
    signals: //是信号申明，和public类似
      /**
      1.信号是已返回void的函数形式给出
      2.信号只需申明，不需实现
      3.自定义信号可以发生重载
      */
      void el();
      void el(QString foodname);

      void emitel();// 触发函数，触发信号
      void emitel(QString foodname);
    ```

    ```c++
    //A.cpp
    void A::emitel(){
      emit el(); //触发关键字 emit,且以函数的形式给出
    }
    void A::emitel(QString foodname){
      emit el(foodname);
    }

    ```

  - 槽

    ```c++
    //B.h
      public slots: //槽函数的访问符，用法同public类似
      /**
      1.返回值void
      2.需要申明，也需要实现
      3.也可以发生重载
      */
      void treat();
      void treat(QString foodname);
    ```

    ```c++
      //B.cpp
      #include <QDebug> // 在qt中，需要使用qDebug来输出
      void B::treat(){
        qDebug() << "槽函数运行" <<endl;
      }
      void B::treat(QString foodname){
        // 这里将QString转为QByteArray类型，然后再转为char*
        qDebug() << "槽函数运行，传入参数为:" << foodname.toUtf8().data() << endl;
      }
    ```

  - 信号和槽的链接

    ```c++
    A*a = new A;
    B*b = new B;
    // 四个参数，触发者(指针)，触发的信号(地址)，接受者(指针)，槽函数(地址)
    connect(a,&A::el,b,&B::treat);

    void(A::*aSignals)(QString) = &A::el; // 指向成员函数的指针(去掉A后是指向全局函数的指针)
    void(B::*bslot)(QString) = &B::treat; //当然这是为了解决重载中connect函数无法区分重载函数，完全可以不重载，稍微改一下函数名就可以。
    connect(a,aSignals,b,bslot); // 这里链接的就是两个有参数的信号和槽
    ```

  - 信号和槽断开链接

  ```c++
  disconnect(a,&A::el,b,&B::treat);
  disconnect(a,aSignals,b,bslot);
  ```

  - 扩展
    - 信号可以链接信号
    - 一个信号可以链接多个槽函数
    - 多个信号可以链接同一个槽函数
    - **信号和槽的参数必须一一对应**

## Lambda表达式

- 基本构成

  ```c++
  [1](2)3 -> 4{
  5
  }
  ```

  - 1是函数对象参数，必须存在，不能省略，是传递给编译器自动生成的函数对象类的构造函数。有以下形式
    - 空，没有使用任何函数参数。
    - =，函数体内可以使用所在范围内的所有局部变量(包括lambda所在类的this)，并且是以**值传递**
    - &, 与上一个差不多，区别在于**引用传递**
  - 3是可修改标识符，默认是连拷贝都不允许你修改的，但是在3的地方添加`mutable`关键字，也许你修改拷贝，但注意只是拷贝，与原值无关。
  - 4返回值类型
- lambda的调用

  ```c++
  int n = 10;
  n = []()->int{return 1000;}();
  qDebug() << "n = " <<n ;
  ```

  > 整个Lambda表达式需要调用

## 菜单栏的创建

  ```c++
    #include<QMenuBar>
    QMenuBar * menu = menuBar(); //菜单栏
    setMenuBar(menu); // 将菜单栏放入窗口
    QMenu* fileMenu = menu->addMenu("文件"); // 添加菜单
    QAction* fileCreate = fileMenu->addAction("新建"); // 添加菜单项
    fileMenu->addSeparator(); // 添加分割线
    QAction* fileopen = fileMenu->addAction("打开"); // 添加菜单项
  ```

## 工具栏

  ```c++
    #include<QToolBar>
    // 工具栏可以有多个
    QToolBar* toolbar = new QToolBar(this); //工具栏
    // 放入窗口
    addToolBar(Qt::LeftToolBarArea,toolbar);
    QAction* tool1 = toolbar->addAction("工具1");
    toolbar->addSeparator();//添加分隔符
    QAction* tool2 = toolbar->addAction("工具2");
    // 只允许左右停靠
    toolbar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    // 设置浮动
    toolbar->setFloatable(false);
    // 移动始能控制，如果关闭则其他允许停靠或浮动都是扯淡，优先级最高
    toolbar->setMovable(false);
  ```

## 状态栏

  ```c++
    #include <QStatusBar>
    //状态栏
    QStatusBar* status = statusBar();
    // 放入窗口
    setStatusBar(status);
    // 放入标签
    QLabel* label = new QLabel("测试状态栏",this);
    // 放入状态栏(从左往右方)
    status->addWidget(label);
    QLabel* label2 = new QLabel("测试状态栏",this);
    status->addPermanentWidget(label2);
  ```

## 铆接部件

  ```c++
    #include <QDockWidget>
      //铆接部件 浮动窗口
    QDockWidget* dock = new QDockWidget("测试铆接部件",this);
    // 添加到窗口
    addDockWidget(Qt::RightDockWidgetArea,dock);
    // 设置停靠范围
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
  ```

## 核心窗口

  ```c++
    // 不一定是文本框
    #include <QTextEdit>
      // 核心窗口
    QTextEdit* edit = new QTextEdit(this);
    setCentralWidget(edit);
  ```

## 资源文件的添加

- 首先在QT项目中右击，`Add new` -> `Qt` ->  `Qt Resource File`, 然后将file名添加到对应的cmake文件内
- 然后右击项目中新出现的.qrc文件， `open in editor`
  - `Add Prefix`可以类似看成新建前缀，就是一个简单分类的作用
  - `Add Files` 是正式在该前缀下存放文件的按钮。一般再将资源文件拷贝到项目目录下。
  - 然后重新构建项目，当.qrc文件右下角出现下拉提示的时候，操作正确。
  - 然后使用资源文件的时候，方法为:`: + 前缀 + 文件名`
  
  ```c++
  fileCreate->setIcon(QIcon(":/media/1.jpg")); // '/'为前缀，media/1.jpg是文件名
  ```

## 对话框的创建

- 模态对话框
  > 在弹出模态对话框的时候，不允许你再对原来的窗口操作

```c++
  QDialog dlg(this);
  dlg.exec();   // 阻塞之后函数无法实行，直到关闭弹窗
```

- 非模态对话框
  > 允许对原来的窗口操作

```c++
  QDialog *dlg = new QDialog(this);
  dlg->setAttribute(Qt::WA_DeleteOnClose); // 设置关闭时释放
  dlg->show();
```
