/*************************************************************************
	> File Name: 4.final.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月02日 星期日 19时49分01秒
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

class A : public map<int, int> {
public:
    virtual void say() {
        cout << "class A : hello world!" << endl;
    }
};

class B final : public A {
public:
    void say() final override {
        cout << "Class B : hello world!" << endl;
    }
};

/*
class C : public B {
public:
    
    void say() override {
        cout << "class C : hello world!" << endl;
    }
};*/


int main() {
    A arr;
    arr[1] = 123;
    arr[3242] = 641;
    for (auto iter : arr) {
        cout << iter.first << ", " << iter.second << endl;
    }

    return 0;
}
