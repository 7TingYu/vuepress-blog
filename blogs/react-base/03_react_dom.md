---
title: react 基础 - 元素渲染
date: 2022-3-23
tags:
 - react
categories:
 - react
---

元素是构成 React 应用的最小砖块。

## 将一个元素渲染为 DOM

想要将一个 React 元素渲染到根 DOM 节点中，只需把它们一起传入 ReactDOM.render()：

```js
const element = <h1>Hello, world</h1>;
ReactDOM.render(element, document.getElementById('root'));
```

ReactDOM.render() 便是将 vdom 转换成真实 dom 的工具了

## 更新已渲染的元素

React 元素是不可变对象。一旦被创建，你就无法更改它的子元素或者属性。一个元素就像电影的单帧：它代表了某个特定时刻的 UI。

**React 只更新它需要更新的部分** -- react diff 算法



























