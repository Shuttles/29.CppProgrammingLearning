# pair

http://c.biancheng.net/view/7169.html





# sort

```c++
// 默认从小到大排序
vector<int> nums;
sort(nums.begin(), nums.end());
// 从大到小排序
// greater和less头文件<functional>
sort(nums.begin(), nums.end(), greater<int>());
```



# string

```c++
string str("0123456789");

// 字符串分割,第二个参数表示长度
// 23456
string s = str.substr(2, 5);
```





# vector

参考资料

1. 初始化vectorhttps://www.techiedelight.com/zh/initialize-vector-cpp/







# queue







# stack









# priority_queue

1. `priority_queue<T, Container, Compare>`
2. Compare是比较方法，类似于sort第三个参数那样的比较方式，对于自定义类型，需要我们手动进行比较运算符的重载。与sort直接Bool一个函数来进行比较的简单方法不同，Compare需要使用**结构体**的运算符重载完成，直接bool cmp(int a,int b){ return a>b; } 这么写是无法通过编译的。
3. greater和less在priority_queue中是相反的！！！greater反而是小顶堆！！默认是less大顶堆！！
4. 注意priority_queue**不能遍历**！！！想要遍历只能先top再pop！！
5. 经典题：[23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)

```c++
#include <queue>
#include <functional>

struct cmp {
	// 从大到小排序
  // 相当于greater
	bool operator()(int a, int b) {
    return a > b;
  }
};

// 小顶堆
priority_queue<int, vector<int>, cmp> q;

priority_queue<int>  //默认降序队列，大顶堆
priority_queue<int,vector<int>,less<int>> //降序队列，大顶堆
priority_queue<int,vector<int>,greater<int>>  //升序队列，小顶堆

// 常用操作
q.empty();
q.size();
q.top();
q.pop();
```









# set和map

1. set维护的是有序集合，map维护的是有序映射

2. set、map基于==红黑树==，时间复杂度为$O(logn)$

3. unordered_map/set基于==哈希表==，时间复杂度为$O(1)$

4. multiset/multimap和set/map的区别就是其值或key可以重复

5. C++ set/map模拟**堆**

   https://cherishman2005.github.io/2019/09/03/C++-STL/



```c++
// 模拟小顶堆
multiset<int, less<int>> minHeap;

// 插入
minHeap.insert();

// 删除
minHeap.erase(pos);

// 取堆顶元素值
*minHeap.begin()
```







# Hashtable-unordered_map

```cpp
// head
#include <unordered_map>
// 声明
unordered_map<int, int> hash
// 1.key是否存在
//   如果直接hash[key]，就插入了一个值了
if (hash.count(key) != 0) {}
// 2.插入
hash[key] = value;
// 3.删除
hash.erase(key);
```

