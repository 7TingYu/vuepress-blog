---
title: node 基础api
date: 2022-03-1
tags:
 - node
categories:
 - node
---


## http

http 模块可以很方便的为我们启动一个服务，一个最简单的 http

创建 01_http.js

```js
// 1. 引入 http 模块
var http = require("http");

// 2. 用 http 模块创建服务
/**
 * req 获取 url 信息 (request)
 * res 浏览器返回响应信息 (response)
 */
http.createServer(function (req, res) {
  // 设置 HTTP 头部，状态码是 200，文件类型是 html，字符集是 utf8
  res.writeHead(200, {
    "Content-Type": "text/html;charset=UTF-8"
  });

  // 往页面打印值
  res.write('<h1 style="text-align:center">Hello NodeJS</h1>');

  // 结束响应
  res.end();

}).listen(3000); // 监听的端口
```

是不是很简单，然后只需要让它跑起来就好了

```sh
node 01_http.js
```


## url

URL 模块是什么呢？在我的理解中是一个用于描述 url 的对象

创建 02_url.js

```js
// 1. 引入 url 模块
var url = require("url");

// 2. 引入 http 模块
var http = require("http");

// 3. 用 http 模块创建服务
/**
 * req 获取 url 信息 (request)
 * res 浏览器返回响应信息 (response)
 */
http.createServer(function (req, res) {

  // 4. 获取服务器请求
  /**
   * 访问地址是：http://localhost:3000/?userName=jsliang&userAge=23
   * 如果你执行 console.log(req.url)，它将执行两次，分别返回下面的信息：
   * /  ?userName=jsliang&userAge=23
   * /  /favicon.ico
   * 这里为了防止重复执行，所以排除 req.url == /favicon.ico 的情况
   */
  if(req.url != "/favicon.ico") {
    
    // 5. 使用 url 的 parse 方法
    /**
     * parse 方法需要两个参数：
     * 第一个参数是地址
     * 第二个参数是 true 的话表示把 get 传值转换成对象
     */ 
    var result = url.parse(req.url, true);
    console.log(result);
    /**
     * Url {
     *   protocol: null,
     *   slashes: null,
     *   auth: null,
     *   host: null,
     *   port: null,
     *   hostname: null,
     *   hash: null,
     *   search: '?userName=jsliang&userAge=23',
     *   query: { userName: 'jsliang', userAge: '23' },
     *   pathname: '/',
     *   path: '/?userName=jsliang&userAge=23',
     *   href: '/?userName=jsliang&userAge=23' }
     */

    console.log(result.query.userName); // jsliang

    console.log(result.query.userAge); // 23
  }

  // 设置 HTTP 头部，状态码是 200，文件类型是 html，字符集是 utf8
  res.writeHead(200, {
    "Content-Type": "text/html;charset=UTF-8"
  });

  // 往页面打印值
  res.write('<h1 style="text-align:center">Hello NodeJS</h1>');

  // 结束响应
  res.end();

}).listen(3000);
```

老规矩，让我们，跑起来！

```sh
node 02_url.js
```

在控制台中我们可以看到这个结构

> ```sh
> Url {
>  protocol: null,
>  slashes: null,
>  auth: null,
>  host: null,
>  port: null,
>  hostname: null,
>  hash: null,
>  search: '?userName=jsliang&userAge=23',
>  query: [Object: null prototype] { userName: 'jsliang', userAge: '23' },
>  pathname: '/',
>  path: '/?userName=jsliang&userAge=23',
>  href: '/?userName=jsliang&userAge=23'
>}
>jsliang
>23
> ```

让我们深入了解下

```js
console.log(url);

/**
 * Console：
 { 
   Url: [Function: Url],
    parse: [Function: urlParse], // 获取地址信息
    resolve: [Function: urlResolve], // 追加或者替换地址
    resolveObject: [Function: urlResolveObject],
    format: [Function: urlFormat], // 逆向 parse，根据地址信息获取原 url 信息
    URL: [Function: URL],
    URLSearchParams: [Function: URLSearchParams],
    domainToASCII: [Function: domainToASCII],
    domainToUnicode: [Function: domainToUnicode] 
  }
 */
```

## CommonJS


CommonJS 就是为 JS 的表现来制定规范，因为 JS 没有模块系统、标准库较少、缺乏包管理工具，所以 CommonJS 应运而生，它希望 JS 可以在任何地方运行，而不只是在浏览器中，从而达到 Java、C#、PHP 这些后端语言具备开发大型应用的能力。

CommonJS 的应用:

- 服务器端 JavaScript 应用程序。（Node.js）
- 命令行工具
- 桌面图形界面应用程序。


### 项目中使用


创建 03_CommonJS.js、03_tool-sum.js

