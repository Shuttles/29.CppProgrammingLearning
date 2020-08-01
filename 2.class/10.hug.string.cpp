/*************************************************************************
	> File Name: 10.hug.string.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月01日 星期六 14时32分16秒
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
#include <cstring>
using namespace std;

namespace haizei{
class string {
public:
    string() {
        this->__buff_size = 10;
        this->buff = new char[this->__buff_size];
        this->__length = 0;
    }
    string(const char *str) {
        this->__buff_size = strlen(str);
        this->buff = new char[this->__buff_size + 1];//存'\0'
        strcpy(this->buff, str);
        this->__length = this->__buff_size;
    }
    char &at(int ind) {
        //边界检查
        if (ind < 0 || ind >= __length) {
            cout << "String Error : out if range" << endl;
            return __end;
        }
        return this->operator[](ind);
    }
    char &operator[](int ind) {
        return buff[ind];
    }
    char *c_str() const {
        return buff;
    }
    string operator+(const string &s) {
        int size = this->__length + s.__length + 1;
        char *temp = new char[size];
        strcpy(temp, this->buff);
        strcat(temp, s.buff);
        return temp;//调用30行
    }
    int size() {
        return __length;
    }


private:
    int __length, __buff_size;
    char *buff;
    char __end;
};

}


ostream &operator<<(ostream &out, const haizei::string &s) {
    out << s.c_str() ;
    return out;
}


int main() {
    haizei::string s1 = "hello world!", s2 = ", haizei", s3 = ", harbin.";
    cout << s1 << endl;
    s1[3] = '6';
    cout << s1 << endl;
    cout << s1 + s2 + s3 << endl;

    cout << s1.size() << endl;
    return 0;
}
