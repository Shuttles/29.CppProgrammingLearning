/*************************************************************************
	> File Name: 4.singleton.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月22日 星期六 16时07分49秒
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
#include <mutex>
using namespace std;

class Singletion {
public:
    static Singletion *getInstance() {
        //双重判断的懒汉模式(最终版)
        if (single == nullptr) {
            unique_lock<mutex> lock(m_mutex);
            if (single == nullptr) {
                single = new Singletion();
            } 
        }
        return single;
    }    
private:
    static Singletion *single;
    static std::mutex m_mutex;
    Singletion() = default;
    Singletion(const Singletion &) = default;
    ~Singletion() {}
};

Singletion *Singletion::single = nullptr;
std::mutex Singletion::m_mutex;


int main() {
    Singletion *single = Singletion::getInstance(); 
    return 0;
}
