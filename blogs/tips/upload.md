---
title: 下载
date: 2022-04-24
tags:
 - js utils
categories:
 - 小识书屋
---


## 通过文件地址直接下载

```html
<a href="http://localhost:5000/test.xlsx" download>点击下载</a>
```



## 二进制流文件下载

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


## 拓展

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











