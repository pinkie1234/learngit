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

丢弃一个没有被合并过的分支，可以通过
git branch -D <name>强行删除


