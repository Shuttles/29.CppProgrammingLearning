/*************************************************************************
	> File Name: 3.constexper.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月02日 星期日 18时56分22秒
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

/*
constexpr int f(int x) {
    if (x == 1) return 1;
    return x * f(x - 1);
}
*/

constexpr int f(int x) {
    return 3 * x * x + x;
}

class A {
public:
    constexpr A(int x, int y) : x(x), y(y) {} 
    int x, y;
};


int main() {
    int n;
    cin >> n;
    cout << f(n) << endl;
    constexpr int m = f(12);
    cout << m << endl;
    constexpr A a(2, 3);
    cout << a.x << " " << a.y << endl;
    return 0;
}
