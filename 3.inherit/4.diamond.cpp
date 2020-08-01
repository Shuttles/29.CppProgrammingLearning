/*************************************************************************
	> File Name: 4.diamond.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月01日 星期六 15时13分12秒
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

struct A {
    int x;

};

struct B : virtual public A {
    void set(int x) {
        this->x = x;
        cout << "set : &this->x = " << &this->x << endl;
    }    
};

struct C : virtual public A {
    int get() { 
        cout << "get : &this->x = " << &this->x << endl;
        return this->x; 
    }

};


struct D : public B, public C {
    
};

int main() {
    D d;
    cout << sizeof(d) << endl;
    d.set(9973);
    cout << d.get() << endl;
    return 0;
}
