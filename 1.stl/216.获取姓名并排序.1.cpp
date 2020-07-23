/*************************************************************************
	> File Name: 216.获取姓名并排序.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月23日 星期四 18时27分29秒
 ************************************************************************/

//没考虑到有重名现象，而set会去重，这道题就过不去了
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<string> s;
    string name;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> name;
        name = name.substr(name.find(".") + 1, name.size());//截取字符串，如果第二个参数过大，就会截取到末尾
        s.insert(name);
    }
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << *iter << endl;
    }

    return 0;
}