```js
// 1. 假设我们文件其中有个工具模块
var tools = {
  sum: (...num) => num.reduce((pre, next) => pre + next, 0)
}

/**
 * 2. 暴露模块
 * exports.str = str;
 * module.exports = str;
 * 区别：
 * module.exports 是真正的接口
 * exports 是一个辅助工具
 * 如果 module.exports 为空，那么所有的 exports 收集到的属性和方法，都赋值给了 module.exports
 * 如果 module.exports 具有任何属性和方法，则 exports 会被忽略
 */

// exports 使用方法
// var str = "jsliang is very good!";
// exports.str = str; // { str: 'jsliang is very good!' }

// module.exports 使用方法
module.exports = tools;
```

在 03_CommonJS.js 引用

```js
var http = require("http");

var tools1 = require('./03_tool-sum');

http.createServer(function (req, res) {
  res.writeHead(200, {
    "Content-Type": "text/html;charset=UTF-8"
  });

  res.write('<h1 style="text-align:center">Hello NodeJS</h1>');
  
  console.log(tools1.sum(1, 2, 3));
  /**
   * Console：
   * 6
   * 6
   * 这里要记得 Node 运行过程中，它请求了两次，
   * http://localhost:3000/ 为一次，
   * http://localhost:3000/favicon.ico 为第二次
   */
  res.end();
}).listen(3000);
```


### node_modules 中使用

我们在 node_modules 中新建一个 03_tool-module-sum.js


```js
var tools = {
  sum: (...num) => num.reduce((pre, next) => pre + next, 0)
}

module.exports = tools;
```

在 03_CommonJS.js 引用

```js
// 如果 Node 在当前目录没找到 tool.js 文件，则会去 node_modules 里面去查找
var tools2 = require('03_tool-module-sum.js');

console.log(tools2.sum(1, 2, 3, 4));
```


如果全部单个文件丢在 node_modules 上，它会显得杂乱无章，这时候我们可以定义个自己的工具集：yu-utils，然后将我们的 tools.js 存放在该目录中：

然后在 node_modules\yu-utils 下初始化信息

```sh
npm init --yes
```
 
我们在 03_CommonJS.js 就可以引用它了：

```js
var http = require("http");

var tools1 = require('./03_tool-sum');

// 如果 Node 在当前目录没找到 tool.js 文件，则会去 node_modules 里面去查找
var tools2 = require('03_tool-module-sum');

/**
 * 通过 package.json 来引用文件
 * 1. 通过在 jsliang-module 中 npm init --yes 来生成 package.json 文件
 * 2. package.json 文件中告诉了程序入口文件为 ："main": "tools.js",
 * 3. Node 通过 require 查找 jsliang-module，发现它有个 package.json
 * 4. Node 执行 tools.js 文件
 */
var tools3 = require('yu-utils');

http.createServer(function (req, res) {

  res.writeHead(200, {
    "Content-Type": "text/html;charset=UTF-8"
  });

  res.write('<h1 style="text-align:center">Hello NodeJS</h1>');
  
  console.log(tools1.sum(1, 2, 3));
  console.log(tools2.sum(1, 2, 3, 4));
  console.log(tools3.sum(4, 5, 6));
  /**
   * Console：
   * 6
   * 24
   * 15
   * 6
   * 24
   * 15
   * 这里要记得 Node 运行过程中，它请求了两次，
   * http://localhost:3000/ 为一次，
   * http://localhost:3000/favicon.ico 为第二次
   */
  
  res.end();

}).listen(3000);

```

## fs 文件管理

fs 基础命令

- fs.stat 检测是文件还是目录
- fs.mkdir 创建目录
- fs.writeFile 创建写入文件
- fs.appendFile 追加文件
- fs.readFile 读取文件
- fs.readdir 读取目录
- fs.rename 重命名
- fs.rmdir 删除目录
- fs.unlink 删除文件

创建我们需要用到的工具文件 05_fs.js、index.js

### fs.stat 查询文件的基本信息

05_fs.js

```js
//  1. fs.stat
let fs = require('fs');
fs.stat('index.js', (error, stats) => {
  if(error) {
    console.log(error);
    return false;
  } else {
    console.log(stats);
    /**
     * Console：
     * Stats {
     *  dev: 886875,
     *  mode: 33206,
     *  nlink: 1,
     *  uid: 0,
     *  gid: 0,
     *  rdev: 0,
     *  blksize: undefined,
     *  ino: 844424931461390,
     *  size: 284,
     *  blocks: undefined,
     *  atimeMs: 1542847157494,
     *  mtimeMs: 1543887546361.2158,
     *  ctimeMs: 1543887546361.2158,
     *  birthtimeMs: 1542847157493.663,
     *  atime: 2018-11-22T00:39:17.494Z,
     *  mtime: 2018-12-04T01:39:06.361Z,
     *  ctime: 2018-12-04T01:39:06.361Z,
     *  birthtime: 2018-11-22T00:39:17.494Z }
     */

    console.log(`文件：${stats.isFile()}`); 
    // Console：文件：true
    
    console.log(`目录：${stats.isDirectory()}`); 
    // Console：目录：false

    return false;
  }
})
```


### fs.mkdir 创建目录


05_fs.js

