---
title: node 基础 - koa
date: 2022-07-08
tags:
 - node
categories:
 - node
---

## 准备初始代码

- github

```shell
git clone -b start-point https://github.com/tuture-dev/koa-quickstart.git
```

- gitee

```shell
git clone -b start-point https://gitee.com/tuture/koa-quickstart.git
```

进入项目，安装依赖：

```shell
cd koa-quickstart && npm install
```

### 最简单的 Koa 服务器

创建 `src/server.ts` ，编写第一个 Koa 服务器，代码如下：

```
// src/server.ts
import Koa from 'koa';
import cors from '@koa/cors';
import bodyParser from 'koa-bodyparser';

// 初始化 Koa 应用实例
const app = new Koa();

// 注册中间件
app.use(cors());
app.use(bodyParser());

// 响应用户请求
app.use((ctx) => {
  ctx.body = 'Hello Koa';
});

// 运行服务器
app.listen(3000);
```

整个流程与一个基本的 Express 服务器几乎完全一致：

1.  初始化应用实例 `app`
1.  注册相关的中间件（跨域 `cors` 和请求体解析中间件 `bodyParser`）
1.  添加请求处理函数，响应用户请求
1.  运行服务器

定睛一看，第 3 步中的请求处理函数（Request Handler）好像不太一样。在 Express 框架中，一个请求处理函数一般是这样的：

```
function handler(req, res) {
  res.send('Hello Express');
}
```

两个参数分别对应请求对象（Request）和响应对象（Response），但是在 Koa 中，请求处理函数却只有一个参数 `ctx` （Context，上下文），然后只需向上下文对象写入相关的属性即可（例如这里就是写入到返回数据 `body` 中）：

```
function handler(ctx) {
  ctx.body = 'Hello Koa';
}
```

我的天，Koa 这是故意偷工减料的吗？先不用急，我们马上在下一节讲解中间件时就会了解到 Koa 这样设计的独到之处。

### 运行服务器

我们通过 `npm start` 就能开启服务器了。可以通过 Curl （或者 Postman 等）来测试我们的 API：

```
$ curl localhost:3000
Hello Koa
```

> **提示**
>
> 我们的脚手架中配置好了 [Nodemon](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fremy%2Fnodemon "https://github.com/remy/nodemon")，因此接下来无需关闭服务器，修改代码保存后会自动加载最新的代码并运行。

## 第一个 Koa 中间件

严格意义上来说，Koa 只是一个中间件框架，正如它的介绍所说：

> Expressive middleware for node.js using ES2017 async functions.（通过 ES2017 async 函数编写富有表达力的 Node.js 中间件）

下面这个表格更能说明 Koa 和 Express 的鲜明对比：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/372626e44bf74b14bbed73809ef07952~tplv-k3u1fbpfcp-zoom-1.image)

可以看到，Koa 实际上对标的是 [Connect](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fsenchalabs%2Fconnect "https://github.com/senchalabs/connect")（Express 底层的中间件层），而不包含 Express 所拥有的其他功能，例如路由、模板引擎、发送文件等。接下来，我们就来学习 Koa 最重要的知识点：**中间件**。

### 大名鼎鼎的“洋葱模型”

你也许从来没有用过 Koa 框架，但很有可能听说过“洋葱模型”，而 Koa 正是洋葱模型的代表框架之一。下面这个图你也许很熟悉了：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/5c2c64fcebe14905b1babb00eb0dc24c~tplv-k3u1fbpfcp-zoom-1.image)

不过以个人观点，这个图实在是太像“洋葱”了，反而不太好理解。接下来我们将以更清晰直观的方式来感受 Koa 中间件的设计之美。首先我们来看一下 Express 的中间件是什么样的：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/d5998cf4d8dc4c89b3ae10aa96dfeae5~tplv-k3u1fbpfcp-zoom-1.image)

请求（Request）直接依次贯穿各个中间件，最后通过请求处理函数返回响应（Response），非常简单。然后我们来看看 Koa 的中间件是什么样的：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/4c383539c6114fdb86499a9f91e34fe0~tplv-k3u1fbpfcp-zoom-1.image)

