/*************************************************************************
	> File Name: 2.visitor.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月20日 星期四 10时49分37秒
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
#include <ctime>
using namespace std;

class Cat;
class Bat;
class Dog;
class Mouse;


class Animal {
public:
    class IVisitor {
    public:
        virtual void visit(Cat *) = 0;
        virtual void visit(Dog *) = 0;
        virtual void visit(Mouse *) = 0;
        virtual void visit(Bat *) = 0;
    };
    virtual void Accept(IVisitor *) = 0;
    virtual ~Animal() {};
};

class Dog : public Animal {
public:
    virtual void Accept(IVisitor *vis) override{
        vis->visit(this);
    }

};


class Cat : public Animal {
public:
    virtual void Accept(IVisitor *vis) override {
        vis->visit(this);
    }

};

class Mouse : public Animal {
public:
    virtual void Accept(IVisitor *vis) override{
        vis->visit(this);
    }

};

class Bat : public Animal {
public:
    virtual void Accept(IVisitor *vis) override {
        vis->visit(this);
    }

};

class AnimalCout : public Animal::IVisitor {
public:
    virtual void visit(Cat *obj) {
        cout << "this is a cat" << endl;
    } 
    virtual void visit(Dog *obj) {
        cout << "this is a dog " << endl;
    }
    virtual void visit(Mouse *obj)  {
        cout << "this is a mouse" << endl;
    }
    virtual void visit(Bat *obj) {
        cout << "this is a bat " << endl;
    }

};

class AnimalCount : public Animal::IVisitor {
public:
    int cnt_cat, cnt_dog, cnt_mouse, cnt_bat;
    AnimalCount() : cnt_cat(0), cnt_dog(0), cnt_mouse(0), cnt_bat(0) {};
    virtual void visit(Cat *obj) {
        cnt_cat += 1;
    } 
    virtual void visit(Dog *obj) {
        cnt_dog += 1;
    }
    virtual void visit(Mouse *obj)  {
        cnt_mouse += 1;
    }
    virtual void visit(Bat *obj) {
        cnt_bat += 1;
    }

};



int main() {
    srand(time(0));
    Animal *arr[10];
    for (int i = 0; i < 10; i++) {
        switch (rand() % 4) {
            case 0: arr[i] = new Cat(); break;
            case 1: arr[i] = new Dog(); break;
            case 2: arr[i] = new Mouse(); break;
            case 3: arr[i] = new Bat(); break;
        }
    }

    /*这么写太操蛋了
    for (int i = 0; i < 10; i++) {
        if (dynamic_cast<Cat *>(arr[i])) {
            cout << "this is a cat" << endl;
        } else if (dynamic_cast<Dog *>(arr[i])) {
            cout << "this is a dog" << endl;
        } else if (dynamic_cast<Mouse *>(arr[i])) {
            cout << "this is a mouse" << endl;
        }
    }*/

    AnimalCout vis;
    AnimalCount cnt;
    for (int i = 0; i < 10; i++) {
        arr[i]->Accept(&vis);
        arr[i]->Accept(&cnt);
    }

    cout << "Cat : " << cnt.cnt_cat << endl;
    cout << "Dog : " << cnt.cnt_dog << endl;
    cout << "Mouse : " << cnt.cnt_mouse << endl;
    cout << "Bat : " << cnt.cnt_bat << endl;
    return 0;
}
