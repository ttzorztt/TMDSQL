/*
 * @Description  : 测试库的使用
 * @Autor        : TMD
 * @Date         : 2022-11-21 09:21:28
 * @LastEditTime : 2022-11-21 10:46:31
 */
// C++多线程测试

#include <iostream>
#include <thread>
#include <atomic> // 原子类型，可用于互斥访问
#include <mutex>
using namespace std;
std::atomic_int x; // 原子变量x
std::mutex y; // 互斥变量 Y

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
class th {
 private:
  /* data */
 public:
  th(/* args */);
  ~th();
  void add();
};

th::th(/* args */) {}

th::~th() {}

void f() {
  int x = 10;
  std::thread tha(funa);
  std::thread thb(funb, x);
  std::thread thc(func, std::ref(x));  // 传引用必须使用std::ref申明
  std::thread thd(fund, &x);

  thb.join();
  tha.join();
  thc.join();
  thd.join();
}
int main(int argc, char const* argv[]) {
//   f();
cout << std::thread::hardware_concurrency() << endl;
  return 0;
}