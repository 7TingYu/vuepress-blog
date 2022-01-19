---
title: sass 常用功能
date: 2022-01-19
tags:
 - sass
categories:
 - 小识书屋
---

## 变量

```scss
$font-stack: Helvetica, sans-serif;
$primary-color: #333;

body {
  font: 100% $font-stack;
  color: $primary-color;
}
```


## 嵌套

引用父级选择器"&"


```scss
// 无论CSS规则嵌套的深度怎样，关键字"&"都会使用父级选择器级联替换全部其出现的位置：

/*===== SCSS =====*/
#main {
  color: black;
  a {
    font-weight: bold;
    &:hover { color: red; }
  }
}

/*===== CSS =====*/
#main {
  color: black; }
  #main a {
    font-weight: bold; }
    #main a:hover {
      color: red; 
}

// "&"必须出现在复合选择器开头的位置，后面再连接自定义的后缀
/*===== SCSS =====*/
#main {
  color: black;
  &-sidebar { border: 1px solid; }
}

/*===== CSS =====*/
#main {
  color: black; }
  #main-sidebar {
    border: 1px solid; 
}

```


嵌套属性


```scss
/*===== SCSS =====*/
.demo {
  // 命令空间后带有冒号:
  font: {
    family: fantasy;
    size: 30em;
    weight: bold;
  }
}

/*===== CSS =====*/
.demo {
  font-family: fantasy;
  font-size: 30em;
  font-weight: bold; 
}
```

## 引入

```scss
// _reset.scss
html, body, ul, ol {
  margin:  0;
  padding: 0;
}

// base.scss
@import 'reset';
body {
  font: 100% Helvetica, sans-serif;
  background-color: #efefef;
}
```

## 混合

混合（Mixin）用来分组那些需要在页面中复用的CSS声明，开发人员可以通过向Mixin传递变量参数来让代码更加灵活，

该特性在添加浏览器兼容性前缀的时候非常有用，

SASS目前使用@mixin name指令来进行混合操作。

```scss
@mixin border-radius($radius) {
    border-radius: $radius;
    -ms-border-radius: $radius;
    -moz-border-radius: $radius;
    -webkit-border-radius: $radius;
}

.box {
    @include border-radius(10px);
}
```


## 继承

```scss
// 这段代码不会被输出到最终生成的CSS文件，因为它没有被任何代码所继承。
%other-styles {
  display: flex;
  flex-wrap: wrap;
}

// 下面代码会正常输出到生成的CSS文件，因为它被其接下来的代码所继承。
%message-common {
  border: 1px solid #ccc;
  padding: 10px;
  color: #333;
}

.message {
  @extend %message-common;
}

.success {
  @extend %message-common;
  border-color: green;
}

.error {
  @extend %message-common;
  border-color: red;
}

.warning {
  @extend %message-common;
  border-color: yellow;
}
```

## 算术运算符


```scss
.container { width: 100%; }

article[role="main"] {
  float: left;
  width: 600px / 960px * 100%;
}

aside[role="complementary"] {
  float: right;
  width: 300px / 960px * 100%;
}
```




