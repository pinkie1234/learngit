git is a distributed version control system.
git is free software distributed under the GPL.
git has a mutable index calle stage.
git tracks changes of files.
creating a branch is quick and simple


分支：
查看分支：git branch

创建分支：git branch <name>

切换分支：git checkout <name>

创建+切换分支：git checkout -b <name>

合并某分支到当前分支：git merge <name>

git stash

删除分支：
git branch -d <name>

查看分支合并情况:
git log --garph

快速合并：
git merge

普通合并：
git merge --no-ff -m "" <name>


多人协作：
丢弃一个没有被合并过的分支，可以通过
git branch -D <name>强行删除

查看远程库信息，使用git remote -v；

本地新建的分支如果不推送到远程，对其他人就是不可见的；

从本地推送分支，使用git push origin branch-name，如果推送失败，先用git pull抓取远程的新提交；

在本地创建和远程分支对应的分支，使用git checkout -b branch-name origin/branch-name，本地和远程分支的名称最好一致；

建立本地分支和远程分支的关联，使用git branch --set-upstream branch-name origin/branch-name；

从远程抓取分支，使用git pull，如果有冲突，要先处理冲突


