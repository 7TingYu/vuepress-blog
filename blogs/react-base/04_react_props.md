---
title: react 基础 - 组件 & Props
date: 2022-3-23
tags:
 - react
categories:
 - react
---

组件允许你将 UI 拆分为独立可复用的代码片段，并对每个片段进行独立构思。

## 函数组件与 class 组件

定义组件最简单的方式就是编写 JavaScript 函数：

```js
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}
```

该函数是一个有效的 React 组件，因为它接收唯一带有数据的 “props”（代表属性）对象与并返回一个 React 元素。这类组件被称为“**函数组件**”，因为它本质上就是 JavaScript 函数。


你同时还可以使用 ES6 的 class 来定义组件(hook出现之前，以及我们想要友好的使用所有生命周期时)：

```js
class Welcome extends React.Component {
  render() {
    return <h1>Hello, {this.props.name}</h1>;
  }
}
```

## 渲染组件

```js
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}

const element = <Welcome name="Sara" />;
ReactDOM.render(
  element,
  document.getElementById('root')
);
```

让我们来回顾一下这个例子中发生了什么：

- 我们调用 ReactDOM.render() 函数，并传入 \<Welcome name="Sara" /> 作为参数。
- React 调用 Welcome 组件，并将 {name: 'Sara'} 作为 props 传入。
- Welcome 组件将 \<h1>Hello, Sara\</h1> 元素作为返回值。
- React DOM 将 DOM 高效地更新为 \<h1>Hello, Sara\</h1>。

> 注意： 组件名称必须以大写字母开头。


## Props 的只读性

组件无论是使用函数声明还是通过 class 声明，都决不能修改自身的 props。

```js
function sum(a, b) {
  return a + b;
}
```

这样的函数被称为“**纯函数**”，因为该函数不会尝试更改入参，且多次调用下相同的入参始终返回相同的结果。

React 非常灵活，但它也有一个严格的规则：

**所有 React 组件都必须像纯函数一样保护它们的 props 不被更改。**











