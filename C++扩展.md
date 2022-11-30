# 单例模式
- 私有静态类对象
- 将构造函数设置为非公有访问方式
- 删除赋值和拷贝构造等函数等函数
- 静态公有方法返回静态类对象
- 类外初始化
## 设计方式之饥汉模式--直接构建
```c++
  #include <iostream>
  #include <mutex>
  #include <mutex>
  #include <condition_variable> // 同步原语，用于阻塞进程，直到另一线程修改共享变量(条件)
  using namespace std;
  class Obj{
    private:
    int value;
    static Obj instance;
    static int num;
    Obj(int x = 0): value(x){}
    Obj(const Obj& obj) = delete;
    Obj& operator=(const Obj& ob) = delete;
  public:
    static Obj& Create(){
      return instance;
    }
  };
  Obj Obj::instance(10);
  void funA(){
    Obj& objA = Obj::Create();
    cout << &objA << endl;
  }
  void funB(){
    Obj& objB = Obj::Create();
    cout << &objB << endl;
  }
  int main(){
    thread tha(funA);
    thread thb(funB);
    tha.join();
    thb.join();
  }
```
## 设计方式之懒汉模式--需要时构建
```c++
  #include <mutex>
  #include <condition_variable> // 同步原语，用于阻塞进程，直到另一线程修改共享变量(条件)

  using namespace std;
  std::mutex mut;
  class Obj{
    private:
    int value;
    static Obj* instance;
    Obj(int x = 0): value(x){}
    Obj(const Obj& obj) = delete;
    Obj& operator=(const Obj& ob) = delete;
  public:
    static Obj* Create(){
      std::lock_guard<std::mutex> lock(mut);   //加锁，防止线程冲突
      if(instance == NULL){
        instance = new Obj(10);
      }
      return instance;
    }
  };
  Obj* Obj::instance = NULL;
  int main(){
    Obj* objA = Obj::Create();
    Obj* objB = Obj::Create();
    cout << &objA << endl << &objB << endl;
  }
```


# 多线程
## 编译方式
> 在linux中，需要添加参数 -lpthread, 即最终编译方式为:
```bash
g++ test.cpp -lpthread -o test
 ```
## `<thread>`
```C++
  #include <thread>
  void funa() {
    cout << "fun()" << endl;
  }
  void funb(int x) {
    cout << "funb(int)" << endl;
  }
  void func(int& x) {
    cout << "func(int&)" << endl;
  }
  void fund(int* x) {
    cout << "fund(int*)" << endl;
  }
  int main(){
    int x = 10;
    std::thread tha(funa);
    std::thread thb(funb, x);
    std::thread thc(func, std::ref(x));  // 传引用必须使用std::ref申明
    std::thread thd(fund, &x);
    thb.join(); 
    tha.join();
    thc.join();
    thd.join();
      return 0;
  }
```
  - 构造函数
  > 需要注意的是： 当线程函数的参数是以引用的方式，需要用 std::ref()进行声明
  - join()
  > join函数的功能是等待线程结束。
> 输出紊乱，由于进程宏观上是同时运行的。所以输出会紊乱
## `<atomic>`
> 原子变量，可以达到互斥访问的效果
```C++
  #include <atomic>
  #include <thread>
  std::atomic_int x;
  std::atomic<int> x; // 与前者效果相同
```

## `<mutex>`
```C++
  #include<mutex>
  std::mutex y; // 普通锁
  std::recursive_mutex m; // 递归锁，从某种意义上来说有计数在其中，就是可以在多次加锁
  std::lock_guard<std::mutex> xx(y); //基于作用域的互斥所有权包装器，当对象申请成功，则说明加锁成功，释放锁在作用域结束之后释放锁， 提供互斥包装器
  std::unique_lock<std::mutex> x1(y); // 可移动的互斥所有权包装器
```
- 基本函数
  - lock() 
  > 加锁
  - unlock()
  > 删锁
  - try_lock()
  > 尝试加锁

## `<condition_variable>`

