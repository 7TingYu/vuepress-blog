---
title: 门徒 0. 方法总结
date: 2022-04-6
tags:
 - 门徒
categories:
 - 门徒

---

### 常见位运算

```shell
# 2 的 n 次
1 << x 
```


### 假设法

对于一个需要递归的算法，我们可以假设某个点已知，得到其结果。


### 字符串转数字

```cpp
int num = 0;
for (int i = l; i <= r; i++) {
    if (s[i] >= '0' && s[i] <= '9') {
        num = num * 10 + (s[i] - '0');
    }
}
return num;
```



