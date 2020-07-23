/*************************************************************************
	> File Name: 256.国王游戏.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月23日 星期四 19时51分36秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 1000
int a[MAX_N + 5], b[MAX_N + 6], ind[MAX_N + 5];
//ind存放这个位置的大臣下标

bool cmp(int i, int j) {
    //对编号进行排序的方法，无论是牵扯到n个数都行，这个技巧很重要！
    return a[i] * b[i] < a[j] * b[j];
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        cin >> a[i] >> b[i];
        ind[i] = i;
    }
    sort(ind + 1, ind + 1 + n, cmp);
    /*
    for (int i = 0; i <= n; i++) {
        cout << ind[i] << " ";
    }
    cout << endl;
    */
    int p = a[0], ans = 0;
    for (int i = 1; i <= n; i++) {
        int temp = p / b[i];
        if (temp > ans) ans = temp;
        p *= a[i];
    }
    cout << ans << endl;
    return 0;
}
