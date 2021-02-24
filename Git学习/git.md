# Git

## Git本地仓库
1. 创建一个文件夹，再git init会出现.git的文件夹
2. cd + 文件夹名会进入文件夹
3. touch + 文件名 创建文件
4. git status 查看文件状态        工作区-> 暂存区 -> 仓库
5. git add 文件名 把文件添加到暂存区
   再git commit -m '此处添加描述'  把文件提交到仓库
6. vi 文件名  修改文件
   按i切入到文本输入模式
   按esc切换到命令行输出模式  输入:wq完成修改
7. cat 文件名 查看文件内容
8. git add 文件名 将文件添加进暂存区 git commit -m '  ' 提交文件进入仓库
9. rm -rf 文件名   删除文件
   git rm 文件名
   git commit -m ' ' 提交删除

## Git远程仓库
1. git clone + 远程仓库地址  将Github上的仓库克隆到本地，然后将本地上的仓库进行修改
2. 待本地仓库处理完成之后 git push便可同步到远程仓库（Github）

