---
title: 简洁工具类
date: 2022-05-06
tags:
 - js utils
categories:
 - 小识书屋
---


## 滑动懒加载


```js
const handleScroll = (e) => {
    let { clientHeight, scrollHeight, scrollTop } = e.target;
    console.log(clientHeight, scrollHeight, scrollTop);
    if (clientHeight + scrollTop + 200 === scrollHeight ) {
        // todo something....
    }
}
```

## 下载文件

### 通过文件地址直接下载

```html
<a href="http://localhost:5000/test.xlsx" download>点击下载</a>
```



### 二进制流文件下载

```js
const Upload = () => {
    const handleDownload = () => {  
        axios({  
            method: 'post',  
            url: "http://localhost:3000/download",  
            data: {    
                test: "test data"  
            },  
            responseType: "arraybuffer" // arraybuffer是js中提供处理二进制的接口
        })
        .then(response => {          
            // 用返回二进制数据创建一个Blob实例          
            let blob = new Blob([response.data], {            
                type: response.mineType, 
            }) // for .xlsx files          

            // 通过URL.createObjectURL生成文件路径          
            let url = window.URL.createObjectURL(blob)          

            // 创建a标签          
            let ele = document.createElement("a")          
            ele.style.display = 'none'          

            // 设置href属性为文件路径，download属性可以设置文件名称          
            ele.href = url          
            ele.download = "测试文件"          

            // 将a标签添加到页面并模拟点击          
            document.querySelectorAll("body")[0].appendChild(ele)          
            ele.click()          

            // 移除a标签          
            ele.remove()        
        });
    }

    return (<input type="button" value="点击下载" onClick="handleDownload">)
}
```


### 拓展

```js
var mimeTypeArr = {
    img: [ 'image/png', 'image/jpeg', 'image/bmp', 'image/jpeg', 'image/gif' ],
    excel: [ 'application/vnd.ms-excel', 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' ],
    ppt: [
        'application/vnd.ms-powerpoint',
        'application/vnd.openxmlformats-officedocument.presentationml.presentation'
    ],
    word: [ 'application/msword', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document' ],
    text: [],
    pdf: [ 'application/pdf' ],
    ZIPRAR: [ 'application/x-zip-compressed', 'application/zip', 'application/x-rar-compressed' ],
    video: [ 'video/mp4', 'video/mpeg', 'video/x-m4v', 'video/quicktime', 'video/x-msvideo' ],
    audio: [
        'audio/x-mpeg',
        'audio/x-mpeg',
        'audio/x-mpegurl',
        'audio/mp4a-latm',
        'audio/mp4a-latm',
        'audio/mp4a-latm',
        'audio/x-ms-wma',
        'audio/x-ms-wmv',
        'audio/x-pn-realaudio',
        'audio/x-wav',
        'audio/mpeg',
        'audio/ogg',
        'audio/wav'
    ],
    html: [ 'text/html', 'text/plain', 'application/octet-stream' ],
    other: [ '*/*', 'text/plain', 'application/x-msdownload' ],
};
```

## 复制

### 图片 

#### 使用getSelection + execCommand api复制图片

```html
<img id="testImg" src="./img/test.jpg" alt="img">
<button id="btn">copy</button>
```

```js
const testImg = document.querySelector("#testImg");
const btn = document.querySelector("#btn");

function handleCopyImg() {  
    const selection = window.getSelection();  
    // 清除选中  
    if (selection.rangeCount > 0) selection.removeAllRanges();  
    // https://developer.mozilla.org/zh-CN/docs/Web/API/Document/queryCommandSupported  
    if(!document.queryCommandSupported('copy')) return alert('浏览器暂不支持复制命令');  
    // 创建range区域  
    const range = document.createRange();   
    range.selectNode(testImg);  
    selection.addRange(range);  
    document.execCommand("copy");  
    selection.removeAllRanges();
}

btn.addEventListener("click", handleCopyImg, false);
```

> 经过实际测验，发现点击按钮复制后，word文档、微信聊天输入框、QQ聊天输入框中都可以正常粘贴复制的图片，但在钉钉聊天输入框中进行粘贴没有任何反应。

#### navigator.clipboard实现复制图片

```html
<img id="testImg" src="./img/test.jpg" alt="img">
<button id="btn">copy</button>
```

```js
const testImg = document.querySelector("#testImg");
const btn = document.querySelector("#btn");

function handleCopyImg() {  
    const canvas = document.createElement('canvas');  
    const ctx = canvas.getContext('2d');  
    const img = new Image();  
    canvas.width = testImg.width;  
    canvas.height = testImg.height;  
    img.crossOrigin = "Anonymous";  
    img.src = testImg.src;    
    img.onload = () => {    
        ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);    
        ctx.drawImage(img, 0, 0);    
        // 将canvas转为blob    
        canvas.toBlob(async blob => {      
            console.log(blob);      
            const data = [        
                new ClipboardItem({          
                    [blob.type]: blob,        
                    }),      
                ];      
                // https://w3c.github.io/clipboard-apis/#dom-clipboard-write      
                await navigator.clipboard.write(data)        
                    .then(          
                        () => {            
                            console.log("Copied to clipboard successfully!");          
                        },          
                        () => {            
                            console.error("Unable to write to clipboard.");          
                        }        
                    );      
        }); 
    }
}
            
btn.addEventListener("click", handleCopyImg, false);
```

