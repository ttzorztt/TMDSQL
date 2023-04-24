/*
 * @Description  :
 * @Autor        : TMD
 * @Date         : 2023-04-24 20:13:40
 * @LastEditTime : 2023-04-24 21:07:10
 */
#include <iostream>
#include <vector>
using namespace std;
class C {
 private:
  /* data */
 public:
  C(/* args */);
  ~C();
  int a = 0;
};
class B {
 private:
  /* data */
 public:
  int a;
  B(C& d);
  ~B();
};

B::B(C& d) { a = 10; }

B::~B() {}


C::C(/* args */) {}

C::~C() {
    cout << "fsdff" << endl;
}

int main(int argc, char const *argv[]) {
  /* code */
  C d;
  B a(d);
  a.~B();
  d.~C();
  std::cout << d.a << std::endl;
  std::cout << a.a << std::endl;
  std::cout << "TMD" << std::endl;
  return 0;
}
