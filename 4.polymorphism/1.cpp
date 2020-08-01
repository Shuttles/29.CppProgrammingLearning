/*************************************************************************
	> File Name: 1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月01日 星期六 15时51分11秒
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

class Animal {
public:
    virtual void runI() {//虚函数
        cout << "I do not know how to run." << endl;
    }
};

class Cat : public Animal {
public:
    void runI() override {
        cout << "I can run with four legs." << endl;
    }
};

class Dog : public Animal {
public:
    void runI() override {
        cout << "I can run with four legs, tail yao a yao!" << endl;
    }
};

class Bat : public Animal {
public:
    void runI() override {
        cout << "I can fly!" << endl;
    }
};

int main() {
    srand(time(0));
    Cat a;
    Animal &b = a;
    Animal *c[10];
    for (int i = 0; i < 10; i++) {
        int op = rand() % 3;
        switch (op) {
            case 0: c[i] = new Cat(); break;
            case 1: c[i] = new Dog(); break;
            case 2: c[i] = new Bat(); break;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        c[i]->runI();//运行时状态！
    }

    return 0;
}
