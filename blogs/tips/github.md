---
title: Git github
date: 2021-04-03
tags:
 - git
categories:
 - 小识书屋
---


最近发现 github ssh 链接失败了

解决ssh: connect to host github.com port 22: Connection refused

## 配置 ssh key

检查是否已存在秘钥

```shell
cd ~/. ssh
```

如果提示 `No such file or directory` 则尚未使用过ssh

```shell
# 生成ssh
ssh-keygen -t rsa -C "邮件地址"
```

并且连续3次回车，最终会生成一个文件，找到ssh\id_rsa.pub文件，打开并复制里面的内容。然后打开你的github主页，进入个人设置 -> SSH and GPG keys -> New SSH key

## 检测 ssh 连接

检测是否配置成功

```shell
# ssh 连接 git@github.com
ssh -T git@github.com
```

`ssh: connect to host github.com Port : 22 Connection refused`

看到这个，恭喜，连接失败了

在 `~/.ssh` 目录中新增 config 文件

```shell
touch config
# sudo touch config
```

修改 config 中的信息

```
Host github.com
// 注册 github.com 的邮箱
User xxxxx@xx.com
Hostname ssh.github.com  
PreferredAuthentications publickey  
IdentityFile ~/.ssh/id_rsa  
Port 443
```

到这一步就完成了






