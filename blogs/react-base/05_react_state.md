---
title: react 基础 - State & 生命周期
date: 2022-3-23
tags:
 - react
categories:
 - react
---

## State

State 为组件本身的状态管理，它本身保存了当前 **class 组件**的数据状态

正确地使用 State 你需要了解：


### 不要直接修改 State

直接修改不会重新渲染组件，如果你想要渲染组件，可以使用 `setState()`

```js
this.setState({comment: 'Hello'});
```


### State 的更新可能是异步的

出于性能考虑，React 可能会把多个 setState() 调用合并成一个调用。

因为 this.props 和 this.state 可能会异步更新，所以你不要依赖他们的值来更新下一个状态。

```js
// Wrong
this.setState({
  counter: this.state.counter + this.props.increment,
});
```

要解决这个问题，可以让 setState() 接收一个函数而不是一个对象。

```js
// Correct
this.setState((state, props) => ({
  counter: state.counter + props.increment
}));
```


### State 的更新会被合并

当你调用 setState() 的时候，React 会把你提供的对象合并到当前的 state。


## 数据是向下流动的(单向数据流)

不管是父组件或是子组件都无法知道某个组件是有状态的还是无状态的，并且它们也并不关心它是函数组件还是 class 组件。

这就是为什么称 state 为局部的或是封装的的原因。除了拥有并设置了它的组件，其他组件都无法访问。

组件可以选择把它的 state 作为 props 向下传递到它的子组件中：

```js
<FormattedDate date={this.state.date} />
```

FormattedDate 组件会在其 props 中接收参数 date，但是组件本身无法知道它是来自于 Clock 的 state，或是 Clock 的 props，还是手动输入的：

```js
function FormattedDate(props) {
  return <h2>It is {props.date.toLocaleTimeString()}.</h2>;
}
```


## 生命周期

### old lifecycle

![old lifecycle](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/e12b2e35c8444f19b795b27e38f4c149~tplv-k3u1fbpfcp-zoom-in-crop-mark:1304:0:0:0.awebp)

挂载

- constructor
- componentWillMount
- render
- componentDidMount

更新

- componentWillReceiveProps
- shouldComponentUpdate
- componentWillUpdate
- render
- componentDidUpdate

卸载

- componentWillUnmount

### new lifecycle

![new lifecycle](https://p6-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/a7d8676f379d4d96bbf0ebd9a8528594~tplv-k3u1fbpfcp-zoom-in-crop-mark:1304:0:0:0.awebp)


挂载

- constructor
- getDerivedStateFromProps
- render
- componentDidMount


更新

- getDerivedStateFromProps
- shouldComponentUpdate
- render
- getSnapshotBeforeUpdate
- componentDidUpdate


卸载

- componentWillUnmount

React从v16.3开始废弃 `componentWillMount` `componentWillReceiveProps` `componentWillUpdate` 三个钩子函数


废弃的原因是在为了 fiber 打基础。


### Fiber

React Fiber的机制: 利用浏览器 requestIdleCallback 将可中断的任务进行分片处理，每一个小片的运行时间很短，这样唯一的线程就不会被独占


Reconciliation 这个过程有可能暂停然后继续执行，所以挂载和更新之前的生命周期钩子就有可能不执行或者多次执行；


### 详解新的生命周期


**constructor()**

constructor() 在React组件挂载之前被调用，在为React.Component子类实现构造函数时，应在其他语句之前调用 super()

> 如果不初始化 state 或不进行方法绑定，则不需要写 constructor() , 只需要设置 this.state 即可


> 不能在 constructor()构造函数内部调用 this.setState(), 因为此时第一次 render()还未执行，也就意味DOM节点还未挂载



**static getDerivedStateFromProps(nextProps, state)**

getDerivedStateFromProps() 在调用 render方法之前调用，在初始化和后续更新都会被调用


> 返回值：返回一个对象来更新 state,  如果返回 null 则不更新任何内容


> 参数： 第一个参数为即将更新的 props,  第二个参数为上一个状态的 state , 可以比较props 和 state来加一些限制条件，防止无用的state更新


> 注意：getDerivedStateFromProps 是一个静态函数，不能使用this, 也就是只能作一些无副作用的操作


**render()**

render() 方法是class组件中唯一必须实现的方法，用于渲染dom, render()方法必须返回reactDOM

> 注意： 不要在 render 里面 setState, 否则会触发死循环导致内存崩溃


**componentDidMount()**

componentDidMount() 在组件挂载后 (插入DOM树后) 立即调用，componentDidMount() 是发送网络请求、启用事件监听方法的好时机，并且可以在 此钩子函数里直接调用 setState()


**shouldComponentUpdate(nextProps, nextState)**

shouldComponentUpdate() 在组件更新之前调用，可以控制组件是否进行更新， 返回true时组件更新， 返回false则不更新

> 包含两个参数，第一个是即将更新的 props 值，第二个是即将跟新后的 state 值，可以根据更新前后的 props 或 state 来比较加一些限制条件，决定是否更新，进行性能优化


> 不建议在 shouldComponentUpdate() 中进行深层比较或使用 JSON.stringify()。这样非常影响效率，且会损害性能


> 不要 shouldComponentUpdate 中调用 setState()，否则会导致无限循环调用更新、渲染，直至浏览器内存崩溃


> 可以使用内置 PureComponent 组件替代


**getSnapshotBeforeUpdate(prevProps, prevState)**

getSnapshotBeforeUpdate() 在最近一次的渲染输出被提交之前调用。也就是说，在 render 之后，即将对组件进行挂载时调用。

> 它可以使组件在 DOM 真正更新之前捕获一些信息（例如滚动位置），此生命周期返回的任何值都会作为参数传递给 componentDidUpdate()。如不需要传递任何值，那么请返回 null

**componentDidUpdate(prevProps, prevState, snapshot)**

componentDidUpdate() 会在更新后会被立即调用。首次渲染不会执行

> 包含三个参数，第一个是上一次props值。 第二个是上一次state值。如果组件实现了 getSnapshotBeforeUpdate() 生命周期（不常用），第三个是“snapshot” 参数传递


> 可以进行前后props的比较进行条件语句的限制，来进行 setState() , 否则会导致死循环

**componentWillUnmount()**

componentWillUnmount() 在组件即将被卸载或销毁时进行调用。

> 此生命周期是取消网络请求、移除监听事件、清理 DOM 元素、清理定时器等操作的好时机






