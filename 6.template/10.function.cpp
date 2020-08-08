/*************************************************************************
	> File Name: 10.function.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月08日 星期六 15时25分35秒
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

void f(function<int(int, int)> g) {
    cout << g(3, 4) << endl;
}

int add(int a, int b) {
    return a + b;
}

struct MaxClass {
    int operator()(int a, int b) {
        return a > b  ? a : b;
    }
};

namespace haizei {

template<typename RT, typename ...PARAMS>
class base {
public:
    virtual RT operator()(PARAMS...) = 0;
};



template<typename RT, typename ...PARAMS> 
class normal_func : base<RT, PARAMS...> {
public:
    typedef RT (*func_type)(PARAMS...);
    normal_func(func_type func) : ptr(func) {
    
    }
    virtual RT operator()(PARAMS... args) override {
        return this->ptr(args...);
    } 
private:
    func_type ptr;
};


template<typename RT, typename ...PARAMS> class function;
template<typename RT, typename ...PARAMS> 
class function<RT(PARAMS...)> {
public:
    function(RT (*func)(PARAMS......)) 
    : ptr(new normal_func<RT, PARAMS...>(func)){
        cout << "normal function constructor" << endl;                               
    }
    template<typename T>
    function(T &&a)
    : ptr(new functor<typename remove_reference<T>::type, RT, PARAMS...>(a)){
        cout << "function object constructor" << endl;
    }

    RT operator()(PARAMS... args) {
        return this->ptr->operator()(args...);
    }
    ~function() {
        delete this->ptr;
    }
private:
    base<RT, PARAMS...> *ptr;
};

}

int main() {
    MaxClass max;
    f(add);
    f(max);

    haizei::function<int(int, int)> g1(add);
    haizei::function<int(int, int)> g2(max);
    return 0;
}