```js
//  2. fs.mkdir
let fs = require('fs');

/**
 * 接收参数
 * path - 将创建的目录路径
 * mode - 目录权限（读写权限），默认 0777
 * callback - 回调，传递异常参数 err
 */
fs.mkdir('assets', (err) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("创建目录成功！");
    // Console：创建目录成功！
  }
})
```


### fs.rmdir 删除目录

05_fs.js

```js
//  8. fs.rmdir
let fs = require('fs');

/**
 * 接收参数
 * path - 将创建的目录路径
 * mode - 目录权限（读写权限），默认 0777
 * callback - 回调，传递异常参数 err
 */
fs.rmdir('assets', (err) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("创建目录成功！");
    // Console：创建目录成功！
  }
})
```


### fs.writeFile 写入文件

05_fs.js

```js
//  3. fs.writeFile
let fs = require('fs');

/**
 * filename (String) 文件名称
 * data (String | Buffer) 将要写入的内容，可以是字符串或者 buffer 数据。
 * · encoding (String) 可选。默认 'utf-8'，当 data 是 buffer 时，该值应该为 ignored。
 * · mode (Number) 文件读写权限，默认 438。
 * · flag (String) 默认值 'w'。
 * callback { Function } 回调，传递一个异常参数 err。
 */
fs.writeFile('index.js', 'Hello jsliang', (err) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log('写入成功！');
  }
})
```

### fs.appendFile 追加内容

05_fs.js

```js
//  4. fs.appendFile
let fs = require('fs');

fs.appendFile('index.js', '这段文本是要追加的内容', (err) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("追加成功");
  }
})
```

### fs.readFile 读取文件

05_fs.js

```js
let fs = require('fs');

// 6. fs.readdir 读取目录
fs.readdir('node_modules', (err, data) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("读取目录成功！");
    console.log(data);
    // Console：
    // 读取目录成功！
    // [ '03_tool-multiply.js', 'jsliang-module' ]
  }
})

```

### fs.readdir 读取目录

05_fs.js

```js
let fs = require('fs');

// 6. fs.readdir 读取目录
fs.readdir('node_modules', (err, data) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("读取目录成功！");
    console.log(data);
    // Console：
    // 读取目录成功！
    // [ '03_tool-multiply.js', 'jsliang-module' ]
  }
})
```

### fs.rename 重命名

05_fs.js

```js
let fs = require('fs');

// 7. fs.rename 重命名
fs.rename('index.js', 'jsliang.js', (err) => {
  if(err) {
    console.log(err);
    return false;
  } else {
    console.log("重命名成功！");
  }
})
```

## fs 流


```js
// 新建 fs
const fs = require('fs');
// 流的方式读取文件
let fileReadStream = fs.createReadStream('index.js');
// 读取次数
let count = 0;
// 保存数据
let str = '';
// 开始读取
fileReadStream.on('data', (chunk) => {
  console.log(`${++count} 接收到：${chunk.length}`);
  // Console：1 接收到：30
  str += chunk;
})
// 读取完成
fileReadStream.on('end', () => {
  console.log("——结束——");
  console.log(count);
  console.log(str);

  // Console：——结束——
  // 1
  // console.log("Hello World！");
})
// 读取失败
fileReadStream.on('error', (error) => {
  console.log(error);
})



let data = 'console.log("Hello World! 我要存入数据！")';

// 创建一个可以写入的流，写入到文件 index.js 中
let writeStream = fs.createWriteStream('index.js');
// 开始写入
writeStream.write(data, 'utf8');
// 写入完成
writeStream.end();
writeStream.on('finish', () => {
  console.log('写入完成！');
  // Console：写入完成
});
```


## get / post

```js
// 加载 http 模块
var http = require('http');

// 虚拟 SQL 读取出来的数据
var items = [];

// 创建 http 服务
http.createServer(function (req, res) {
  
  // 设置跨域的域名，* 代表允许任意域名跨域
  res.setHeader('Access-Control-Allow-Origin', '*');
  // 设置 header 类型
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
  // 跨域允许的请求方式
  res.setHeader('Content-Type', 'application/json');

  // 判断请求
  switch (req.method) {
    
    // post 请求时，浏览器会先发一次 options 请求，如果请求通过，则继续发送正式的 post 请求
    case 'OPTIONS':
      res.statusCode = 200;
      res.end();
      break;
    
      // 如果是 get 请求，则直接返回 items 数组
    case 'GET':
      let data = JSON.stringify(items);
      res.write(data);
      res.end();
      break;
      
    // 如果是 post 请求
    case 'POST':
      let item = '';
      // 读取每次发送的数据
      req.on('data', function (chunk) {
        item += chunk;
      });
      // 数据发送完成
      req.on('end', function () {
        // 存入
        item = JSON.parse(item);
        items.push(item.item);
        // 将数据返回到客户端
        let data = JSON.stringify(items);
        res.write(data);
        res.end();
      });
      break;
  }
}).listen(3000)

console.log('http server is start...');
```



