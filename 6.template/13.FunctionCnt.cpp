/*************************************************************************
	> File Name: 30.function.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/ 8 15:25:29 2020
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <functional>
using namespace std;

namespace haizei {

template<typename RT, typename ...PARAMS> 
class base {
public :
    virtual RT operator()(PARAMS...) = 0;
    virtual base<RT, PARAMS...> *getCopy() = 0;
    virtual ~base() {}
};

template<typename RT, typename ...PARAMS> //函数
class normal_func : public base<RT, PARAMS...> {
public :
    typedef RT (*func_type)(PARAMS...);
    normal_func(func_type func) : ptr(func) {}
    virtual RT operator()(PARAMS...args) override {
        return this->ptr(args...);
    }
    virtual base<RT, PARAMS...> *getCopy() override  {
        return new normal_func<RT, PARAMS...>(ptr);
    } 

private:
    func_type ptr;
};

template<typename C, typename RT, typename ...PARAMS> 
class functor : public base<RT, PARAMS...> {//函数对象
public :
    functor(C &func) : ptr(func) {}
    virtual RT operator()(PARAMS...args) override {
        return this->ptr(args...);
    }
    virtual base<RT, PARAMS...> *getCopy() override {
        return new functor<C, RT, PARAMS...>(ptr);
    }

private:
    C &ptr;
};

template<typename RT, typename ...PARAMS> class function;
template<typename RT, typename ...PARAMS>
class function<RT(PARAMS...)> {
public :
    //转换构造
    function(RT (*func)(PARAMS...)) 
    : ptr(new normal_func<RT, PARAMS...>(func)) {}

    template<typename T>
    function(T a) 
    : ptr(new functor<typename remove_reference<T>::type, RT, PARAMS...>(a)){}

    //拷贝构造
    function(const function &f) {
        this->ptr = f.ptr->getCopy();
    }

    //移动构造
    function(function &&f) {
        this->ptr = f.ptr;
        f.ptr = nullptr;
    }

    RT operator()(PARAMS... args) {
        return this->ptr->operator()(args...);
    }
    ~function() {
        if (ptr != nullptr) delete ptr;
    }

private:
    base<RT, PARAMS...> *ptr;
};

} // end of haizei



/*我的版本
//改成模板类
template<typename RT, typename ...PARAMS> class FunctionCnt;
template<typename RT, typename ...PARAMS> 
class FunctionCnt<RT(PARAMS...)> {
public:
    FunctionCnt(function<RT(PARAMS...)> g) : g(g), __cnt(0) {}
    //原本想法是通过ARG类取出所有参数类型作为形参列表
    //template<typename ...ARGS>//这说明可以直接用变参列表！不必前面非得有个参数！
    RT operator()(PARAMS... args) {
        __cnt += 1;
        return g(args...);
    }
    int cnt() { return __cnt; }
private:
    function<RT(PARAMS...)> g;
    int __cnt;
};*/


//光哥版本
template<typename RT, typename ...PARAMS> class FunctionCnt;
template<typename RT, typename ...PARAMS> 
class FunctionCnt<RT(PARAMS...)> {
public:
    FunctionCnt(haizei::function<RT(PARAMS...)> g) : g(g), __cnt(0) {
        cout << "constructor" << endl;
    }
    RT operator()(PARAMS... args) {
        cout << "in operator()" << endl;
        __cnt += 1;
        return g(args...);
    }
    int cnt() { return __cnt; }

private:
    haizei::function<RT(PARAMS...)> g;
    int __cnt;
};

//试验函数
double multply(double a, double b, double c) {
    return a * b * c;
}


int main() {
    int n;
    FunctionCnt<double(double, double, double)> multply_cnt(multply);
    cout << multply_cnt(5.5, 4.4, 8.2) << endl;
    cout << multply_cnt(111.0, 11.2, 13.3) << endl;
    cout << multply_cnt.cnt() << endl;
    return 0;
}
