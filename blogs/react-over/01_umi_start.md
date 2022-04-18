---
title: react umi - umi start
date: 2022-04-18
tags:
 - react
categories:
 - react
---


## umi

中文可发音为乌米，是一个可插拔的企业级 react 应用框架。

umi 以路由为基础的，支持类 next.js 的约定式路由，以及各种进阶的路由功能，并以此进行功能扩展，比如支持路由级的按需加载。


### 他和 dva、roadhog 是什么关系？

简单来说，

- roadhog 是基于 webpack 的封装工具，目的是简化 webpack 的配置
- umi 可以简单地理解为 roadhog + 路由，思路类似 next.js/nuxt.js，辅以一套插件机制，目的是通过框架的方式简化 React 开发
- dva 目前是纯粹的数据流，和 umi 以及 roadhog 之间并没有相互的依赖关系，可以分开使用也可以一起使用，个人觉得 umi + dva 是比较搭的


## 目录及约定

在文件和目录的组织上，umi 更倾向于选择约定的方式。

```shell
.
├── dist/                          // 默认的 build 输出目录
├── mock/                          // mock 文件所在目录，基于 express
├── config/
    ├── config.js                  // umi 配置，同 .umirc.js，二选一
└── src/                           // 源码目录，可选
    ├── layouts/index.js           // 全局布局
    ├── pages/                     // 页面目录，里面的文件即路由
        ├── .umi/                  // dev 临时目录，需添加到 .gitignore
        ├── .umi-production/       // build 临时目录，会自动删除
        ├── document.ejs           // HTML 模板
        ├── 404.js                 // 404 页面
        ├── page1.js               // 页面 1，任意命名，导出 react 组件
        ├── page1.test.js          // 用例文件，umi test 会匹配所有 .test.js 和 .e2e.js 结尾的文件
        └── page2.js               // 页面 2，任意命名
    ├── global.css                 // 约定的全局样式文件，自动引入，也可以用 global.less
    ├── global.js                  // 可以在这里加入 polyfill
    ├── app.js                     // 运行时配置文件
├── .umirc.js                      // umi 配置，同 config/config.js，二选一
├── .env                           // 环境变量
└── package.json
```


## 约定式路由

### 基础路由

假设 pages 目录结构如下：

```shell
+ pages/
  + users/
    - index.js
    - list.js
  - index.js
```

那么，umi 会自动生成路由配置如下：

```js
[
  { path: '/', component: './pages/index.js' },
  { path: '/users/', component: './pages/users/index.js' },
  { path: '/users/list', component: './pages/users/list.js' },
]
```

### 动态路由

umi 里约定，带 $ 前缀的目录或文件为动态路由。

```shell
+ pages/
  + $post/
    - index.js
    - comments.js
  + users/
    $id.js
  - index.js
```

会生成路由配置如下：

```js
[
  { path: '/', component: './pages/index.js' },
  { path: '/users/:id', component: './pages/users/$id.js' },
  { path: '/:post/', component: './pages/$post/index.js' },
  { path: '/:post/comments', component: './pages/$post/comments.js' },
]
```

### 可选的动态路由


umi 里约定动态路由如果带 $ 后缀，则为可选动态路由。

```shell
+ pages/
  + users/
    - $id$.js
  - index.js
```

会生成路由配置如下：


```js
[
  { path: '/': component: './pages/index.js' },
  { path: '/users/:id?': component: './pages/users/$id$.js' },
]
```


### 全局 layout

约定 src/layouts/index.js 为全局路由，返回一个 React 组件，通过 props.children 渲染子组件。


```js
export default function(props) {
  return (
    <>
      <Header />
      { props.children }
      <Footer />
    </>
  );
}
```

### 不同的全局 layout

在 layouts/index.js 对 location.path 做区分，渲染不同的 layout 。


### 404 路由

约定 pages/404.js 为 404 页面，需返回 React 组件



### 权限路由


umi 的权限路由是通过配置路由的 Routes 属性来实现。约定式的通过 yaml 注释添加，配置式的直接配上即可。

```js
[
  { path: '/', component: './pages/index.js' },
  { path: '/list', component: './pages/list.js', Routes: ['./routes/PrivateRoute.js'] },
]
```

