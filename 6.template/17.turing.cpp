/*************************************************************************
	> File Name: 17.turing.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月13日 星期四 14时25分51秒
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

template<int n> 
struct IsEven {
    static constexpr int r = !(n % 2);
};

template<int a, int b>
struct Add {
    static constexpr int r = (a + b);
};

/*我写的
template<int n>
struct Sum {
    static constexpr int r = (1 + n) * n / 2;
};*/

//光哥写的
template<int n>
struct Sum {
    static constexpr int r = n + Sum<n - 1>::r;
};

template<>
struct Sum<0> {
    static constexpr int r = 0;
};

//求阶乘
template<int n>
struct Factorial {
    static constexpr int r = n * Factorial<n - 1>::r;
};

template<>
struct Factorial<1> {
    static constexpr int r = 1;
};

//判断是否是素数
/*
int IsPrime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}*/

template<int n, int i>
struct getNextN {
    static constexpr int r = (i * i > n ? 0 : n);
};

template<int n, int i>
struct getNextI {
    static constexpr int r = (n % i == 0 ? 0 : i + 1);
};

template<int n, int i>
struct IsTest {
    static constexpr int r = IsTest<getNextN<n, i>::r, getNextI<n, i>::r>::r;
};

//两个偏特化版本分别代表了两种出口！
template<int i>//偏特化版本是递归出口！
struct IsTest<0, i> {
    static constexpr int r = 1;//是素数 对应第65行代码
};

template<int n>
struct IsTest<n, 0> {
    static constexpr int r = 0;//不是素数 对应第63行代码
};

template<int i>
struct IsTest<2, i> {
    static constexpr int r = 1;//n == 2一定是素数
};

template<int n>
struct IsPrime {
    static constexpr int r = IsTest<n, 2>::r;
};

/*黄志博写的版本
template<int n, int m>
struct Check{
    static constexpr bool r = (n%m != 0) && Check<n, m-1>::r;
};

template<int n>
struct Check<n, 2>{
    static constexpr bool r = (n%2 != 0);
};


template<int n>
struct IsPrime{
    static constexpr int r = Check<n, (int)sqrt(n)>::r;
};
*/

//求n以内的素数和
template<int n>
struct SumPrime {
    static constexpr int r = (n * IsPrime<n>::r) + SumPrime<n - 1>::r;
};

template<>
struct SumPrime<1> {
    static constexpr int r = 0;
};



/*
void PrintPrime(int n) {
    for (int i = 2; i <= n; i++) {
        constexpr int x = i;
        if (!IsPrime<x>::r) continue;
        cout << x * IsPrime<x>::r << endl;
    }
    return ;
}*/

template<int i, int n>
struct getNextCnt {
    static constexpr int r = (i > n ? 0 : 1);
};

template<int n>
struct print_prime {
    template<int i, int cnt>//这个第二个参数其实是个判断条件！！！
    struct __output {
        static void run() {
            if (IsPrime<i>::r) {
                cout << i << endl;
            }
            print_prime<n>::__output<i + 1, getNextCnt<i + 1, n>::r>::run();
        }
    };

    template<int i>//偏特化版本作为递归出口
    struct __output<i, 0> {
        static void run() {
            return ;
        }
    };
    
    static void output() {//静态函数作为对外接口
        print_prime<n>::__output<2, 1>::run();//这个1是随便传的，只要不是0就行！
        return ;
    }

};

int main() {
    cout << IsEven<123>::r << endl;    
    cout << IsEven<124>::r << endl;    
    cout << Add<97, 87>::r << endl;
    cout << Sum<10>::r << endl;
    cout << Sum<100>::r << endl;
    cout << Factorial<5>::r << endl;
    cout << Factorial<10>::r << endl;

    cout << IsPrime<9973>::r << endl;
    cout << IsPrime<87>::r << endl;
    cout << IsPrime<1537>::r << endl;
    cout << IsPrime<65>::r << endl;

    cout << SumPrime<10>::r << endl;
    cout << SumPrime<20>::r << endl;

    print_prime<100>::output();

    return 0;
}
