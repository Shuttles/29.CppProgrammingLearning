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

class People {
    friend int main();
    int x, y;
    string name;
public:
    People(string name);
    void set(int x);
    void say();
};

People::People(string _name) {
    this->name = _name;
}

void People::set(int x) {
    cout << "set function : " << this << endl;
    this->x = x;//this指针指向当前对象
    return ;
}

void People::say() {
    cout << "My name is " << name << endl;
    return ;
}

int main() {
    People a("hug");
    People b = string("czy");
    a.say();
    b.say();
    return 0;
}
