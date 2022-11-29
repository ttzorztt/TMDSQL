/*
 * @Description  : 测试库的使用
 * @Autor        : TMD
 * @Date         : 2022-11-21 09:21:28
 * @LastEditTime : 2022-11-29 23:03:33
 */
// C++多线程测试

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