---
title: react 基础 - 列表 & Key
date: 2022-3-23
tags:
 - react
categories:
 - react
---


## 渲染多个组件

你可以通过使用 {} 在 JSX 内构建一个元素集合。

下面，我们使用 Javascript 中的 map() 方法来遍历 numbers 数组。将数组中的每个元素变成 \<li> 标签，最后我们将得到的数组赋值给 listItems：

```js
const numbers = [1, 2, 3, 4, 5];
const listItems = numbers.map((number) =>
  <li>{number}</li>
);
```

我们把整个 listItems 插入到 \<ul> 元素中，然后渲染进 DOM： 

```js
ReactDOM.render(
  <ul>{listItems}</ul>,
  document.getElementById('root')
);
```

## key

key 帮助 React 识别哪些元素改变了，比如被添加或删除。

## 用 key 提取组件

元素的 key 只有放在就近的数组上下文中才有意义。

## key 值在兄弟节点之间必须唯一

数组元素中使用的 key 在其兄弟节点之间应该是独一无二的。然而，它们不需要是全局唯一的。
