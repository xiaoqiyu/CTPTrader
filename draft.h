#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>

std::mutex mtx;        // 全局互斥锁
std::queue<int> que;   // 全局消息队列
std::condition_variable cr;   // 全局条件变量
int cnt = 1;           // 数据

void producer() {
	while(true) {
		{
			std::unique_lock<std::mutex> lck(mtx);
			// 在这里也可以加上wait 防止队列堆积  while(que.size() >= MaxSize) que.wait();
			que.push(cnt);
			std::cout << "向队列中添加数据：" << cnt ++ << std::endl;
            sleep(2);
			// 这里用大括号括起来了 为了避免出现虚假唤醒的情况 所以先unlock 再去唤醒
		}
		cr.notify_all();       // 唤醒所有wait
	}
}

void consumer() {
	while (true) {
		std::unique_lock<std::mutex> lck(mtx);
		while (que.size() == 0) {           // 这里防止出现虚假唤醒  所以在唤醒后再判断一次
			cr.wait(lck);
		}
		int tmp = que.front();
		std::cout << "从队列中取出数据：" << tmp << std::endl;
		que.pop();
        sleep(2);
	}
}

int thread_test()
{
	std::thread thd1[2], thd2[2];
	for (int i = 0; i < 2; i++) {
		thd1[i] = std::thread(producer);
		thd2[i] = std::thread(consumer);
		thd1[i].join();
		thd2[i].join();
	}
	return 0;
}

void test(const char *b)
{
    char a[10];
    std::strcpy(a, b);
    std::cout<<a<<b<<std::endl;
}

void test_str()
{
	std::string a="abc";
    char d[10]={"abc"};
    char *aa = new char[10];
    strcpy(aa,a.c_str());
    // std::cout<<d[1]<<d[7]<<std::endl;
    // test(a.c_str());
    test(d);
    test(aa);
    test(a.c_str());

	std::string s = "abc";
    std::string ss;
    char *ptr = const_cast<char*>(s.c_str());
    char cc[10] ={'\0'};
    strcpy(cc, ptr);
    std::cout<<cc<<","<<*(ptr+1)<<std::endl;

}