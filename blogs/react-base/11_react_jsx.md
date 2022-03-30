---
title: react 基础 - JSX
date: 2022-3-30
tags:
 - react
categories:
 - react
---


实际上，JSX 仅仅只是 React.createElement(component, props, ...children) 函数的语法糖。

```jsx
<MyButton color="blue" shadowSize={2}>
  Click Me
</MyButton>
```

会编译为：

```js
React.createElement(
  MyButton,
  {color: 'blue', shadowSize: 2},
  'Click Me'
)
```

如果没有子节点，你还可以使用自闭合的标签形式，如：

```jsx
<div className="sidebar" />
```

会编译为:

```js
React.createElement(
  'div',
  {className: 'sidebar'}
)
```

## 使用 JSX

### React 必须在作用域内

由于 JSX 会编译为 React.createElement 调用形式，所以 React 库也必须包含在 JSX 代码作用域内。


### 在 JSX 类型中使用点语法

在 JSX 中，你也可以使用点语法来引用一个 React 组件。

```js
import React from 'react';

const MyComponents = {
  DatePicker: function DatePicker(props) {
    return <div>Imagine a {props.color} datepicker here.</div>;
  }
}

function BlueDatePicker() {
  return <MyComponents.DatePicker color="blue" />;
}
```


### 用户定义的组件必须以大写字母开头


以小写字母开头的元素代表一个 HTML 内置组件，大写字母开头的元素则对应着在 JavaScript 引入或自定义的组件


```js
import React from 'react';

// 错误！组件应该以大写字母开头：
function hello(props) {
  // 正确！这种 <div> 的使用是合法的，因为 div 是一个有效的 HTML 标签
  return <div>Hello {props.toWhat}</div>;
}

function HelloWorld() {
  // 错误！React 会认为 <hello /> 是一个 HTML 标签，因为它没有以大写字母开头：
  return <hello toWhat="World" />;
}

```

要解决这个问题，我们需要重命名 hello 为 Hello，同时在 JSX 中使用 \<Hello /> ：


```js
import React from 'react';

// 正确！组件需要以大写字母开头：
function Hello(props) {
  // 正确！ 这种 <div> 的使用是合法的，因为 div 是一个有效的 HTML 标签：
  return <div>Hello {props.toWhat}</div>;
}

function HelloWorld() {
  // 正确！React 知道 <Hello /> 是一个组件，因为它是大写字母开头的：
  return <Hello toWhat="World" />;
}
```


### 在运行时选择类型


你不能将通用表达式作为 React 元素类型。如果你想通过通用表达式来（动态）决定元素类型，你需要首先将它赋值给大写字母开头的变量。

```js
import React from 'react';
import { PhotoStory, VideoStory } from './stories';

const components = {
  photo: PhotoStory,
  video: VideoStory
};

function Story(props) {
  // 错误！JSX 类型不能是一个表达式。
  return <components[props.storyType] story={props.story} />;
}
```


要解决这个问题, 需要首先将类型赋值给一个大写字母开头的变量：


```js
import React from 'react';
import { PhotoStory, VideoStory } from './stories';

const components = {
  photo: PhotoStory,
  video: VideoStory
};

function Story(props) {
  // 正确！JSX 类型可以是大写字母开头的变量。
  const SpecificStory = components[props.storyType];
  return <SpecificStory story={props.story} />;
}
```


## JSX 中的 Props


### JavaScript 表达式作为 Props


### 字符串字面量


### Props 默认值为 “True”


### 属性展开


## JSX 中的子元素


### 字符串字面量


### JSX 子元素


### JavaScript 表达式作为子元素


### 函数作为子元素


### 布尔类型、Null 以及 Undefined 将会忽略






