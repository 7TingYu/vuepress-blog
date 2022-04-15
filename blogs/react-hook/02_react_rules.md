---
title: react hook - Hook 规则
date: 2022-04-13
tags:
 - react
categories:
 - react
---

Hook 本质就是 JavaScript 函数，但是在使用它时需要遵循两条规则。


## 只在最顶层使用 Hook

不要在循环，条件或嵌套函数中调用 Hook








## 只在 React 函数中调用 Hook


不要在普通的 JavaScript 函数中调用 Hook。


- 在 React 的函数组件中调用 Hook
- 在自定义 Hook 中调用其他 Hook



