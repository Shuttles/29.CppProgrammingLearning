/*************************************************************************
	> File Name: 3.class.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月06日 星期四 14时46分56秒
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
template<typename T>
class PrintAny {
public:
    void operator()(const T &a) {
        cout << a << endl;
    }
};
}


int main() {
    haizei::PrintAny<int> print1;
    haizei::PrintAny<string> print2;
    print1(123);
    print2("hello world");
    print2("hello haizei");
    return 0;
}
