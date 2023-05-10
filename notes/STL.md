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

