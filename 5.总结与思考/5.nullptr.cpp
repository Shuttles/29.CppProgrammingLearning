/*************************************************************************
	> File Name: 5.nullptr.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月02日 星期日 20时06分23秒
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


int f(int x) {
    cout << "output int value : ";
    cout << x << endl;
    return 0;
}

int f(int *x) {
    cout << "output address : ";
    cout << x << endl;
    return 0;
}


int main() {
    printf("nullptr = %lld\n", (long long)nullptr);
    cout << "NULL = " << NULL << endl;
    int n = 123, *p = &n;
    f(n);
    f(p);
    f(nullptr);//本地就是地址
    f((int)NULL);//本质是int 0,我们只是看成地址，即本质是(void *)0
    return 0;
}
