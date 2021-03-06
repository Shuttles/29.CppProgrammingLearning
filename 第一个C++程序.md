# 第一个C++程序

```c++
#include <iostream>
using std::cout;
using std::endl;

int main() {
    cout << "Hello world!" << endl;
    return 0;
}
```

1. 我们通过代码第一行引入了一个名为`iostream(Input Output stream)`的头文件，而`cout`则是一个在这个头文件中被定义好的==对象==，其中包含了许多有用的输入输出相关功能。

2. 对于`cout`对象而言，输出操作由操作符`<<`来表达，其作用是紧随其后的双引号中的字符串输出到标准输出设备(即显示器)上，以换行符`endl`结尾。

3. 下面的几行`using`表示使用***<u>命名空间std</u>***中的指定内容(这里使用的是cout和endl)，所以我们可以知道，如果想使用iostream中的某个对象，就必须要加上对应的语句，格式为

   ```c++
   using std::XXX
   ```

4. 我们之后开发C++语言程序的过程其实也就是包含了各自逻辑意义的***<u>子程序的函数或者对象们</u>***，把它们调用来、调用去的过程(就像我们已经在main函数中调用了cout对象这样)。

   只不过这些函数/对象中，有一些是外部的头文件中已经定义好的，我们引入了头文件就可以使用，比如cout是一个在iostream中已经声明好了、可以直接使用的对象。而另一些可能需要你自己去定义、实现之后，你才可以进一步去进行调用。