---
title: vue next - 村长源码共读会 patch 根组件到首次渲染dom
date: 2022-3-8
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
- componentUpdateFn -- packages\runtime-core\src\renderer.ts
  - patch
  - processElement()
  - mountElement()
  - hostCreateElement()
  - hostInsert()
  - mountChildren()


![](https://i.niupic.com/images/2022/03/07/9W5c.jpg)

## 思考




