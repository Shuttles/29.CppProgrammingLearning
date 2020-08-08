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



//remove_reference begin
template<typename T> struct remove_reference { typedef T type; };
template<typename T> struct remove_reference<T &> { typedef T  type; };
template<typename T> struct remove_reference<T &&> { typedef T type; };

template<typename T>
typename remove_reference<T>::type add2(T &&a, T &&b) {
    typename remove_reference<T>::type c = a + b;
    return c;
}
//remove_reference end


//add_const begin
template<typename T> struct add_const { typedef const T type; };
template<typename T> struct add_const<const T> { typedef const T type; };
//add_const end


//add_lvalue_reference begin
template<typename T> struct add_lvalue_reference { typedef T &type; };
template<typename T> struct add_lvalue_reference<T &> { typedef T &type; };
template<typename T> struct add_lvalue_reference<T &&> { typedef T &type; };
//add_lvalue_reference end


//add_rvalue_reference begin
template<typename T> struct add_rvalue_reference { typedef T &&type; };
template<typename T> struct add_rvalue_reference<T &> { typedef T &&type; };
template<typename T> struct add_rvalue_reference<T &&> { typedef T &&type; };
//add_rvalue_reference end


//remove_pointer begin
//递归处理
template<typename T> struct remove_pointer { typedef T type; };
template<typename T> struct remove_pointer<T *> { typedef typename remove_pointer<T>::type type; };
//remove_pointer end

//move begin
template<typename T> 
typename add_rvalue_reference<T>::type move(T &&a) { 
    return  typename add_rvalue_reference<T>::type(a); 
};
//move end

//检验左右值
void f(int &x) {
    cout << "f function : left value" << endl;
}

void f(int &&x) {
    x = 9973;
    cout << "f function : right value" << endl;
}

}//end of haizei


struct foo {
    void m() const {
        cout << "Const" << endl;
    }
};

template<typename T1, typename T2>
void print_is_same() {
    cout << is_same<T1, T2>() << endl;
}

int main() {
    //add_const
    haizei::add_const<foo>::type{}.m();


    cout << "----------------------" << endl;
    //add_l/rvalue_reference
    using nonref = int;
    using lref = typename haizei::add_lvalue_reference<nonref>::type;
    using rref = typename haizei::add_rvalue_reference<nonref>::type;
    cout << std::is_lvalue_reference<lref>::value << endl;
    cout << std::is_rvalue_reference<rref>::value << endl;


    cout << "----------------------" << endl;
    //remove_pointer
    print_is_same<int, haizei::remove_pointer<int *>::type>();



    cout << "----------------------" << endl;
    int n = 45, m = 67;
    int *p = &n, *q = &m;
    haizei::f(n);
    haizei::f(haizei::move(n));
    cout << n << endl;

    /*
    cout << "----------------------" << endl;
    int inta = 123, intb = 456;
    cout << haizei::add2(inta, intb) << endl;

    cout << "----------------------" << endl;
    cout << haizei::add2(123, 456) << endl;
    */
    return 0;
}
