---
title: Git 拓展
date: 2021-04-29
tags:
 - git
categories:
 - 小识书屋
---

<!-- [TOC] -->

## 1. 武装你的代码库


我们的代码库由通常很多人维护，经常会出现代码风格不一致或者代码质量不过关，提交信息紊乱的情况。即使是一个人的代码库，有的时候，自己写代码时不太注意细节，也会出现风格不一致的情况。

提升你的提交规范，武装你的代码库。

### 规范 commit 信息

首先，看下 angular 的代码库的 commit 记录，如图：

![img](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/672c985640504158959c4d89c507f7ad~tplv-k3u1fbpfcp-zoom-1.image)

参考文章中有使用到的插件，但个人觉得还是有些许繁琐，所以这里主要列出 type 说明，有兴趣的同学可以围观原文。

| 值       | 描述                                               |
| -------- | -------------------------------------------------- |
| feat     | 新增一个功能                                       |
| fix      | 修复一个bug                                        |
| docs     | 文档变更                                           |
| style    | 代码格式（不影响功能）                             |
| refactor | 代码重构                                           |
| perf     | 改善性能                                           |
| test     | 测试                                               |
| build    | 变更项目构建或外部依赖（ps: webpack、gulp、npm等） |
| ci       | 更改持续集成软件的配置文件和package中的scripts命令 |
| chore    | 变更构建流程或者辅助工具                           |
| revert   | 代码回退                                           |


参考：[十分钟的时间，武装你的代码库](https://juejin.cn/post/6861769180736126983)