/*************************************************************************
	> File Name: test.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2021年03月29日 星期一 11时42分20秒
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
        cout << "A default constructor" << endl; 
        this->x = 0x01020304;
    }
    A(const A &a) { 
        cout << "A copy constructor : " << this << endl; 
    }
    void say() {
        cout << "class A" << endl;
    }
    int x;
};

class B : public A {
public:
    B() { 
        cout << "B default constructor" << endl; 
        this->y = 0x05060708;
    }
    B(const B &b) : A(b) {
        cout << "B copy constructor : " << this << endl;
    }
    void func() {
        A::say();
    }
    void say() {
        cout << "class B" << endl;
    }
    int y;
};


int main() {
    B b1;
    B b2(b1);
    
    cout << "&b1 = " << &b1 << endl;
    cout << "&b2 = " << &b2 << endl;

    /*
    const char *msg = (const char *)(&b1);
    for (int i = 0; i < sizeof(B); i++) {
        printf("%X", msg[i]);
    }
    printf("\n");
    */
    return 0;
}