> 经过实际测验，在微信、QQ、钉钉聊天输入框均可以粘贴图片，唯一的缺点是低版本浏览器不支持(IE完全不支持)。


## 获取日历

```js
// 在 js 中，0 是周日，0 ~ 6 代表周一至周日
const WEEKDAYS = [0, 1, 2, 3, 4, 5, 6]

// 一周只有7天，不会有第8天，所以只要拷贝一次就可以了
const DOUBLE_WEEKDAYS = WEEKDAYS.concat(WEEKDAYS)

/**
 * 获取获得一周7天的数字
 *
 * @param firstWeekDay 周开始时间
 *
 * @return 周数组
 */
function getWeekdays(firstWeekDay = 0) {
  if (firstWeekDay === 0) return WEEKDAYS
  return DOUBLE_WEEKDAYS.slice(firstWeekDay % 14, (firstWeekDay + 7) % 14)
}
// 简体中文
const zh = {
  // 完整名称 
  weekdays: ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'],
  // 短名称
  weekdaysShort: ['周日', '周一', '周二', '周三', '周四', '周五', '周六'],
  // 缩写
  weekdaysAbbr: ['日', '一', '二', '三', '四', '五', '六']
}

// 英文
const en = {
  // 完整名称 
  weekdays: ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'],
  // 短名称
  weekdaysShort: ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'],
  // 缩写
  weekdaysAbbr: ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat']
}

/**
 * 获取一星期的名称列表
 *
 * @param {Number[]}  weekdays 一周7天的数字
 *
 * @param {Object[]}
 */
function getWeekHead(weekdays, locale) {
  return weekdays.map(day => ({
    name: locale.weekdays[day],
    short: locale.weekdaysShort[day],
    abbr: locale.weekdaysAbbr[day],
    day: day
  }))
}

/**
 * 获取月份日历
 *
 * @param {*} year  年
 * @param {*} month 月
 * @param {Object} options
 * @param {Number[]} options.weekdays     一周7天的数组
 * @param {Number} [options.firstWeekDay=0]      周开始时间
 * @param {Number} [options.visibleWeeksCount=6] 单个日历上显示的周数量
 */
function getMonthCalendar(year, month, options) {
  const weekdays = options.weekdays
  const cursor = new Date(year, month - 1, 1, 0, 0, 0, 0)

  const count = (options.visibleWeeksCount || 6) * 7

  // 让时间定位在周开始的时间
  cursor.setDate(cursor.getDate() - weekdays.indexOf(cursor.getDay()))

  const calendar = []

  let week = []
  for (let i = 0; i < count; i++) {
    if (!(i % 7)) {
      week = calendar[i / 7] = []
    }

    week.push(
      // 拷贝时间
      new Date(cursor)
    )

    cursor.setDate(cursor.getDate() + 1)
  }

  return calendar
}

function format(d) {
  return `${d.getFullYear()}-${(d.getMonth() + 1).toString().padStart(2, 0)}-${d.getDate().toString().padStart(2, 0)}`
}

/**
 * 获取月份日历
 *
 * @param {*} year  年
 * @param {*} month 月
 * @param {*} start 开始时的星期 0 日， 1 周一
 */
function getMonth(year, month, start = 0) {
  return getMonthCalendar(year, month, {weekdays: getWeekdays(start)})
}

```


## 一些工具库收藏

- [any-touch](https://github.com/any86/any-touch) 一个关于手势的工具库
- [numeral](http://numeraljs.com/) 数字处理工具
- [moment.js](http://momentjs.cn/) 时间工具库
- [day.js](https://dayjs.fenxianglu.cn/) 时间工具库，与 moment 的区别在于， day 是借鉴于 moment 二次开发，api保持一致，但更轻，个人喜欢看着 moment 文档写 day
- [qs](https://github.com/ljharb/qs) 轻量的 url 参数转换，api 请求时离不开它
- [js-cookie](https://github.com/js-cookie/js-cookie) 简单的、轻量的处理 cookies 的 js API
- [vConsole](https://github.com/Tencent/vConsole/blob/dev/README_CN.md) 轻量、可拓展、针对手机网页的前端开发者调试面板。
- [Animate.css](https://animate.style/) 简易的 css 动画库
- [lodash.js](https://www.lodashjs.com/) 一致性、模块化、高性能的 JavaScript 实用工具库，虽然基本都是使用深拷贝
- [clipboard.js](https://github.com/zenorocha/clipboard.js) 将文本复制到剪贴板的 JS 库。

### webpack

- [purifycss](https://github.com/purifycss/purifycss) 可以帮助你移除没使用到的 css(Webpack)


