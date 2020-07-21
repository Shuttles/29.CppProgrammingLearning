/*************************************************************************
	> File Name: 1.stl.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月21日 星期二 19时51分45秒
 ************************************************************************/

#include <iostream>
#include <queue>
using namespace std;

int main() {
    int op, val;
    queue<int> q;
    while (cin >> op >> val) {
        switch (op) {
            case 1: q.push(val);break;
            case 2: q.pop();break;
            case 3: cout << q.front() << endl; break;
        }
        cout << "queue size :" << q.size() << ", empty :" << (q.empty() ? "True" : "False ") << endl;
    }
    return 0;
}
