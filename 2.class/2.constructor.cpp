/*************************************************************************
	> File Name: 2.constructor.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月26日 星期日 18时14分44秒
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

class People {
public:
//constructor
    /*
    People() {
        arr = new int[10];
        cout << "default constructor " << endl;
    }*/

    People() = default;//使用默认构造函数
    //People() = delete;//删除默认构造函数
    //为什么要有上面两行呢？因为要把隐藏的规则显示出来方便check
    People(string name) {
        //只传入一个参数的构造函数称为转换构造函数
        //只有转换构造函数才能在“定义对象”之外被调用！！！！
        //上句话存疑，因为实践证明，现在的C++机制中好像是只有定义的时候调用构造函数，其他情况都不调用！！！！
        cout << "string param constructor " << endl;
        this->name = name;
    }

    People (int age) {
        //只要我具备一个整形值，就可以创造出来一个People对象
        cout << "int param constructor" << endl;
        this->age = age;
    }

//copy constructor
    People(const People &a) {
        //copy constructor
        //一定要传引用！！否则会无限递归！
        cout << "copy constructor" << endl;
        this->name = a.name;
        this->age = a.age;
    }

//operator=
    void operator=(const People &a) {
        cout << "operator=" << endl;
        this->name = a.name;
        this->age = a.age;
    }

//destuctor
    ~People() {
        //delete arr;
        cout << "destuctor" << endl;
    }
    //int *arr;
    string name;
    int age;
};

int add(People a, People b) {
    return a.age + b.age;
}


int main() {
    cout << add(4, 5) << endl;//调用转换构造函数
    People a("hug");    
    People b = string("hug");
    People c(543);
    People d = 678;
    cout << a.name  << endl;
    cout << b.name  << endl;
    cout << c.age  << endl;
    cout << d.age << endl;

    cout << "-----------------------" << endl;
    c = 987;//如果没有重载opertor=就会调用转换构造函数  //经过实践，左边那句注释是错的，应该调用默认operator=
    //上面一行　987会先调用自身转换构造函数变为一个匿名对象，经过operator=之后就会销毁
    cout << c.age  << endl;
    d = string("wangjialong"); //必须转换为string对象
    cout << d.name << endl;



    cout << "-----------------------" << endl;
    People e = a;//调用copy constructor

    cout << e.name << endl;
    cout << e.age << endl;

    c = a;//没有调用copy constructor.实际上调用opertor=,因为这不是定义
    cout << c.name << endl;
    cout << c.age << endl;
    return 0;
}
