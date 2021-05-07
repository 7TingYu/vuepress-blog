#!/usr/bin/env sh

# 确保脚本抛出遇到的错误
set -e

# 生成静态文件
npm run build

# 进入生成的文件夹
# cd public

git init
git add .
git commit -m 'deploy'

# 如果发布到 https://<USERNAME>.github.io  填写你刚刚创建的仓库地址
# git remote add origin https://github.com/7tingyu/blog—templete.git

# git push -f git@github.com:7tingyu/7tingyu.github.io.git master:master

git push -f git@gitee.com:yu7/yu7.git master:master

cd ..

# tcb hosting:deploy public -e blog-9g8lgnuke4603ff9
