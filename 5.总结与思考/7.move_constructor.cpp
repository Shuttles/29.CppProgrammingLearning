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
        cout << "string : default constructor : " << this << endl;
        this->__buff_size = 10;
        this->buff = new char[this->__buff_size];
        this->__length = 0;
    }
    string(const char *str) {
        cout << "string: const char constructor : " << this << endl;
        this->__buff_size = strlen(str);
        this->buff = new char[this->__buff_size + 1];//存'\0'
        strcpy(this->buff, str);
        this->__length = this->__buff_size;
    }
    string(const string &s) : __length(s.__length), __buff_size(s.__buff_size), __end(s.__end){
        //加了const 既可以绑定左值也可以绑定右值
        cout << "string : copy constructor : " << this << endl;
        this->buff = new char[this->__buff_size];
        strcpy(this->buff, s.c_str());

        /*
        for (int i = 0; i < this->__buff_size; i++) {
            this->buff[i] = s.buff[i];
        }*/
    }
    
    string(string &&s) : __length(s.__length), __buff_size(s.__buff_size), __end(s.__end) {
        cout << "move constructor : " << this << endl;
        this->buff = s.buff;//指向匿名对象的存储空间，以免脱裤子放屁
        s.buff = nullptr;
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
        cout << "operator+ : " << this << endl;
        int size = this->__length + s.__length + 1;
        char *temp = new char[size];
        strcpy(temp, this->buff);
        strcat(temp, s.buff);
        //维护属性
        this->__length = size - 1;
        this->__buff_size = size;
        return temp;//调用30行
    }
    int size() {
        return __length;
    }
    ~string() {
        cout << "string : destructor : " << this << endl;
        if (this->buff) delete this->buff;
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
    cout << "-----------------------------------" << endl;
    cout << "======s4 begin======" << endl;
    haizei::string s4 = s1 + s2 + s3;
    cout << "======s4 end========" << endl;
    
    cout << "-----------------------------------" << endl;
    cout << s1 << endl;


    cout << "-----------------------------------" << endl;
    haizei::string s5 = s4;
    cout << s4 << endl;
    cout << s5 << endl;
    s4[3] = '=';
    cout << s4 << endl;
    cout << s5 << endl;


    cout << "-----------------------------------" << endl;
    s1[3] = '6';
    cout << s1 << endl;
    cout << s1 + s2 + s3 << endl;

    cout << s1.size() << endl;
    return 0;
}
