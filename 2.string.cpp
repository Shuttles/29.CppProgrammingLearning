/*************************************************************************
	> File Name: 2.string.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月21日 星期二 20时06分36秒
 ************************************************************************/

#include <iostream>
using namespace std;

int main() {
    string s1 = "hello ", s2 = "world!";
    s1 += s2;
    cout << s1 << endl;

    for (int i = 0; i < s1.size(); i++) {
        cout << s1[i] << endl;
    }

    return 0;
}
