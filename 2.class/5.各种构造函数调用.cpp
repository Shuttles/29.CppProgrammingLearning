/*************************************************************************
	> File Name: 5.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月27日 星期一 17时00分05秒
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
private:
    int age;
    string name;
public:
    People() {
        cout << "constructor" << endl;
    }
    People(string name) {
        cout << "string param constructor" << endl;
        this->age = 18;
        this->name = name;
    }
    People(int age, string name) {
        cout << "int string param constructor" << endl;
        this->age = age;
        this->name = name;
    }
    People(const People &p) {
        cout << "copy constructor" << endl;
        this->age = p.age;
        this->name = p.name;
    }
    void operator=(const People &p) {
        cout << "operator=" << endl;
        this->age = p.age;
        this->name = p.name;
    }

    ~People() {
        cout << "destructor" << endl;
    }
};


int main() {
    People a;//调用默认构造函数
    cout << "------------------------------------" << endl;
    People b(20, "Shuttles");//调用有参构造函数
    cout << "------------------------------------" << endl;
    People c(b);//调用拷贝构造函数
    cout << "------------------------------------" << endl;
    People d = b;//调用拷贝构造函数


    cout << "------------------------------------" << endl;
    People e("wangjialong");//调用转换构造函数
    cout << "------------------------------------" << endl;
    e = b;//调用operator=，即赋值运算符

    return 0;
}
