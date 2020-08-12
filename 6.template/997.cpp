/*************************************************************************
	> File Name: 997.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月12日 星期三 19时03分04秒
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
class shape {
public: 
    virtual int area()=0;
};


class rectangle : public shape {
public: 
    int a, b; 
    void setLength (int x, int y) { a=x; b=y;} 
    int area() { return a*b; } 
};

int main() {
    rectangle r; 
    r.setLength(3,5);
    shape *s1=&r;
    shape &s2=r;
    //shape s3=r;
    //shape s4[3]; 
    return 0;
}
