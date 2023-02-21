---
title: node 基础 - egg
date: 2022-06-06
tags:
 - node
categories:
 - node
---

## 2.1 Egg.js的安装、配置、项目基本结构

### 2.1.1 安装

```
$ mkdir egg-example && cd egg-example
$ npm init egg --type=simple
$ npm i
```

```
$ npm run dev
$ open http://localhost:7001
```

一个Egg项目就已经初始化好啦，可以跑起来了：


### 2.1.2 项目目录结构

egg-project

```
├── package.json
├── app.js (可选)
├── agent.js (可选)
├── app
|   ├── router.js
│   ├── controller
│   |   └── home.js
│   ├── service (可选)
│   |   └── user.js
│   ├── middleware (可选)
│   |   └── response_time.js
│   ├── schedule (可选)
│   |   └── my_task.js
│   ├── public (可选)
│   |   └── reset.css
│   ├── view (可选)
│   |   └── home.tpl
│   └── extend (可选)
│       ├── helper.js (可选)
│       ├── request.js (可选)
│       ├── response.js (可选)
│       ├── context.js (可选)
│       ├── application.js (可选)
│       └── agent.js (可选)
├── config
|   ├── plugin.js
|   ├── config.default.js
│   ├── config.prod.js
|   ├── config.test.js (可选)
|   ├── config.local.js (可选)
|   └── config.unittest.js (可选)
└── test
    ├── middleware
    |   └── response_time.test.js
    └── controller
        └── home.test.js
```

### 2.1.3 内置的ctx对象

ctx这个对象非常重要，请求来的参数，返回去的消息都需要通过ctx这个对象获取或者设置
ctx是继承koa的context对象通过设置ctx.body， 可以改变返回信息



### 2.1.4. 尝试新写一个路由

在controller中

```
 async list() {
    const { ctx } = this;
    ctx.body = {
      code: 200,
      data: [
        {
          id: '1',
          name: '张三',
        },
        {
          id: '2',
          name: '李四',
        },
        {
          id: '3',
          name: '王五',
        },
      ],
      msg: '操作成功',
    };
  }
```

在router.js中匹配新写的路由

```
router.get('/list', controller.home.list);
```