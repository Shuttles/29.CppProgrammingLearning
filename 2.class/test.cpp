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
public:
    People(string name) {
        cout << "string param constructor : " << this << endl;
        this->name = name;
    }

    People(const People &a) {
        cout << "copy constructor : " << this << endl;
        this->name = a.name;
    }
    ~People() {
        cout << "destructor : " << this << endl;
    }

private:
    string name;
};


People func() {
    People temp_a("czy");
    return temp_a;
}


int main() {
    People a = func();
    return 0;
}
