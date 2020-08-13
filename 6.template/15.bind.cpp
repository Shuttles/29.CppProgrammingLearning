/*************************************************************************
	> File Name: 15.bind.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月13日 星期四 11时17分58秒
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
#include <functional>
using namespace std;

int add(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return a + b;
}

int add2(int a, int b, int c) {
    cout << a << "  " << b << "  " << c << endl;
    return a + b + c;
}

int add_cnt(function<int(int, int)> func, int &n, int a, int b) {
    n += 1;
    return func(a, b);
}

int main() {
    function<int(int)> f1 = bind(add, 5, placeholders::_1);
    f1(3), f1(4), f1(5);
    function<int(int, int)> f2 = bind(add, placeholders::_1, placeholders::_2);
    f2(3, 4), f2(5, 6), f2(7, 8);

    function<int(int, int)> f3 = bind(add2, placeholders::_2, 6, placeholders::_1);
    f3(9, 10);

    //绑定一个可以统计函数执行次数的方法
    int n = 0;
    function<int(int, int)> f5 = bind(add_cnt, add, ref(n), placeholders::_1, placeholders::_2);
    f5(99, 88);
    f5(92, 80);
    f5(95, 78);
    cout << n << endl;
    return 0;
}
