# 太长不看版

![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1ghfyogvndgj31de0u0gx8.jpg)









学习语言是其实是按照编程范式来学的

C++的学习重点是

1. ==理解程序的运行流程==
2. 学C++就是学一套逻辑！



C++的设计重点：

1. ==将运行时的bug转换为编译时的bug==

   







开发效率

1. 代码开发
2. 测试
3. 维护





以下类的实现都是==泛型编程==写出来的，重点在于==把类型区别淡化==

queue类：队列

1. 头文件：queue

2. 命名空间：std

3. 声明：

   ```c++
   #include <queue>
   using std::queue;
   queue<data_type> q;
   ```

   

stack类：栈

与queue基本相同



string类：字符串

1. 头文件：string

2. 命名空间

3. 声明

   ```c++
   #include <string>
   using std::string;
   string s1, s2;
   
   s1 = "Hello world!\n"
       
   s1 == s2; //判等
   s1 < s2; //字典序小于
   s1 += s2; //字符串连接
   s1.length();//字符串长度 O(1),因为string是个类    而strlen是O(n)
   ```





HASH_MAP类(非标准)

1. 头文件

2. 命名空间：__gnu_ccc;

3. 声明

   ```c++
   hash_map<key_type, value_type, hash_func> h;
   ```

   



unordered_map类：哈希表

1. 头文件：unordered_map

2. 命名空间：std

3. 声明

   ```c++
   
   unordered_map<>
   ```

   



sort

1. 快排的优化
   + 单边递归法
2. 堆排序





