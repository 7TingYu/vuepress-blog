---
title: react 基础 - JSX
date: 2022-3-23
tags:
 - react
categories:
 - react
---

JSX，是一个 JavaScript 的语法扩展。JSX 可以很好地描述 UI 应该呈现出它应有交互的本质形式。JSX 可能会使人联想到模板语言，但它具有 JavaScript 的全部功能。

## 在 JSX 中嵌入表达式

```js
const name = 'Josh Perez';
const element = <h1>Hello, {name}</h1>;

ReactDOM.render(
  element,
  document.getElementById('root')
);
```

在 JSX 语法中，你可以在大括号内放置任何有效的 JavaScript 表达式。


## JSX 也是一个表达式

也就是说，你可以在 if 语句和 for 循环的代码块中使用 JSX，将 JSX 赋值给变量，把 JSX 当作参数传入，以及从函数中返回 JSX：

```js
function getGreeting(user) {
  if (user) {
    return <h1>Hello, {formatName(user)}!</h1>;
  }
  return <h1>Hello, Stranger.</h1>;
}
```

## JSX 中指定属性

你可以通过使用引号，来将属性值指定为字符串字面量：

```js
const element = <a href="https://www.reactjs.org"> link </a>;
```

也可以使用大括号，来在属性值中插入一个 JavaScript 表达式：

```js
const element = <img src={user.avatarUrl}></img>;
```

## JSX 防止注入攻击

你可以安全地在 JSX 当中插入用户输入内容：

```js
const title = response.potentiallyMaliciousInput;
// 直接使用是安全的：
const element = <h1>{title}</h1>;
```

## JSX 表示对象

Babel 会把 JSX 转译成一个名为 React.createElement() 函数调用。

以下两种示例代码完全等效：

```js
const element = (
  <h1 className="greeting">
    Hello, world!
  </h1>
);
```


```js
const element = React.createElement(
  'h1',
  {className: 'greeting'},
  'Hello, world!'
);
```


















