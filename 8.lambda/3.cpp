/*************************************************************************
	> File Name: 3.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月17日 星期一 14时42分46秒
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
    struct greater {
        bool operator()(const T &a, const T &b) {
            return a > b;
        }
    };

    template<typename T> 
    struct less {
        bool operator()(const T &a, const T &b) {
            return a < b;
        }
    };



}// end of haizei


int main() {
    srand(time(0));
    int arr[10];
    for (int i = 0; i < 10; i++) arr[i] = rand() % 100;
    sort(arr, arr + 10, haizei::greater<int>());

    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
