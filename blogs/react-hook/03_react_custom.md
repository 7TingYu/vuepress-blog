---
title: react hook - 自定义 Hook 
date: 2022-04-13
tags:
 - react
categories:
 - react
---

通过自定义 Hook，可以将组件逻辑提取到可重用的函数中。


**自定义 Hook 是一个函数，其名称以 “use” 开头，函数内部可以调用其他的 Hook。**


- **自定义 Hook 必须以 “use” 开头吗？**
  - 必须如此。这个约定非常重要。不遵循的话，由于无法判断某个函数是否包含对其内部 Hook 的调用，React 将无法自动检查你的 Hook 是否违反了 Hook 的规则。
- **在两个组件中使用相同的 Hook 会共享 state 吗？**
  - 不会。自定义 Hook 是一种重用状态逻辑的机制(例如设置为订阅并存储当前值)，所以每次使用自定义 Hook 时，其中的所有 state 和副作用都是完全隔离的。
- **自定义 Hook 如何获取独立的 state？**
  - 每次调用 Hook，它都会获取独立的 state。













