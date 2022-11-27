/*
 * @Description  : 测试库的使用
 * @Autor        : TMD
 * @Date         : 2022-11-21 09:21:28
 * @LastEditTime : 2022-11-27 18:09:07
 */
// C++多线程测试

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
      cv.wait(lock);
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