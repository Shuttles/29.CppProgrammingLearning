/*************************************************************************
	> File Name: 9.my_string.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年07月30日 星期四 12时22分11秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#define MAX_STR 1000
using namespace std;

namespace haizei {

class String {
friend ostream &operator<<(ostream &out, const String &str);
friend istream &operator>>(istream &in, String &str);//不写成const是有原因的！见下面的定义
public:
    String(char *str = NULL);//constructor
    String(const String &str);//copy
    String operator+(const String &str);
    String &operator=(const String &str);
    bool operator==(const String &str);
    char operator[](int ind);
    int length();
    String substr(int begein, int n);
    

    ~String();  

private:
    char *__data;
    int __length;

};

//constructor
String::String(char *str) {//默认参数只能写一次！上面已经写在声明中了!
    cout << "default constructor" << " this : " << this << endl;
    if (str == NULL) {
        __data = new char[1];
        __data[0] = '\0';
        __length = 0;
    } else {
        __length = strlen(str);
        __data = new char[__length + 1];//用不用+1?
        strncpy(__data, str, __length);
    }
}

//copy constructor
String::String(const String &str) : __length(str.__length) {
    cout << "copy constructor this : " << this << endl;
    __data = new char[__length + 1];
    strncpy(__data, str.__data, __length);
}



//destructor
String::~String() {
    cout << "destructor this : " << this << endl;
    delete[] __data;
}



String& String::operator=(const String &str) {
    delete[] this->__data;
    this->__length = str.__length;
    this->__data = new char[this->__length + 1];
    strncpy(this->__data, str.__data, str.__length);
    return *this;
}


String String::operator+(const String &str) {
    haizei::String new_str;
    delete[] new_str.__data;//释放原有空间
    //创建长度为两个字符串长度和的空间大小
    new_str.__length = this->__length + str.__length;
    new_str.__data = new char[new_str.__length + 1];
    //写入
    int offset = 0;
    offset += sprintf(new_str.__data, "%s", this->__data);
    sprintf(new_str.__data + offset, "%s", str.__data);
    return new_str;
}

bool String::operator==(const String &str) {
    if (!strcmp(this->__data, str.__data)) 
        return true;
    else 
        return false;
}

char String::operator[](int ind) {
    return this->__data[ind];
}

int String::length() {
    return __length;
}


String String::substr(int begein, int n) {
    String new_str;
    delete[] new_str.__data;
    new_str.__length = n;
    new_str.__data = new char[n + 1];

    char *start = &(this->__data[begein]);
    strncpy(new_str.__data, start, n);
    return new_str;
}


//cin  
istream &operator>>(istream &in, String &str) {
    //in >> str.__data;//不能这么写，遇到空格就ｇｇ了
    char temp[MAX_STR + 5];
    scanf("%[^\n]s", temp);
    getchar();
    strncpy(str.__data, temp, strlen(temp));//如果写成const String,这行不会报错！
    str.__length = strlen(temp);//如果写成const String,报错：__length is read-only object!
    return in;
}


//cout
ostream &operator<<(ostream &out, const String &str) {
    out << str.__data;       
    return out;
}

}

/*写在haizei外面不好使
istream &operator>>(istream &in, const haizei::String &str) {
    in >> str.data;
    return in;
}

ostream &operator<<(ostream &out, haizei::String &str) {
    out << str.data;
    return out;
}
*/

int main() {
    //haizei::String str1("hello world!");
    haizei::String str1;
    cin >> str1;
    cout << "str1 = " << str1 << endl;

    cout << "---------------------" << endl;
    haizei::String str2 = "hello world!";
    cout << "str2 = " << str2 << endl;

    cout << "---------------------" << endl;
    haizei::String str3(" hello haizei!");
    cout << "str2 + str3 = " << str2 + str3 << endl;


    cout << "---------------------" << endl;
    str2 = str3;
    cout << "After str2 = ' hello haizei!', str2 = " << str2 << endl;

    cout << "---------------------" << endl;
    cout << (str1 == str3) << endl;

    cout << "---------------------" << endl;
    cout << "str2.length() = " << str2.length() << endl; 

    cout << "---------------------" << endl;
    cout << "str2[10] = " << str2[10] << endl;

    cout << "---------------------" << endl;
    cout << "str2.substr(10, 2) = " << str2.substr(10, 2) << endl;
    return 0;
}
