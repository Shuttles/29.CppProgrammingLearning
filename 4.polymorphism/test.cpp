/*************************************************************************
	> File Name: test.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2021年03月29日 星期一 14时34分27秒
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
    virtual ~A() {}

private:
};

class B : public A {
public:
    void sayB() {
        cout << "this is class B, x = " << x << endl;
    }
    int x;
};

class C : public A {
public:
    void sayC() {
        cout << "this is class C, x = " << x << endl;
    }
    double x;
};

class D : public A {
public:
    void sayD() {
        cout << "this is class D, x = " << x << endl;
    }
    string x;
};


int my_dynamic_cast(A *ta) {
    char **pa = (char **)(ta);
    char **pb = (char **)(new B());
    char **pc = (char **)(new C());
    char **pd = (char **)(new D());
    int ret = 1;
    if (pa[0] == pb[0]) ret = 0;
    else if (pa[0] == pc[0]) ret = 1;
    else if (pa[0] == pd[0]) ret = 2;
    return ret;
}

int main() {
    srand(time(0));
    A *pa;
    B *pb;
    C *pc;
    D *pd;
    switch (rand() % 3) {
        case 0: pb = new B(); pa = pb, pb->x = 123; break;
        case 1: pc = new C(); pa = pc, pc->x = 45.6; break;
        case 2: pd = new D(); pa = pd, pd->x = "hello world"; break;
    }

    if (pb = (dynamic_cast<B *>(pa))) {
        cout << "Class B : ";
        pb->sayB();
    } else if (pc = (dynamic_cast<C *>(pa))) {
        cout << "Class C : ";
        pc->sayC();
    } else if (pd = (dynamic_cast<D *>(pa))) {
        cout << "Class D : ";
        pd->sayD();
    }
    

    return 0;
}
