---
title: vue next - 村长源码共读会 dom 和组件属性初始化过程
date: 2022-3-9
tags:
 - vue
categories:
 - vue
---


## 思考

### dom 从何而来

### 节点如何初始化

1. dom

- attrs style class ...
- props.ts
  - patchProp


2. 组件

- attrs props
  - setupComponent
  - initPorps


### diff 更新流程

- setupRenderEffect
- componentUpdateFn
- patch
  - processFragment
    - patchBlockChildren
    - patch
    - patchElement


