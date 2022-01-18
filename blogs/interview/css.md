---
title: interview css
date: 2022-01-16
tags:
 - interview
categories:
 - interview
---

## css

#### 防止高度坍塌：4种

- 父元素 overflow: hidden;
- 结尾子元素 clear: both;
- 父元素浮动 float: left;
  - 解决: 父元素之后的 平级元素增加 clear: both;
- 完美解决: 父元素末尾伪元素设置 clear: both;



### BFC(block formatting context)

> - 独立渲染区域
> - 外部不影响内部
> - 内部不影响外部

块级格式化上下文

**4种情况会形成BFC渲染区域**

- float的值不是none
- position的值不是static或者relaative。
- display的值是inline-block、table-cell、flex、table-capttion或者inline-flex
- overflow的值不是visible



**解决问题**

- 高度坍塌
- 垂直方向上高度合并
- 垂直方向上的margin溢出
- 左定宽,右自适应
  - 左浮动,右overflow:hidden;



### IFC(inline formatting context)

> display: inline | inline-block | inline-flex



### 垂直方向上的margin溢出

- 父元素overflow:hidden;
- 父元素第一个子元素添加空<table>
- 父元素 padding 代替子元素 margin
- 父元素透明上边框
- 父元素::before{content:"";display:table}



### flex

- flex-direction 主轴及其排列方向
- flex-wrap 是否换行
- justify-content 主轴上的对齐方式
- align-items 交叉轴的统一对齐



### 居中的方法总结

> 父元素必须是块级格子容器
>
> 父元素宽度必须已经被设定好

#### 水平居中

块级居中

- margin: 0 auto;
- 父相子绝
  - left：50%;
  - margin-left：-子宽一半; or transform: translateX(-50%);
- display: flex; flex-direction: row; justify-content: center;

行内居中

- text-align: center;

#### 垂直居中

块级居中

- 父相子绝
  - top：50%;
  - margin-top：-子宽一半; or transform: translateY(-50%);
- display: flex; flex-direction: row; align-items: center;

行内居中

- 单行文字 line-height: heigth;
- 多行文字: 
  - 父元素 display: inline | inline-block | table-cell;
  - vertical-align: middle;

### 移动端适配 -- 5种

> - 设备的物理像素 pt --- 屏幕宽/分辨率
> - css 像素 px 
>   - 1px ~ 0.76pt
>   - 手机屏幕 1px ~ 2pt
> - rem 
> - em
> - rpx
>   - 1rpx = 0.5px = 1pt
> - vw/vh
> - %

```html
<meta name="viewport" content="" />
```



- flex
- 父相子绝
- grid
- float
- rem

