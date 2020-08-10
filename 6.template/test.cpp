/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 一  8/10 22:43:48 2020
 ************************************************************************/

#include<iostream>
using namespace std;

//所以说右值可以绑定在左值引用上！只不过左值引用得写成const int &
//实践证明上面那句话是错的！不能将引用绑定在局部变量中！
const int &add(int &&a, int &&b) {
    int c = a + b;
    return c;
}


int main() {
    cout << add(2, 4) << endl;
    return 0;
}
