---
title: react 基础 - 组件间的通讯
date: 2022-8-29
tags:
 - react
categories:
 - react
---

## React组件间的通讯方式

- 父子
  - props
  - 实例方法
  - 回调函数
  - 事件冒泡
- 兄弟
  - 父组件
- 任意组件
  - 观察者模式
  - 全局变量
  - Context

### 父子

#### Props

Props 是目前为止最常用的方式，用于在组件之间传递信息。用 props 可以把数据从父组件传递到它的子组件中。

#### 实例方法

在父组件中可以用 refs 引用子组件，之后就可以调用子组件的实例方法了。

```jsx
class Child extends React.Component {
    myFunc() {
        console.log('hello')
    }
}

class Parent extends React.Component {
    render() {
        return (
            <Child ref={foo => {
                this.foo = foo
            }}>
            </Child>
        )
    }
    componentDidMount() {
        this.foo.myFunc()
        // hello
    }
}
```

#### 回调函数

子组件传给它的父组件, 可以通过回调函数的形式

#### 事件冒泡

当你想在父组件中捕获来自子组件中的 DOM 事件时，可以采用此方法。


### 兄弟

如果两个需要通讯的组件，它们拥有共同的父级组件，只是需要使用父级组件作为沟通的媒介




