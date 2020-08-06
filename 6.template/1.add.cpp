/*************************************************************************
	> File Name: 1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月06日 星期四 11时46分01秒
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


class A {
public:
    A(int x) : x(x) {}
    int x;
};

class B {
public:
    B(int y) : y(y) {}
    int y;
};

int operator+(const A &a, const B &b) {
    return a.x + b.y;
}


/*
template<typename T, typename U>
decltype(T() + U()) add(T a, U b) {
    return a + b;
}*/

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {//typeof的升级版
    return a + b;
}

int main() {
    A a(1000);
    B b(645);
    cout << a + b << endl;
    cout << add(a, b) << endl;
    cout << add(2, 3) << endl;
    cout << add(2.3, 4.3) << endl;
    cout << add(2.3, 5) << endl;
    cout << add(5, 2.3) << endl;
    cout << add(string("hello"), string(" world")) << endl; 

    cout << max(4, 3) << endl;
    cout << max(4.3, 3) << end;

    return 0;
}
