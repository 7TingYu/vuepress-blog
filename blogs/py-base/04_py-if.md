---
title: python 条件判断
date: 2023-2-21
tags:
 - python
categories:
 - python
---


## 条件判断

计算机之所以能做很多自动化的任务，因为它可以自己做条件判断。

一个简单的判断语句：

```py
age = 3
if age >= 18:
    print('your age is', age)
    print('adult')
else:
    print('your age is', age)
    print('teenager')
```
    
根据Python的缩进规则，如果if语句判断是True，就把缩进的两行print语句执行了，否则，什么也不做。

当然上面的判断是很粗略的，完全可以用elif做更细致的判断：

```py
age = 3
if age >= 18:
    print('adult')
elif age >= 6:
    print('teenager')
else:
    print('kid')
```

### 再议 input

最后看一个有问题的条件判断。很多同学会用input()读取用户的输入，这样可以自己输入，程序运行得更有意思：

```py
birth = input('birth: ')
if birth < 2000:
    print('00前')
else:
    print('00后')
```

输入1982，结果报错：

```
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: unorderable types: str() > int()
```

这是因为input()返回的数据类型是str，str不能直接和整数比较，必须先把str转换成整数。Python提供了int()函数来完成这件事情：

```py
s = input('birth: ')
birth = int(s)
if birth < 2000:
    print('00前')
else:
    print('00后')
```

再次运行，就可以得到正确地结果。但是，如果输入abc呢？又会得到一个错误信息：

```py
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ValueError: invalid literal for int() with base 10: 'abc'
```

原来int()函数发现一个字符串并不是合法的数字时就会报错，程序就退出了。

如何检查并捕获程序运行期的错误呢？后面的错误和调试会讲到。

## 小结

条件判断可以让计算机自己做选择，Python的if...elif...else很灵活。