可以看到，Koa 中间件不像 Express 中间件那样在请求通过了之后就完成了自己的使命；相反，中间件的执行清晰地分为**两个阶段**。我们马上来看下 Koa 中间件具体是什么样的。

### Koa 中间件的定义

Koa 的中间件是这样一个函数：

```
async function middleware(ctx, next) {
  // 第一阶段
  await next();
  // 第二阶段
}
```

第一个参数就是 Koa Context，也就是上图中贯穿所有中间件和请求处理函数的绿色箭头所传递的内容，里面**封装了请求体和响应体**（实际上还有其他属性，但这里暂时不讲），分别可以通过 `ctx.request` 和 `ctx.response` 来获取，以下是一些常用的属性：

```
ctx.url    // 相当于 ctx.request.url
ctx.body   // 相当于 ctx.response.body
ctx.status // 相当于 ctx.response.status
```

> **提示**
>
> 关于所有请求和响应上面的属性及其别称，请参考 [Context API 文档](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fkoajs%2Fkoa%2Fblob%2Fmaster%2Fdocs%2Fapi%2Fcontext.md "https://github.com/koajs/koa/blob/master/docs/api/context.md")。

中间件的第二个参数便是 `next` 函数，这个熟悉 Express 的同学一定知道它是干什么的：用来把控制权转交给下一个中间件。但是它跟 Express 的 `next` 函数本质的区别在于，**Koa 的 ****`next`**** 函数返回的是一个 Promise**，在这个 Promise 进入完成状态（Fulfilled）后，就会去执行中间件中第二阶段的代码。

那么我们不禁要问：这样把中间件的执行拆分为两个阶段，到底有什么好处吗？我们来通过一个非常经典的例子来感受一下：日志记录中间件（包括响应时间的计算）。

### 实战：日志记录中间件

让我们来实现一个简单的日志记录中间件 `logger` ，用于记录每次请求的方法、URL、状态码和响应时间。创建 `src/logger.ts` ，代码如下：

```
// src/logger.ts
import { Context } from 'koa';

export function logger() {
  return async (ctx: Context, next: () => Promise<void>) => {
    const start = Date.now();
    await next();
    const ms = Date.now() - start;
    console.log(`${ctx.method} ${ctx.url} ${ctx.status} - ${ms}ms`);
  };
}
```

严格意义上讲，这里的 `logger` 是一个**中间件工厂函数**（Factory），调用这个工厂函数后返回的结果才是真正的 Koa 中间件。之所以写成一个工厂函数，是因为我们可以通过给工厂函数传参的方式来更好地控制中间件的行为（当然这里的 `logger` 比较简单，就没有任何参数）。

在这个中间件的第一阶段，我们通过 `Date.now()` 先获取请求进入的时间，然后通过 `await next()` 让出执行权，等待下游中间件运行结束后，再在第二阶段通过计算 `Date.now()` 的差值来得出处理请求所用的时间。

思考一下，如果用 Express 来实现这个功能，中间件应该怎么写，会有 Koa 这么简单优雅吗？

> **提示**
>
> 这里通过两个 `Date.now()` 之间的差值来计算运行时间其实是不精确的，为了获取更准确的时间，建议使用 `process.hrtime()` 。

然后我们在 `src/server.ts` 中把刚才的 `logger` 中间件通过 `app.use` 注册进去，代码如下：

```
// src/server.ts
// ...

import { logger } from './logger';

// 初始化 Koa 应用实例
const app = new Koa();

// 注册中间件
app.use(logger());
app.use(cors());
app.use(bodyParser());

// ...
```

这时候再访问我们的服务器（通过 Curl 或者其他请求工具），应该可以看到输出日志：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/da0b6530625e40ea9c9ce93a8ca2798c~tplv-k3u1fbpfcp-zoom-1.image)

关于 Koa 框架本身的内容基本讲完了，但是对于一个比较完整的 Web 服务器来说，我们还需要更多的“武器装备”才能应对日常的业务逻辑。在接下来的部分，我们将通过社区的优秀组件来解决两个关键问题：路由和数据库，并演示如何结合 Koa 框架进行使用。

## 实现路由配置

