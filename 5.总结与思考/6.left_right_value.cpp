/*************************************************************************
	> File Name: 6.left_right_value.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月02日 星期日 20时24分04秒
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

#define TEST(a, f) {\
    cout << #a << " : " << #f << " ";\
    f(a);\
}

void f2(int &x) {
    cout << "left value" << endl;
}

void f2(int &&x) {
    cout << "right value" << endl;
}

void f(int &x) {
    cout << "left value" << endl;
    TEST(x, f2);
}

void f(int &&x) {
    cout << "right value" << endl;
    //x = 123;//x能放到等号左边，所以x是左值，即使x是个右值引用！！！
    //TEST(forward<int &&>(x), f2);//forward<>()可以将形参变成想要的值
    TEST(move(x), f2);//move()强制形参变为右值
}

int test_func(const int &&x) {
    cout << x << endl;
    return 0;
}


int main() {
    int a, b = 1, c = 3;
    (++a) = b + c;
    cout << a << endl;

    (a++);
    (a = b) = c;
    cout << a << " " << b << endl;

    int arr[10];
    arr[3] = 12;

    (a += 3) = 67;
    cout << a << endl;

    TEST(a += 3, f);
    TEST(1 + 4, f);
    TEST(b + c, f);
    TEST(a++, f);
    TEST(++a, f);

    test_func(a);
    return 0;
}
