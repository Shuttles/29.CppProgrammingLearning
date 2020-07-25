/*************************************************************************
	> File Name: 1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月25日 星期六 16时19分55秒
 ************************************************************************/

#include <iostream>
using namespace std;

class People {
    friend int main();
    int x, y;
public:
    void set(int x) ; /*{
        cout << "set functiona : " << this << endl;
        this->x = x;//this指针指向当前对象
    }*/
    void say(); /*{
        //类内方法，可以访问private成员
        cout << x << " " << y << endl;
    }*/
};

struct People2 {//C++中的struct跟class本质上是一样的，都是定义类，保留struct关键字只是为了兼容C
    int x, y;
};

void People::set(int x) {
    cout << "set function : " << this << endl;
    this->x = x;
    return ;
}

void People::say() {
    cout << x << " " << y << endl;//找x是由内向外查找的，所以找到的是类内的成员属性
    return ;
}

int main() {
    People a;
    People2 b;//声明不需要struct 关键字
    a.y = 18432;
    cout << "a object : " << &a << endl;
    a.set(3);
    b.x = 4;
    /*
    cout << a.x << endl;//会报错，因为无明确说明都是private
    */
    cout << b.x << endl;//不会报错，因为struct 中若无明确说明都是public
    a.say();
    return 0;
}