- wait函数
> wait函数的主要功能就是先将该进程阻塞，然后在释放锁
```C++
  #include <iostream>
  #include <thread>
  #include <atomic> // 原子类型，可用于互斥访问
  #include <mutex>
  #include <condition_variable> // 同步原语，用于阻塞进程，直到另一线程修改共享变量(条件)

  using namespace std;
  std::mutex mx;
  std::condition_variable cv; // 条件变量
  int isReady = 0;
  const int n = 10;
  void printfA(){
    std::unique_lock<std::mutex> lock(mx);
    int i = 0;
    while(i < n){
      while (isReady != 0){
        cv.wait(lock); // 阻塞
      }
      std::cout << "A" << endl;
      isReady = 1;
      ++i;
      cv.notify_all(); //唤醒所有等待条件变量的线程
    }
  }
  void printfB(){
    std::unique_lock<std::mutex> lock(mx);
    int i = 0;
    while(i < n){
      while (isReady != 1){
        cv.wait(lock);
      }
      std::cout << "B" << endl;
      isReady = 2;
      ++i;
      cv.notify_all(); //唤醒所有等待条件变量的线程
    }
  }
  void printfC(){
    std::unique_lock<std::mutex> lock(mx);
    int i = 0;
    while(i < n){
      while (isReady != 2){
        cv.wait(lock);
      }
      std::cout << "C" << endl;
      isReady = 0;
      ++i;
      cv.notify_all(); //唤醒所有等待条件变量的线程
    }
  } 

  int main(){
    thread tha(printfA);
    thread thb(printfB);
    thread thc(printfC);
    tha.join();
    thb.join();
    thc.join();
    return 0;
  }
```
> 十次循环打印ABC，达到线程通信。
>

## 死锁
- 互斥
- 占有等待
- 不可抢占
- 循环等待
### 避免死锁
```C++
  // 同时获取xy才会加锁
  std::mutex x;
  std::mutex y;
  void func(){
    std::unique_lock<std::mutex> lockx(x,std::defer_lock); 
    std::unique_lock<std::mutex> locky(y,std::defer_lock);
    std::lock(lockx,locky);
    //
  }
```

- 例子: 两个进程分别打印奇数和偶数
```c++
  #include <iostream>
  #include <thread>
  #include <atomic> // 原子类型，可用于互斥访问
  #include <mutex>
  #include <condition_variable> // 同步原语，用于阻塞进程，直到另一线程修改共享变量(条件)

  using namespace std;

  std::mutex x;
  std::condition_variable cv;
  bool js = 0;
  int count = 0;
  void print_0(){
    while(count <= 100){
      std::unique_lock<std::mutex> locktmp(x);
      while(!js){
        cv.wait(locktmp);
      }
      if(js && count <= 100){
        std::cout << "进程1  ：" << count << std::endl;
        ++count;
        js = false;
      }
      cv.notify_all();
    }
  }
  void print_1(){
    while(count <= 100){
      std::unique_lock<std::mutex> locktmp(x);
          while(js){
        cv.wait(locktmp);
      }
      if(!js && count <= 100){
        std::cout << "进程2  ：" << count << std::endl;
        ++count;
        js = true;
      }
      cv.notify_all();
    }
  }
  int main(){
    std::thread tha(print_0);
    std::thread thb(print_1);
    tha.join();
    thb.join();
  }
```
- 生产者消费者
```C++
  #include <condition_variable>  // 同步原语，用于阻塞进程，直到另一线程修改共享变量(条件)
  #include <iostream>
  #include <mutex>
  #include <queue>
  #include <chrono> //时间
  #include <thread>
  using namespace std;
  std::mutex mut;
  const int MAXCOUNT = 20;
  const int BUFFSIZE = 5;
  std::condition_variable cv;
  std::queue<int> myque;
  // 生产者
  void input(int value){
    std::unique_lock<std::mutex> tmp(mut);
    while(myque.size() >= BUFFSIZE){
      cv.wait(tmp);
    }
    cout << "生产者生产: " << value << endl;
    myque.push(value);
    cv.notify_all();
  }
  int output(){
    std::unique_lock<std::mutex> tmp(mut);
    while(myque.empty()){
      cv.wait(tmp);
    }
    int ret = myque.front();
    cout << "消费者消费  " << ret << endl;
    myque.pop();
    cv.notify_all();
    return ret;
  }

  void p() {
    int value = 0;
    for(int a =0; a < 20; ++a){
      input(value);
      ++value;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
  }

  // 消费者
  void c() {
    for(int a =0; a < 20; ++a){
      output();

    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    }
  }
  int main() {
    std::thread tha(p);
    std::thread thb(c);
    tha.join();
    thb.join();
  }
```

# 线程池
> 线程池技术通过在系统中预先创建一定数量的线程，当任务请求到来时从线程池中分配一个预先创建的线程去处理任务，线程在处理完任务之后还可以重用，不会销毁，而是等待下一个任务的到来。
- 一个好处是：对于多核处理器，由于线程会被分配到多个CPU，会提高并行处理的效率
- 另一个好处是：每个线程独立堵塞，可以防止主线程被阻塞而使主线程被阻塞，导致其他的请求得不到响应的问题。
- 可以避免大量的线程创建和销毁动作，从而节省系统资源。