由于 Koa 只是一个中间件框架，所以路由的实现需要独立的 npm 包。首先安装 `@koa/router` 及其 TypeScript 类型定义：

```
$ npm install @koa/router
$ npm install @types/koa__router -D
```

> **注意**
>
> 有些教程使用 `koa-router` ，但由于 `koa-router` 目前处于几乎无人维护的状态，所以我们这里使用维护更积极的 Fork 版本 `@koa/router`。

### 路由规划

在这篇教程中，我们将实现以下路由：

-   `GET /users` ：查询所有的用户
-   `GET /users/:id` ：查询单个用户
-   `PUT /users/:id` ：更新单个用户
-   `DELETE /users/:id` ：删除单个用户
-   `POST /users/login` ：登录（获取 JWT Token）
-   `POST /users/register` ：注册用户

### 实现 Controller

在 `src` 中创建 `controllers` 目录，用于存放控制器有关的代码。首先是 `AuthController` ，创建 `src/controllers/auth.ts` ，代码如下：

```
// src/controllers/auth.ts
import { Context } from 'koa';

export default class AuthController {
  public static async login(ctx: Context) {
    ctx.body = 'Login controller';
  }

  public static async register(ctx: Context) {
    ctx.body = 'Register controller';
  }
}
```

然后创建 `src/controllers/user.ts`，代码如下：

```
// src/controllers/user.ts
import { Context } from 'koa';

export default class UserController {
  public static async listUsers(ctx: Context) {
    ctx.body = 'ListUsers controller';
  }

  public static async showUserDetail(ctx: Context) {
    ctx.body = `ShowUserDetail controller with ID = ${ctx.params.id}`;
  }

  public static async updateUser(ctx: Context) {
    ctx.body = `UpdateUser controller with ID = ${ctx.params.id}`;
  }

  public static async deleteUser(ctx: Context) {
    ctx.body = `DeleteUser controller with ID = ${ctx.params.id}`;
  }
}
```

注意到在后面三个 Controller 中，我们通过 `ctx.params` 获取到路由参数 `id` 。

### 实现路由

然后我们创建 `src/routes.ts`，用于把控制器挂载到对应的路由上面：

```
// src/routes.ts
import Router from '@koa/router';

import AuthController from './controllers/auth';
import UserController from './controllers/user';

const router = new Router();

// auth 相关的路由
router.post('/auth/login', AuthController.login);
router.post('/auth/register', AuthController.register);

// users 相关的路由
router.get('/users', UserController.listUsers);
router.get('/users/:id', UserController.showUserDetail);
router.put('/users/:id', UserController.updateUser);
router.delete('/users/:id', UserController.deleteUser);

export default router;
```

可以看到 `@koa/router` 的使用方式基本上与 Express Router 保持一致。

### 注册路由

最后，我们需要将 `router` 注册为中间件。打开 `src/server.ts`，修改代码如下：

```
// src/server.ts
// ...

import router from './routes';
import { logger } from './logger';

// 初始化 Koa 应用实例
const app = new Koa();

// 注册中间件
app.use(logger());
app.use(cors());
app.use(bodyParser());

// 响应用户请求
app.use(router.routes()).use(router.allowedMethods());

// 运行服务器
app.listen(3000);
```

可以看到，这里我们调用 `router` 对象的 `routes` 方法获取到对应的 Koa 中间件，还调用了 `allowedMethods` 方法注册了 HTTP 方法检测的中间件，这样当用户通过不正确的 HTTP 方法访问 API 时，就会自动返回 405 Method Not Allowed 状态码。

我们通过 Curl 来测试路由（也可以自行使用 Postman）：

```
$ curl localhost:3000/hello
Not Found
$ curl localhost:3000/auth/register
Method Not Allowed
$ curl -X POST localhost:3000/auth/register
Register controller
$ curl -X POST localhost:3000/auth/login
Login controller
$ curl localhost:3000/users
ListUsers controller
$ curl localhost:3000/users/123
ShowUserDetail controller with ID = 123
$ curl -X PUT localhost:3000/users/123
UpdateUser controller with ID = 123
$ curl -X DELETE localhost:3000/users/123
DeleteUser controller with ID = 123
```

