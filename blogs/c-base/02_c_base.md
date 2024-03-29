---
title: c语言 基础 - 基本语法
date: 2022-04-20
tags:
 - c语言
categories:
 - c语言
---


## 分号

在 C 程序中，分号是语句结束符。也就是说，每个语句必须以**分号结束**。它表明一个逻辑实体的结束。


## 注释

C 语言有两种注释方式：

```c
// 单行注释

/* 单行注释 */
/* 
 多行注释
 多行注释
 多行注释
 */
```

## 标识符

C 标识符是用来标识变量、函数，或任何其他用户自定义项目的名称。一个标识符以**字母 A-Z 或 a-z 或下划线 _ 开始**，**后跟零个或多个字母、下划线和数字（0-9）**。


C 标识符内不允许出现标点字符，比如 @、$ 和 %。**C 是区分大小写**的编程语言。


## 关键字


| 关键字   | 说明                                                          |
| -------- | ------------------------------------------------------------- |
| auto     | 声明自动变量                                                  |
| break    | 跳出当前循环                                                  |
| case     | 开关语句分支                                                  |
| char     | 声明字符型变量或函数返回值类型                                |
| const    | 定义常量，如果一个变量被 const 修饰，那么它的值就不能再被改变 |
| continue | 结束当前循环，开始下一轮循环                                  |
| default  | 开关语句中的"其它"分支                                        |
| do       | 循环语句的循环体                                              |
| double   | 声明双精度浮点型变量或函数返回值类型                          |
| else     | 条件语句否定分支（与 if 连用）                                |
| enum     | 声明枚举类型                                                  |
| extern   | 声明变量或函数是在其它文件或本文件的其他位置定义              |
| float    | 声明浮点型变量或函数返回值类型                                |
| for      | 一种循环语句                                                  |
| goto     | 无条件跳转语句                                                |
| if       | 条件语句                                                      |
| int      | 声明整型变量或函数                                            |
| long     | 声明长整型变量或函数返回值类型                                |
| register | 声明寄存器变量                                                |
| return   | 子程序返回语句（可以带参数，也可不带参数）                    |
| short    | 声明短整型变量或函数                                          |
| signed   | 声明有符号类型变量或函数                                      |
| sizeof   | 计算数据类型或变量长度（即所占字节数）                        |
| static   | 声明静态变量                                                  |
| struct   | 声明结构体类型                                                |
| switch   | 用于开关语句                                                  |
| typedef  | 用以给数据类型取别名                                          |
| unsigned | 声明无符号类型变量或函数                                      |
| union    | 声明共用体类型                                                |
| void     | 声明函数无返回值或无参数，声明无类型指针                      |
| volatile | 说明变量在程序执行中可被隐含地改变                            |
| while    | 循环语句的循环条件                                            |


