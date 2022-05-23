---
title: 事件总线 eventbus
date: 2022-03-05
tags:
 - js utils
categories:
 - 小识书屋
---

## 低配版

```js
class EventBus {
  constructor() {
    this.events = this.events || new Object();
  }

  // 发布
  emit(type, ...args) {
    const events = this.events[type];
    // 查看这个type的event有多少个回调函数，如果有多个需要依次调用。
    if (Array.isArray(events)) {
      // 我们希望返回一个结果
      return events.map((item) => item.apply(this, args));
    } else {
      // 当 events 不为数组，说明还未创建，返回空
      return;
    }
  }

  // 订阅
  on(type, fun) {
    const e = this.events[type];

    if (!e) {
      //如果从未注册过监听函数，则将函数放入数组存入对应的键名下
      this.events[type] = [fun];
    } else {
      //如果注册过，则直接放入
      e.push(fun);
    }
  }

  // 卸载
  off(type) {
    delete this.events[type];
  }

  // 清除
  clear() {
    this.events = new Object();
  }
}

const eventBus = new EventBus();
export default eventBus;
```




