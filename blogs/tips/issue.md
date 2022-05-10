---
title: issue
date: 2022-05-09
tags:
 - js issue
categories:
 - 小识书屋
---

::: tip
这边用于存放一些 平时开发遇到的 奇奇怪怪的 问题
:::

## node的serve静态服务器模拟数据跨域问题(05-09)

### install

工具： server
安装： npm install -g serve
使用： serve -p 8080

### 解决跨域

安装的serve依赖包 serve/bin/serve.js 找到 handler 函数

安装路径可以通过`npm config get prefix`查看。

添加允许跨域的代码

```js
const handler = coroutine(function*(req, res) {
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Methods","PUT,POST,GET,DELETE,OPTIONS");
  res.setHeader("Access-Control-Allow-Headers", "Content-Type,Content-Length, Authorization, Accept,X-Requested-With");
  yield serverHandler(req, res, flags, current, ignoredFiles)
})
```

**以上方法不可用？查看源码**

添加 --cors 便能解决

```shell
serve --cors
```

server 版本 serve@13.0.2





