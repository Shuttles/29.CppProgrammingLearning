/*************************************************************************
	> File Name: 287.合并果子.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月23日 星期四 19时04分40秒
 ************************************************************************/

#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> PII;

int main() {
    int n, a, sum = 0, t = 0;//ｔ是时间戳，防止去重
    cin >> n;
    set<PII> s;
    for (int i = 0; i < n; i++) {
        cin >> a;
        s.insert(PII(a, t++));
    }

    for (int i = 0; i < n - 1; i++) {
        int a = s.begin()->first;
        s.erase(s.begin());
        int b = s.begin()->first;
        s.erase(s.begin());
        sum += (a + b);
        s.insert(PII(a + b, t++));
    }
    cout << sum << endl;
    return 0;
}
