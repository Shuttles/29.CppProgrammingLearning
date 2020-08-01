/*************************************************************************
	> File Name: 3.my_hashtable.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月01日 星期六 18时48分18秒
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

class IHashFunc{//接口类
public:
    virtual int operator()(int) = 0;
};


class HashTable {
typedef int (*HashFunc_T)(int);
typedef pair<int, int> PII;
public:
    HashTable(HashFunc_T);
    HashTable(IHashFunc &);
    int &operator[](int); 

private:
    HashTable(HashFunc_T, IHashFunc *, int);
    int hash_type;
    HashFunc_T func1;
    IHashFunc *func2;
    int __size;
    PII **data;
};

HashTable::HashTable(HashFunc_T func1, IHashFunc *func2, int hash_type) 
: func1(func1), func2(func2), hash_type(hash_type){
    this->__size = 1000;
    this->data = new PII *[this->__size];
    for (int i = 0; i < this->__size; i++) {
         data[i] = nullptr;
    }
}

HashTable::HashTable(HashFunc_T func) : HashTable(func, nullptr, 1) {
    //意味着传入的是个普通函数
}

HashTable::HashTable(IHashFunc &func) : HashTable(nullptr, &func, 2) {
    //意味着传入的是个函数对象
}

int &HashTable::operator[](int x) {
    int hash = 0;
    switch (hash_type) {
        case 1:
            hash = func1(x);
            break;
        case 2:
            hash = (*func2)(x);
            break;
    }
    if (hash < 0) hash &= 0x7fffffff;
    int ind = hash % __size, t = 1;
    while (data[ind] && data[ind]->first != x) {
        ind += t * t;
        if (ind < 0) ind = ind & 0x7fffffff;
        ind %= __size;
        t += 1;
    }
    if (data[ind] == nullptr) data[ind] = new PII(x, 0);
    return data[ind]->second;
}


int hash1(int x) {
    return (x << 1) ^ (x << 3) ^ (x >> 5);
}

class MyHashFunc : public IHashFunc {
public:
    int operator()(int x) override {
        return (x << 1) ^ (x << 3) ^ (x >> 5);
    }
};


int main() {
    MyHashFunc hash2;
    HashTable h1(hash1);
    HashTable h2(hash2);
    h1[123] = 345;
    h2[123] = 678;
    cout << h1[123] << endl;
    cout << h2[123] << endl;
    cout << h1[789] << endl;
    cout << h2[10000] << endl;

    return 0;
}
