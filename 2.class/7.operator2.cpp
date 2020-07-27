/*************************************************************************
	> File Name: 7.operator2.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月27日 星期一 19时20分44秒
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

class Point {
public:
    Point() : __x(0), __y(0) {}
    Point(int x, int y) : __x(x), __y(y) {}
    int x() const { return __x; }
    int y() const { return __y; }
    
    Point operator+(const Point &a) {
        return Point(x() + a.x(), y() + a.y());
    }

    /*我自己写的
    void operator+=(const Point &a) {
        this->x += a.x();
        this->y += a.y();
    }*/

    //hug写的
    Point &operator+=(const Point &a) {
        __x += a.x();
        __y += a.y();
        return *this;
    }

    //前++
    Point &operator++() {
        __x += 1;
        __y += 1;
        return *this;
    }

    Point operator++(int) {//这个int毛用都没有，就是为了区别
        Point temp = *this;
        __x += 1;
        __y += 1;
        return temp;//不能返回引用，因为生命周期到了
    }

private:
    int __x, __y;
};

ostream &operator<<(ostream &out, const Point &a) {
    out << "Point (" << a.x() << ", " << a.y() << ")";
    return out;
}

int main() {
    Point a(4, 5), b(3, 4), c(1, 1);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;


    cout << a + b << endl;


    cout << "pre incr : " << ++(c += b) << endl;
    cout << c << endl;
    cout << "after incr : " << c++ << endl;
    cout << c << endl;

    int n = 6, m = 7;
    (n += m)++;
    cout << n << endl;

    return 0;
}
