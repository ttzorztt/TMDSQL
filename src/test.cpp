/*
 * @Description  : 测试库的使用
 * @Autor        : TMD
 * @Date         : 2022-11-21 09:21:28
 * @LastEditTime : 2022-11-29 17:45:04
 */
// C++多线程测试

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
  while(1){
    std::lock_guard<std::mutex> locktmp(x);
    if(count > 100) break;
    if(js){
      std::cout << "进程1  ：" << count << std::endl;
      ++count;
      js = false;
    }
  }
}
void print_1(){
  while(1){
    std::lock_guard<std::mutex> locktmp(x);
    if(count > 100) break;
    if(!js){
      std::cout << "进程2  ：" << count << std::endl;
      ++count;
      js = true;
    }
  }
}
int main(){
  std::thread tha(print_0);
  std::thread thb(print_1);
  tha.join();
  thb.join();
}