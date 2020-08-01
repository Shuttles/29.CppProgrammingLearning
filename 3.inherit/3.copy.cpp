/*************************************************************************
	> File Name: 3.copy.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月28日 星期二 20时44分53秒
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
    A() {
        cout << "class A default constructor" << endl;
        this->x = 0x01020304;
    }
    A(const A &a) {
        cout << "class A copy constructor : " << this << endl;
    }
    void say() {
        cout << "class A " << endl;
    }
    int x;
};

class B : public A {
public:
    B() {
        this->y = 0x05060708;
        cout << "class B default constructor" << endl;
    }
    B(const B &b) : A(b) {
        cout << "class B copy constructor : " << this << endl;
    }
    void func() {
        A::say();//加上A::
    }
    void say() {
        cout << "class B" << endl;
    }
    int y;
};

int main() {
    B b1;
    B b2(b1);
    b2.func();
    const char *msg = (const char *)(&b1);
    for (int i = 0; i < sizeof(B); i++) {
        printf("%X", msg[i]);
    }
    printf("\n");
    return 0;
}