同时可以看到服务器的输出日志如下：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/8c55eb5dd1654d02b19f9460e23020f7~tplv-k3u1fbpfcp-zoom-1.image)

路由已经接通，接下来就让我们来接入真实的数据吧！

## 接入 MySQL 数据库

从这一步开始，我们将正式接入数据库。Koa 本身是一个中间件框架，理论上可以接入任何类型的数据库，这里我们选择流行的关系型数据库 MySQL。并且，由于我们使用了 TypeScript 开发，因此这里使用为 TS 量身打造的 [ORM](https://link.juejin.cn?target=http%3A%2F%2Fwww.ruanyifeng.com%2Fblog%2F2019%2F02%2Form-tutorial.html "http://www.ruanyifeng.com/blog/2019/02/orm-tutorial.html") 库 TypeORM。

### 数据库的准备工作

首先，请安装和配置好 MySQL 数据库，可以通过两种方式：

-   官网下载安装包，这里是[下载地址](https://link.juejin.cn?target=https%3A%2F%2Fdev.mysql.com%2Fdownloads%2Fmysql%2F "https://dev.mysql.com/downloads/mysql/")
-   使用 MySQL Docker 镜像

在确保 MySQL 实例运行之后，我们打开终端，通过命令行连接数据库：

```
$ mysql -u root -p
```

输入预先设置好的根帐户密码之后，就进入了 MySQL 的交互式执行客户端，然后运行以下命令：

```
--- 创建数据库
CREATE DATABASE koa;

--- 创建用户并授予权限
CREATE USER 'user'@'localhost' IDENTIFIED BY 'pass';
GRANT ALL PRIVILEGES ON koa.* TO 'user'@'localhost';

--- 处理 MySQL 8.0 版本的认证协议问题
ALTER USER 'user'@'localhost' IDENTIFIED WITH mysql_native_password BY 'pass';
flush privileges;
```

### TypeORM 的配置和连接

首先安装相关的 npm 包，分别是 MySQL 驱动、TypeORM 及 `reflect-metadata`（反射 API 库，用于 TypeORM 推断模型的元数据）：

```
$ npm install mysql typeorm reflect-metadata
```

然后在项目根目录创建 `ormconfig.json` ，TypeORM 会读取这个数据库配置进行连接，代码如下：

```
// ormconfig.json
{
  "type": "mysql",
  "host": "localhost",
  "port": 3306,
  "username": "user",
  "password": "pass",
  "database": "koa",
  "synchronize": true,
  "entities": ["src/entity/*.ts"],
  "cli": {
    "entitiesDir": "src/entity"
  }
}
```

这里有一些需要解释的字段：

-   `database` 就是我们刚刚创建的 `koa` 数据库
-   `synchronize` 设为 `true` 能够让我们每次修改模型定义后都能自动同步到数据库*（如果你接触过其他的 ORM 库，其实就是自动数据迁移）*
-   `entities` 字段定义了模型文件的路径，我们马上就来创建

接着修改 `src/server.ts`，在其中连接数据库，代码如下：

```
// src/server.ts
import Koa from 'koa';
import cors from '@koa/cors';
import bodyParser from 'koa-bodyparser';
import { createConnection } from 'typeorm';
import 'reflect-metadata';

import router from './routes';
import { logger } from './logger';

createConnection()
  .then(() => {
    // 初始化 Koa 应用实例
    const app = new Koa();

    // 注册中间件
    app.use(logger());
    app.use(cors());
    app.use(bodyParser());

    // 响应用户请求
    app.use(router.routes()).use(router.allowedMethods());

    // 运行服务器
    app.listen(3000);
  })
  .catch((err: string) => console.log('TypeORM connection error:', err));
```

### 创建数据模型定义

在 `src` 目录下创建 `entity` 目录，用于存放数据模型定义文件。在其中创建 `user.ts` ，代表用户模型，代码如下：

```
// src/entity/user.ts
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class User {
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  name: string;

  @Column({ select: false })
  password: string;

  @Column()
  email: string;
}
```

可以看到，用户模型有四个字段，其含义很容易理解。而 TypeORM 则是通过[装饰器](https://link.juejin.cn?target=https%3A%2F%2Fwww.tslang.cn%2Fdocs%2Fhandbook%2Fdecorators.html "https://www.tslang.cn/docs/handbook/decorators.html")这种优雅的方式来将我们的 `User` 类映射到数据库中的表。这里我们使用了三个装饰器：

-   `Entity` 用于装饰整个类，使其变成一个数据库模型
-   `Column` 用于装饰类的某个属性，使其对应于数据库表中的一列，可提供一系列选项参数，例如我们给 `password` 设置了 `select: false` ，使得这个字段在查询时默认不被选中
-   `PrimaryGeneratedColumn` 则是装饰主列，它的值将自动生成

> **提示**
>
> 关于 TypeORM 所有的装饰器定义及其详细使用，请参考其[装饰器文档](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Ftypeorm%2Ftypeorm%2Fblob%2Fmaster%2Fdocs%2Fzh_CN%2Fdecorator-reference.md "https://github.com/typeorm/typeorm/blob/master/docs/zh_CN/decorator-reference.md")。

### 在 Controller 中操作数据库

然后就可以在 Controller 中进行数据的增删改查操作了。首先我们打开 `src/controllers/user.ts` ，实现所有 Controller 的逻辑，代码如下：

```
// src/controllers/user.ts
import { Context } from 'koa';
import { getManager } from 'typeorm';

import { User } from '../entity/user';

export default class UserController {
  public static async listUsers(ctx: Context) {
    const userRepository = getManager().getRepository(User);
    const users = await userRepository.find();

    ctx.status = 200;
    ctx.body = users;
  }

  public static async showUserDetail(ctx: Context) {
    const userRepository = getManager().getRepository(User);
    const user = await userRepository.findOne(+ctx.params.id);

    if (user) {
      ctx.status = 200;
      ctx.body = user;
    } else {
      ctx.status = 404;
    }
  }

  public static async updateUser(ctx: Context) {
    const userRepository = getManager().getRepository(User);
    await userRepository.update(+ctx.params.id, ctx.request.body);
    const updatedUser = await userRepository.findOne(+ctx.params.id);

    if (updatedUser) {
      ctx.status = 200;
      ctx.body = updatedUser;
    } else {
      ctx.status = 404;
    }
  }

  public static async deleteUser(ctx: Context) {
    const userRepository = getManager().getRepository(User);
    await userRepository.delete(+ctx.params.id);

    ctx.status = 204;
  }
}
```

TypeORM 中操作数据模型主要是通过 `Repository` 实现的，在 Controller 中，可以通过 `getManager().getRepository(Model)` 来获取到，之后 `Repository` 的查询 API 就与其他的库很类似了。

> **提示**
>
> 关于 Repository 所有的查询 API，请参考[这里的文档](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Ftypeorm%2Ftypeorm%2Fblob%2Fmaster%2Fdocs%2Fzh_CN%2Frepository-api.md "https://github.com/typeorm/typeorm/blob/master/docs/zh_CN/repository-api.md")。

细心的你应该还发现我们通过 `ctx.request.body` 获取到了请求体的数据，这是我们在第一步就配置好的 `bodyParser` 中间件在 Context 对象中添加的。

然后我们修改 `AuthController` ，实现具体的注册逻辑。由于密码不能明文保存在数据库中，需要使用非对称算法进行加密，这里我们使用曾经获得过密码加密大赛冠军的 [Argon2](https://link.juejin.cn?target=https%3A%2F%2Fwww.argon2.com%2F "https://www.argon2.com/") 算法。安装对应的 npm 包：

```
npm install argon2
```

然后实现具体的 `register` Controller，修改 `src/controllers/auth.ts`，代码如下：

```
// src/controllers/auth.ts
import { Context } from 'koa';
import * as argon2 from 'argon2';
import { getManager } from 'typeorm';

import { User } from '../entity/user';

export default class AuthController {
  // ...

  public static async register(ctx: Context) {
    const userRepository = getManager().getRepository(User);

    const newUser = new User();
    newUser.name = ctx.request.body.name;
    newUser.email = ctx.request.body.email;
    newUser.password = await argon2.hash(ctx.request.body.password);

    // 保存到数据库
    const user = await userRepository.save(newUser);

    ctx.status = 201;
    ctx.body = user;
  }
}
```

确保服务器在运行之后，我们就可以开始测试一波了。首先是注册用户（这里我用 Postman 演示，直观一些）：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/a4b3bb213e5545549ce1cdbd91be4ccc~tplv-k3u1fbpfcp-zoom-1.image)

你可以继续注册几个用户，然后继续访问 `/users` 相关的路由，应该可以成功地获取、修改和删除相应的数据了！

## 实现 JWT 鉴权

JSON Web Token（JWT）是一种流行的 RESTful API 鉴权方案。这里我们将手把手带你学会如何在 Koa 框架中使用 JWT 鉴权，但是不会过多讲解其原理（可参考[这篇文章](https://link.juejin.cn?target=http%3A%2F%2Fwww.ruanyifeng.com%2Fblog%2F2018%2F07%2Fjson_web_token-tutorial.html "http://www.ruanyifeng.com/blog/2018/07/json_web_token-tutorial.html")进行学习）。

首先安装相关的 npm 包：

```
npm install koa-jwt jsonwebtoken
npm install @types/jsonwebtoken -D
```

创建 `src/constants.ts` ，用于存放 JWT Secret 常量，代码如下：

```
// src/constants.ts
export const JWT_SECRET = 'secret';
```

在实际开发中，请替换成一个足够复杂的字符串，并且最好通过环境变量的方式注入。

### 重新规划路由

有些路由我们希望只有已登录的用户才有权查看（*受保护的路由*），而另一些路由则是所有请求都可以访问（*不受保护的路由*）。在 Koa 的洋葱模型中，我们可以这样实现：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/0b985f6ddd88475d88af6413b7dc71ef~tplv-k3u1fbpfcp-zoom-1.image)

所有请求都可以直接访问未受保护的路由，但是受保护的路由就放在 JWT 中间件的后面（或者从洋葱模型的角度看是“里面”），这样对于没有携带 JWT Token 的请求就直接返回，而不会继续传递下去。

想法明确之后，打开 `src/routes.ts` 路由文件，修改代码如下：

```
// src/routes.ts
import Router from '@koa/router';

import AuthController from './controllers/auth';
import UserController from './controllers/user';

const unprotectedRouter = new Router();

// auth 相关的路由
unprotectedRouter.post('/auth/login', AuthController.login);
unprotectedRouter.post('/auth/register', AuthController.register);

const protectedRouter = new Router();

// users 相关的路由
protectedRouter.get('/users', UserController.listUsers);
protectedRouter.get('/users/:id', UserController.showUserDetail);
protectedRouter.put('/users/:id', UserController.updateUser);
protectedRouter.delete('/users/:id', UserController.deleteUser);

export { protectedRouter, unprotectedRouter };
```

上面我们分别实现了 `protectedRouter` 和 `unprotectedRouter` ，分别对应于需要 JWT 中间件保护的路由和不需要保护的路由。

### 注册 JWT 中间件

接着便是注册 JWT 中间件，并分别在其前后注册不需要保护的路由 `unprotectedRouter` 和需要保护的路由 `protectedRouter`。修改服务器文件 `src/server.ts` ，代码如下：

```
// src/server.ts
// ...
import jwt from 'koa-jwt';
import 'reflect-metadata';

import { protectedRouter, unprotectedRouter } from './routes';
import { logger } from './logger';
import { JWT_SECRET } from './constants';

createConnection()
  .then(() => {
    // ...

    // 无需 JWT Token 即可访问
    app.use(unprotectedRouter.routes()).use(unprotectedRouter.allowedMethods());

    // 注册 JWT 中间件
    app.use(jwt({ secret: JWT_SECRET }).unless({ method: 'GET' }));

    // 需要 JWT Token 才可访问
    app.use(protectedRouter.routes()).use(protectedRouter.allowedMethods());

    // ...
  })
  // ...
```

对应刚才“洋葱模型”的设计图，是不是感觉很直观？

> **提示**
>
> 在 JWT 中间件注册完毕后，如果用户请求携带了有效的 Token，后面的 `protectedRouter` 就可以通过 `ctx.state.user` 获取到 Token 的内容（更精确的说法是 Payload，负载，一般是用户的关键信息，例如 ID）了；反之，如果 Token 缺失或无效，那么 JWT 中间件会直接自动返回 401 错误。关于 koa-jwt 的更多使用细节，请参考其[文档](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fkoajs%2Fjwt "https://github.com/koajs/jwt")。

### 在 Login 中签发 JWT Token

我们需要提供一个 API 端口让用户可以获取到 JWT Token，最合适的当然是登录接口 `/auth/login`。打开 `src/controllers/auth.ts` ，在 `login` 控制器中实现签发 JWT Token 的逻辑，代码如下：

```
// src/controllers/auth.ts
// ...
import jwt from 'jsonwebtoken';

// ...
import { JWT_SECRET } from '../constants';

export default class AuthController {
  public static async login(ctx: Context) {
    const userRepository = getManager().getRepository(User);

    const user = await userRepository
      .createQueryBuilder()
      .where({ name: ctx.request.body.name })
      .addSelect('User.password')
      .getOne();

    if (!user) {
      ctx.status = 401;
      ctx.body = { message: '用户名不存在' };
    } else if (await argon2.verify(user.password, ctx.request.body.password)) {
      ctx.status = 200;
      ctx.body = { token: jwt.sign({ id: user.id }, JWT_SECRET) };
    } else {
      ctx.status = 401;
      ctx.body = { message: '密码错误' };
    }
  }

  // ...
}
```

在 `login` 中，我们首先根据用户名（请求体中的 `name` 字段）查询对应的用户，如果该用户不存在，则直接返回 401；存在的话再通过 `argon2.verify` 来验证请求体中的明文密码 `password` 是否和数据库中存储的加密密码是否一致，如果一致则通过 `jwt.sign` 签发 Token，如果不一致则还是返回 401。

这里的 Token 负载就是标识用户 ID 的对象 `{ id: user.id }` ，这样后面鉴权成功后就可以通过 `ctx.user.id` 来获取用户 ID。

### 在 User 控制器中添加访问控制

Token 的中间件和签发都搞定之后，最后一步就是在合适的地方校验用户的 Token，确认其是否有足够的权限。最典型的场景便是，在更新或删除用户时，我们要**确保是用户本人在操作**。打开 `src/controllers/user.ts` ，代码如下：

```
// src/controllers/user.ts
// ...

export default class UserController {
  // ...

  public static async updateUser(ctx: Context) {
    const userId = +ctx.params.id;

    if (userId !== +ctx.state.user.id) {
      ctx.status = 403;
      ctx.body = { message: '无权进行此操作' };
      return;
    }

    const userRepository = getManager().getRepository(User);
    await userRepository.update(userId, ctx.request.body);
    const updatedUser = await userRepository.findOne(userId);

    // ...
  }

  public static async deleteUser(ctx: Context) {
    const userId = +ctx.params.id;

    if (userId !== +ctx.state.user.id) {
      ctx.status = 403;
      ctx.body = { message: '无权进行此操作' };
      return;
    }

    const userRepository = getManager().getRepository(User);
    await userRepository.delete(userId);

    ctx.status = 204;
  }
}
```

两个 Controller 的鉴权逻辑基本相同，我们通过比较 `ctx.params.id` 和 `ctx.state.user.id` 是否相同，如果不相同则返回 403 Forbidden 错误，相同则继续执行相应的数据库操作。

代码写完之后，我们用刚才注册的一个用户信息去访问登录 API：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/67ac6f6341234418ad8745ab15f65070~tplv-k3u1fbpfcp-zoom-1.image)

成功地获取到了 JWT Token！然后我们复制获取到的 Token，在接下来测试受保护的路由时，我们需要添加一个 `Authorization` 头部，值为 `Bearer <JWT_TOKEN>` ，如下图所示：

![](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/d6e15a4fe5bd4672b16f1a18857dc259~tplv-k3u1fbpfcp-zoom-1.image)

然后就可以测试受保护的路由了！这里由于篇幅限制就省略了。

## 错误处理

最后，我们来简单地聊一下 Koa 中的错误处理。由于 Koa 采用了 async 函数和 Promise 作为异步编程的方案，所以错误处理自然也很简单了——直接用 JavaScript 自带的 try-catch 语法就可以轻松搞定。

### 实现自定义错误（异常）

首先，让我们来实现一些自定义的错误（或者异常，本文不作区分）类。创建 `src/exceptions.ts` ，代码如下：

```
// src/exceptions.ts
export class BaseException extends Error {
  // 状态码
  status: number;
  // 提示信息
  message: string;
}

export class NotFoundException extends BaseException {
  status = 404;

  constructor(msg?: string) {
    super();
    this.message = msg || '无此内容';
  }
}

export class UnauthorizedException extends BaseException {
  status = 401;

  constructor(msg?: string) {
    super();
    this.message = msg || '尚未登录';
  }
}

export class ForbiddenException extends BaseException {
  status = 403;

  constructor(msg?: string) {
    super();
    this.message = msg || '权限不足';
  }
}
```

这里的错误类型参考了 [Nest.js](https://link.juejin.cn?target=https%3A%2F%2Fdocs.nestjs.com%2Fexception-filters "https://docs.nestjs.com/exception-filters") 的设计。出于学习目的，这里作了简化，并且只实现了我们需要用到的错误。

### 在 Controller 中使用自定义错误

接着我们便可以在 Controller 中使用刚才的自定义错误了。打开 `src/controllers/auth.ts`，修改代码如下：

```
// src/controllers/auth.ts
// ...
import { UnauthorizedException } from '../exceptions';

export default class AuthController {
  public static async login(ctx: Context) {
    // ...

    if (!user) {
      throw new UnauthorizedException('用户名不存在');
    } else if (await argon2.verify(user.password, ctx.request.body.password)) {
      ctx.status = 200;
      ctx.body = { token: jwt.sign({ id: user.id }, JWT_SECRET) };
    } else {
      throw new UnauthorizedException('密码错误');
    }
  }

  // ...
}
```

可以看到，我们将直接手动设置状态码和响应体的代码改成了简单的错误抛出，代码清晰了很多。

> **提示**
>
> Koa 的 Context 对象提供了一个便捷方法 `throw` ，同样可以抛出异常，例如 `ctx.throw(400, 'Bad request')`。

同样地，修改 `UserController` 相关的逻辑。修改 `src/controllers/user.ts`，代码如下：

```
// src/controllers/user.ts
// ...
import { NotFoundException, ForbiddenException } from '../exceptions';

export default class UserController {
  // ...

  public static async showUserDetail(ctx: Context) {
    const userRepository = getManager().getRepository(User);
    const user = await userRepository.findOne(+ctx.params.id);

    if (user) {
      ctx.status = 200;
      ctx.body = user;
    } else {
      throw new NotFoundException();
    }
  }

  public static async updateUser(ctx: Context) {
    const userId = +ctx.params.id;

    if (userId !== +ctx.state.user.id) {
      throw new ForbiddenException();
    }

    // ...
  }
 // ...
  public static async deleteUser(ctx: Context) {
    const userId = +ctx.params.id;

    if (userId !== +ctx.state.user.id) {
      throw new ForbiddenException();
    }

    // ...
  }
}
```

### 添加错误处理中间件

最后，我们需要添加错误处理中间件来捕获在 Controller 中抛出的错误。打开 `src/server.ts` ，实现错误处理中间件，代码如下：

```
// src/server.ts
// ...

createConnection()
  .then(() => {
    // ...

    // 注册中间件
    app.use(logger());
    app.use(cors());
    app.use(bodyParser());

    app.use(async (ctx, next) => {
      try {
        await next();
      } catch (err) {
        // 只返回 JSON 格式的响应
        ctx.status = err.status || 500;
        ctx.body = { message: err.message };
      }
    });

    // ...
  })
  // ...
```

可以看到，在这个错误处理中间件中，我们把返回的响应数据转换成 JSON 格式（而不是之前的 Plain Text），这样看上去更统一一些。











