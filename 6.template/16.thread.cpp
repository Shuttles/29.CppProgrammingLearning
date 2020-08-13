/*************************************************************************
	> File Name: 16.thread.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月13日 星期四 11时49分03秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <thread>//内部实现用到了bind
using namespace std;

void func() {
    cout << "hello world!" << endl;
}

void func2(int x) {
    cout << x << " hello world!" << endl;
    return ;
}

void func3(int &x) {
    x += 1;//x称为临界资源，使用前得加锁，使用后得解锁
    cout << x << " hello world!" << endl;
}

int main() {
    thread t1(func);
    thread t2(func);
    thread t3(func);
    t1.join();
    t2.join();
    t3.join();

    cout << "-----------------------" << endl;
    thread t4(func2, 4);
    thread t5(func2, 5);
    thread t6(func2, 6);
    t4.join();
    t5.join();
    t6.join();

    cout << "-----------------------" << endl;
    int n = 0;
    thread t7(func3, ref(n));
    thread t8(func3, ref(n));
    thread t9(func3, ref(n));
    t7.join();
    t8.join();
    t9.join();
    cout << "n = " << n << endl;
    return 0;
}
