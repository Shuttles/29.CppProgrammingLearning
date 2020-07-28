/*************************************************************************
	> File Name: 2.constructor.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月28日 星期二 19时55分41秒
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


class D {
public:
    D() { cout << "D constructor" << endl; }
    ~D() { cout << "D destructor" << endl; }
};

class A {
public:
    A() = delete;
    A(int x, int y) { cout << "A constructor" << endl; }
    ~A() { cout << "A destructor" << endl; }
};

class B {
public:
    B() { cout << "B constructor" << endl; }
    ~B() { cout << "B destructor"  << endl;}
};

class C : public D {
public:
    C() : b(), a(3, 4) { cout << "C constructor" << endl; } //初始化列表规定不了属性初始化顺序，只跟在类中声明的顺序有关
    ~C() { cout << "C destructor" << endl; }
    
private:
    A a;
    B b;
};

int main() {
    C c;

    return 0;
}
