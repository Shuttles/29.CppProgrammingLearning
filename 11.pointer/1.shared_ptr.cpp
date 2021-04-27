/*************************************************************************
	> File Name: 1.shared_ptr.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2021年04月26日 星期一 13时59分58秒
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

class A {
public:
    A() : x(123), y(456) {
        cout << "A : " << this << " constructor " << endl;
    }
    int x, y;
    ~A() {
        cout << "A : " << this << " destructor " << endl;
    }
};


template<typename T>
class shared_ptr {
public:
    shared_ptr() : ptr(nullptr), pcnt(nullptr) {}
    shared_ptr(T* p) : ptr(p), pcnt(new int(1)) {}
    shared_ptr(const shared_ptr<T> &p) : ptr(p.ptr), pcnt(p.pcnt) {
        *pcnt += 1;
    }

    shared_ptr<T> &operator=(const shared_ptr<T> &p) {
        this->use_count_des();
        this->ptr = p.ptr;
        this->pcnt = p.pcnt;
        *pcnt += 1;
        return *this;
    }

    int use_count() { return (pcnt ? *pcnt : 0); }
    T &operator*() { return *(this->ptr); }
    T *operator->() { return this->ptr; }

    ~shared_ptr() {
        this->use_count_des();
    }
private:
    T *ptr;
    int *pcnt;
    void use_count_des() {
        if (pcnt) {
            *pcnt -= 1;
            if (*pcnt == 0) {
                delete pcnt;
                delete ptr;
            }
        }
    }
};

} //end of namespace haizei

int main() {
    haizei::shared_ptr<haizei::A> p(new haizei::A()), q = p;
    haizei::shared_ptr<haizei::A> k(new haizei::A());

    cout << p->x << " " << p->y << endl;
    cout << q->x << " " << q->y << endl;
    cout << p.use_count() << endl;//2

    cout << "--------------------------" << endl;
    q = k;
    cout << p.use_count() << endl;//1

    cout << "--------------------------" << endl;
    p = k;
    cout << p.use_count() << endl;//3
    return 0;
}
