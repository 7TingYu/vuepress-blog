---
title: react 问题集合
date: 2022-05-13
tags:
 - react
categories:
 - react
---

## antd+react Table 组件不刷新

原因：table 组件只有在 rowKey 属性更新时才会进行刷新

解决：当页面较少时更新 rowKey 值便可


## antd-react form 赋值

通过 initialValues 设置初始值

通过 form.current.setFieldsValue 动态赋值


## antd-react form switch 动态赋值

在 \<Form.item /> 标签上加上 valuePropName="checked"

```js
<Form.item name="switch" valuePropName="checked" />
```