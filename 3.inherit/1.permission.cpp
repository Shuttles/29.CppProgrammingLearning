/*************************************************************************
	> File Name: 1.permission.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月28日 星期二 18时53分23秒
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

class Animal {
public:
    Animal(string name, int age) : __name(name), age(age) {}
    void say() {
        cout << "my name is : " << __name << ", my age is : " << age << endl;
    }
protected:
    string __name;

private:
    int age;
};

class Cat : public Animal {
public:
    Cat() = delete;
    Cat(string name, int age) : Animal(name, age) {}
};


class Bat : protected Animal {
public:
    Bat() = delete;
    Bat(string name, int age, string color)  {}
    /*
    void say() {
        this->Animal::say();
        cout << "class Bat : " << __name << endl;
        cout << "class Bat : " << age << endl;//会报错，因为age是private
    }*/
};


int main() {
    Cat a("kitty", 29);
    a.say();

    Bat b("hug", 16384);
    b.say();//会报错，因为say变成了protected
    return 0;
}
