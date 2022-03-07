---
title: vue next - 村长源码共读会 打包脚本解析
date: 2022-3-7
tags:
 - vue
categories:
 - vue
---



## 学习方法

**单步调试**

**提出问题**

**package.json 分析入口**

**利用调用栈（call stack）**

**搜索方法 ctrl + t**

## package.json

package.json

```json
{"dev": "node scripts/dev.js"}
```

scripts\dev.js

这里我看到的版本与原先的rollup不同，新dev改用exbuild打包


在这里做简单的导图

- scripts/dev.js
- rollup.config.js
  - packages 目录
  - 打包格式
    - cjs
    - es
    - iife
  - entryFile
    - packages/vue/src/index.ts
- 入口文件的作用

## 整体流程

- createApp -- packages\runtime-dom\src\index.ts
- createRenderer -- packages\runtime-core\src\renderer.ts
- createAppApi -- packages\runtime-core\src\apiCreateApp.ts
- mount -- packages\runtime-core\src\apiCreateApp.ts
- render -- packages\runtime-core\src\renderer.ts
- patch -- packages\runtime-core\src\renderer.ts
- processComponent -- packages\runtime-core\src\renderer.ts
- mountComponent -- packages\runtime-core\src\renderer.ts
- setupComponent -- packages\runtime-core\src\renderer.ts
- setupStatefulComponent -- packages\runtime-core\src\component.ts
- setup -- packages\runtime-core\src\component.ts
- handleSetupResult -- packages\runtime-core\src\component.ts
- finishComponentSetup -- packages\runtime-core\src\component.ts
  - instance.render
  - applyOptions
- setupRenderEffect -- packages\runtime-core\src\renderer.ts
  - componentUpdateFn
  - new ReactiveEffect
  - update()


## 课后问题

### 入口文件的作用

声明了 compileToFunction 
输出依赖包


### compileToFunction 何时调用

结束组件安装时


### 组件挂载（mountComponent）都做了什么事

- 挂载只执行一次
- 初始化
  - 看到第一次渲染结果
- 建立更新机制






