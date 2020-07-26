/*************************************************************************
	> File Name: 3.class_method.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月26日 星期日 19时43分30秒
 ************************************************************************/

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
    Point() {
        cout << "constructor : " << this <<  endl;
        Point::total_cnt += 1;
        seek_cnt = 0;
    }
    Point(const Point &a) : Point() {
        cout << "copy constructor : " << this << endl;
        this->x = a.x;
        this->y = a.y;
    }
    Point(double z) : Point() { //编译器升级了，中间会产生一个匿名对象，所以不会多统计
        //转换构造函数
        cout << "convert constructor : " << this << endl;
        this->x = 99, this->y = 99;
    }
    Point(int x, int y) : Point() {//显式调用默认构造函数
        cout << "int int param constructor : " << this << endl;
        //有参构造函数
        this->x = x;
        this->y = y;
    }

    void operator=(const Point &a) {
        cout << "operator= : " << this <<  endl;
        this->x = a.x, this->y = a.y;
        return;
    }
    
    void set(int x, int y) {
        this->x = x, this->y = y;
    }

    void seek() const {
        seek_cnt += 1;
        cout << "x = " << x << ", " << "y = " << y << endl;
    }
    
    int S() const {
        return this->seek_cnt;
    }

    static int T() {//类方法
        return Point::total_cnt;
    }

    ~Point() {
        cout << "destructor : " << this << endl;
        Point::total_cnt -= 1;
    }

private:
    int x, y;
    mutable int seek_cnt;
    static int total_cnt;//类属性声明
    
};


int Point::total_cnt = 0;//类属性的定义和初始化必须放在类外面

void test() {
    Point a;
    cout << Point::T() << endl;
    return ;
}


int main() {
    Point a;
    cout << a.T() << endl;//调用类方法
    test();
    Point b;
    cout << b.T() << endl;
    
    cout << "---------------------------------" << endl;
    Point c(3, 4);
    cout << c.T() << endl;
    Point d(3, 4);
    cout << d.T() << endl;


    cout << "---------------------------------" << endl;
    c = 5.6;//调用的是5.6的构造函数
    cout << c.T() << endl;
    cout << &a << endl;
    cout << &b << endl;
    cout << &c << endl;
    cout << &d << endl;

    cout << "---------------------------------" << endl;
    d.seek();
    c.seek();

    const Point e(6, 7);
    e.seek();
    e.seek();
    e.seek();
    e.seek();
    cout << e.S() << endl;
    return 0;
}
