/*************************************************************************
	> File Name: 6.operator.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月27日 星期一 18时29分03秒
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

class istream {
public:
    istream &operator>>(int &n) {//返回值必须是引用，否则只是个对象的拷贝
        std::cin >> n;
        return *this;
    }
private:

};

class ostream {
public:
    ostream &operator<<(int &n) {
        std::cout << n;
        return *this;
    }
    ostream &operator<<(const char *msg) {//必须是const.因为下面主函数中的" "和"\n"是const char*
        std::cout << msg;
        return *this;
    }
private:

};

istream cin;
ostream cout;

};


//类外重载运算符
haizei::ostream &operator<<(haizei::ostream &out, double &z) {
    std::cout << z;
    return out;
}

/*
ostream &operator+(ostream &out, int &x) {
    std::cout << x;
    return out;
}*/

ostream &operator+(ostream &out, const int &z) {
    out << z;//和55行效果相同
    return out;
}

int main() {
    int n, m;
    haizei::cin >> n >> m;
    haizei::cout << n  << " " << m << "\n";

    double k = 5.6;
    haizei::cout << k << "\n";

    (((((cout + 8) << " ") +  9) << " ") + 10) << "\n";//效果　输出8 9 10
    return 0;
}
