/*************************************************************************
	> File Name: test.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2021年03月20日 星期六 21时00分45秒
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
using namespace std;

class Clock {
public:
    Clock() {
        second = 0, minute = 0, hour = 0;
    }
    Clock(int newS, int newM, int newH);//重载
    void setTime(int newS = 0, int newM = 0, int newH = 0) {
        second = newS;
        minute = newM;
        hour = newH;
    }
    void showTime();

private:
    int second, minute, hour;
};

void Clock::showTime() {
    cout << hour << ":" << minute << ":" << second << endl;
    return ;
}

Clock::Clock(int newS, int newM, int newH) {
    second = newS, minute = newM, hour = newH;
}


int main() {
    Clock clock_1, clock_2(59, 10, 21);
    clock_1.showTime();
    clock_2.showTime();
    return 0;
}
