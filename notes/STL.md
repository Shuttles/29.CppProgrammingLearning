

# set和map

1. set维护的是有序集合，map维护的是有序映射
2. set、map基于==红黑树==，时间复杂度为$O(logn)$
3. unordered_map/set基于==哈希表==，时间复杂度为$O(1)$





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

