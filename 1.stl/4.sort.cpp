/*************************************************************************
	> File Name: 4.sort.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月21日 星期二 20时53分10秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    //a在什么情况下排在b的前面！
    return a > b;
}

struct CMP_FUNC {
    bool operator()(int a, int b) {
        return a > b;
    }  
};


int main() {
    int arr[1000], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    nth_element(arr, arr + 1, arr + n);
    //排完序之后arr[1]应该放什么元素, O(n);
    cout << arr[1] << endl;
    sort(arr, arr + n, [](int a, int b) -> bool { return a > b; });
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
