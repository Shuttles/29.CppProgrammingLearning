/*************************************************************************
	> File Name: 4.RVO.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月26日 星期日 21时10分51秒
 ************************************************************************/

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
        cout << "string param constrcutor" << endl;
        this->name = name;
    }
    People(const People &a) {
        cout << "copy constrcutor" << endl;
        this->name = a.name;
    }

private:
    string name;
};


People func() {
    People temp_a("hug");
    return temp_a;
}

int main() {
    People a = func();

    return 0;
}
