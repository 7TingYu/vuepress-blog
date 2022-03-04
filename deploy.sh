#!/usr/bin/env sh

# 确保脚本抛出遇到的错误
set -e

# 生成静态文件
npm run build

# 进入生成的文件夹
cd ./dist

git init
git add .
git commit -m 'deploy'
# git remote -v

# 如果发布到 https://<USERNAME>.github.io  填写你刚刚创建的仓库地址
# git remote add gitee git@gitee.com:yu7/yu7.git
git remote add github git@github.com:7TingYu/7tingyu.github.io.git
git remote -v

# git push -f git@github.com:7TingYu/7TingYu.git master:master
# git push -f git@gitee.com:yu7/yu7.git master:master

# git push -f gitee master:master
git push -f github master:master

cd ..

# tcb hosting:deploy public -e blog-9g8lgnuke4603ff9
