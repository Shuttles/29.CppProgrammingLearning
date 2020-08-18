/*************************************************************************
	> File Name: 1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月17日 星期一 09时58分27秒
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

int main() {
    int n = 10000, m, x, y ;
    auto a = [=](int a, int b) { return a + b + n; };
    n = 100000;
    auto b = [=](int a, int b) {
        return a + b + n;
    };

    //cout << typeid(a).name() << endl;
    
    cout << a(1, 2) << endl;
    cout << b(1, 2) << endl;
}
