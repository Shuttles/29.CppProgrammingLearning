/*************************************************************************
	> File Name: 14.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月12日 星期三 09时35分13秒
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
#include <functional>
using namespace std;



namespace haizei {

template<typename RT, typename ...PARAMS> 
class Base {
public:
    virtual RT operator()(PARAMS...) = 0;//实现成虚函数，具体功能由子类实现
    virtual ~Base() {}
};

//包装普通函数的子类
template<typename RT, typename ...PARAMS>
class normal_func : public Base<RT, PARAMS...> {
public:
    typedef RT (*func_type)(PARAMS...);
    normal_func(func_type func) : ptr(func) {}
    virtual RT operator()(PARAMS...args) override {
        return this->ptr(args...);
    }
private:
    func_type ptr;
};

//包装函数对象的子类
template<typename C, typename RT, typename ...PARAMS>//C是对象的类型
class functor : public Base<RT, PARAMS...> {
public:
    functor(C &func) : ptr(func) {}
    virtual RT operator()(PARAMS...args) override {
        return this->ptr(args...);
    }
private:
    C &ptr;
};



template<typename RT, typename ...PARAMS> class function;
template<typename RT, typename ...PARAMS> 
class function<RT(PARAMS...)> {
public:
    function(RT (*func)(PARAMS...))
    : ptr(new normal_func<RT, PARAMS...>(func)) {
        cout << "normal_function constructor" << endl;
    }
    template<typename T>
    function(T &&a) 
    : ptr(new functor<typename remove_reference<T>::type, RT, PARAMS...>(a)) {
        cout << "function object constructor" << endl;
    }
    //调用ptr指针的operator()
    RT operator()(PARAMS... args) {
        this->ptr->operator()(args...);
    }
    ~function() {
        delete ptr;
    }
private:
    Base<RT, PARAMS...> *ptr;
};

}

void f(function<int(int, int)> g) {
    cout << g(3, 4) << endl;
}

int add(int a, int b) {
    return a + b;
}

struct MaxClass {
    int operator()(int a, int b) {
        return a > b ? a : b;
    }
};


int main() {
    MaxClass max;
    f(add);
    f(max);
    haizei::function<int(int, int)> g1(add);
    haizei::function<int(int, int)> g2(max);
    cout << g1(3, 4) << endl;
    cout << g2(3, 4) << endl;


    return 0;
}
