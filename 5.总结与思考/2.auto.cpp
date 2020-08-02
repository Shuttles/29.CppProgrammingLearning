/*************************************************************************
	> File Name: 2.auto.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月02日 星期日 18时40分01秒
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

int f(auto x, auto y) {
    return x + y;
}



int main() {
    auto a = 123;
    auto arr[10] = {1, 2, 3, 4};
    cout << sizeof(a)  << endl;
    map<int, int> arr;
    arr[234234] = 23445;
    arr[2345] = 345;
    arr[999] = 10000;
    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }
    cout << endl;
    //下面是c++11中的新语法
    for (auto x : arr) {
        cout << x.first << " " << x.second << endl;
    }

    return 0;
}
