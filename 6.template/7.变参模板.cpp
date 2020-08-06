/*************************************************************************
	> File Name: 2.my_max.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月06日 星期四 12时18分30秒
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

namespace haizei {
template<typename T, typename U>
auto max(T a, U b) -> decltype(a > b ? a : b) {//decltype是typeof的升级版
    return (a > b ? a : b);    
}

template<typename T, typename U>
    auto min(T a, U b) -> decltype(a > b ? b : a) {//decltype是typeof的升级版
    return (a > b ? b : a); //min也用>实现   
}

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T, typename U>
auto add(T *a, U *b) -> decltype(*a + *b) {
    return add(*a, *b);
}

template<>
int add(int a, int b) {
    cout << "add int : " << a << " " << b << endl;
    return a + b;
}

template<typename T>
class FoolPrintAny {
public:
    void operator()(const T &a) {
        cout << a << endl;
    }        
};


template<>
class FoolPrintAny<int> {
public:
    void operator()(const int &a) {
        cout << "naughty : " <<  2 * a << endl;
    }        
};


template<typename T> 
void printAny(const T &a) {
    cout << a << endl;
    return ;
}

//变参模板
template<typename T, typename ...ARGS> 
void printAny(const T &a, ARGS...args) {
    cout << a << " ";
    printAny(args...);
    return ;
}

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS> 
class Test<T(ARGS...)> {
public:
    T operator()(
        typename ARGS<ARGS...>::__tpye a, 
        typename ARGS<ARGS...>::__rest::__type b) {
        return a + b;
    }
};

}


int main() {
    haizei::FoolPrintAny<string> f;
    f("hello world!");
    haizei::FoolPrintAny<int> f2;
    f2(123);
    int n = 45, m = 67;
    int *p = &n, *q = &m;
    cout << haizei::add(n, m) << endl;
    cout << haizei::add(p, q) << endl;

    cout << "----------------------" << endl;
    haizei::printAny(123, 34.5, "hello world!", &n);
    haizei::Test<int(int, int)> f3;
    cout << f3(3, 4) << endl;
    return 0;
}
