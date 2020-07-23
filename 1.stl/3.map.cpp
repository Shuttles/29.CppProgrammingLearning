/*************************************************************************
	> File Name: 3.map.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月21日 星期二 20时09分44秒
 ************************************************************************/

#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

int main() {
    /*
    map<double, string> arr;
    //底层是红黑树
    arr[1.2] = "hello ";
    arr[4.3] = "world!";
    arr[-4.5] = "haizei";
    arr[89.7] = "world";

    for (auto iter = arr.begin(); iter != arr.end(); iter++) {
        cout << iter->first << " " << iter->second << endl;
    }*/

    unordered_map<double, string> arr;
    //哈希表
    arr[1.2] = "hello ";
    arr[4.3] = "world!";
    arr[-4.5] = "haizei";
    arr[89.7] = "world";

    double n;
    while (cin >> n) {
        /*
        if (arr[n] != "") {
            //只要是用[]去访问，就一定会在红黑树中插入一个结点
            cout << "find : " << arr[n] << endl;
        } else {
            cout << "not found :" << n << endl;
        }
        */

        if (arr.find(n) != arr.end()) {
            //arr.find(n)返回的是一个指针对象，不会在map中新增结点
            cout << "find : " << arr[n] << endl;
        } else {
            cout << "not found :" << n << endl;
        }
    }

    for (auto iter = arr.begin(); iter != arr.end(); iter++) {

        cout << iter->first << " " << iter->second << endl;
    }

    return 0;
}
