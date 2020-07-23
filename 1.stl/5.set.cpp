/*************************************************************************
	> File Name: 5.set.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月23日 星期四 18时13分26秒
 ************************************************************************/

#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    //底层也是红黑树
    //但是可以用作堆！！！！！
    //set以及能满足堆的功能了，就没必要再定义给一个heap了！！！
    s.insert(345);
    s.insert(65);
    s.insert(3995);
    s.insert(9000);
    cout << s.size() << endl;
    s.insert(65);
    cout << s.size() << endl;
    cout << *(s.begin()) << endl;
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        //iter是迭代器
        cout << *(iter) << endl;
    }

    s.erase(s.begin());//传入迭代器
    cout << *(s.begin()) << endl;

    return 0;
}
