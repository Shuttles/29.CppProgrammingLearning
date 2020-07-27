/*************************************************************************
	> File Name: 8.operator3.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月27日 星期一 20时04分25秒
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
        arr = new int[10];
    }
    A(const A &a) : A() {//这样实现　就是深拷贝，否则系统默认的是浅拷贝
        for (int i = 0; i < 10; i++) {
            this->arr[i] = a.arr[i];
        }
        this->x = a.x, this->y = a.y;
    }
    int x, y;
    int *arr;
};

class B {
public:
    B() : obj(nullptr){
        arr = new int[10];
        arr[3] = 9973;
    }
    B(A *obj) : B() {
        this->obj = obj;
    }
    int operator()(int a, int b) {
        return a + b;
    }
    int &operator[](int ind) {//必须返回引用，否则51行会报错
        return arr[ind];
    }
    void operator[](const char *msg) {
        cout << msg << endl;
        return ;
    }
    A *operator->() {//当成单目运算符
        return obj;
    }
    A &operator*() {
        return *obj;
    }

    ~B() { delete arr; }
private:
    int *arr;
    A *obj;
};

ostream &operator<<(ostream &out, const A &a) {
    out << "A(" << a.x << ", " << a.y << ")";
    return out;
}

int main() {
    B add;
    cout << add(3, 4) << endl;//函数对象
    cout << add[3] << endl;//数组对象

    add[3] = 8876;
    cout << add[3] << endl;

    add["hello world"];

    /*
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        //iter不是指针，是个指针对象，只是表现的像个指针
    } */

    A a, b(a);
    a.x = 67, a.y = 99;
    B p = &a;
    
    cout << p->x << " " << p->y << endl;

    cout << *p << endl;




    a.arr[3] = 9973;
    b.arr[3] = 6687;
    cout << a.arr[3] << endl;
    cout << b.arr[3] << endl;

    return 0;
}
