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


//ARG类
template<int n, typename T, typename ...ARGS>//解析第n项
class ARG {
public:
    typedef typename ARG<n - 1, ARGS...>::__type   __type;
};

template<typename T, typename ...ARGS>
class ARG<0, T, ARGS...> {
public:
    typedef T __type;
};


//这段删了没问题？！应该是不能删的！
template<typename T>
class ARG<0, T> {//虽然知道这个地方是模板类的偏特化，但是还是不太懂86行
public:
    typedef T __type;
};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS> 
class Test<T(ARGS...)> {
public:
    T operator()(ARGS... args) {
        return add<T>(args...);
    }
private:
    template<typename T1, typename U, typename ...US>
    T1 add(U a, US ...args) {
        return a + add<T1>(args...);
    }
    template<typename T1, typename U>
    T1 add(U a) {
        return a;
    } 
}
;

template<typename T, typename U>
T test_param_func(U a) {
    return T(a * 2);
}

void func2(int (*func)(double)) {
    cout << func(2.3) << endl;
}

/*
template<typename T>
T add2(T &a, T &b) {
    T c = a + b;
    return c;
}*/

template<typename T> struct remove_reference {
    typedef T type;
};


template<typename T> struct remove_reference<T &> {
    typedef const T &  type;
};

template<typename T> struct remove_reference<T &&> {
    typedef T type;
};

template<typename T>
typename remove_reference<T>::type add2(T &&a, T &&b) {
    typename remove_reference<T>::type c = a + b;
    return c;
}

/*
template<typename T, typename ...ARGS> 
class Cat {
public:
    string __name;
};

template<typename T> 
class Cat<T> {//必须得声明成偏特化版本,普通模板类不能重名！！！
public:
    int __age;
};*/



}//end of haizei


int main() {
    int inta = 123, intb = 456;
    cout << haizei::add2(inta, intb) << endl;

    cout << "----------------------" << endl;
    cout << haizei::add2(123, 456) << endl;

    cout << "----------------------" << endl;
    haizei::func2(haizei::test_param_func);

    cout << "----------------------" << endl;
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

    /*
    cout << "----------------------" << endl;
    haizei::Test<int(int, int)> f3;
    cout << f3(3, 4) << endl;
    */


    cout << "----------------------" << endl;
    haizei::Test<int(int, int, int, int)> f4;
    cout << f4(1, 2, 3, 4) << endl;

    return 0;
}
