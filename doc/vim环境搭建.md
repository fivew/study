#基础
1. vim 有很多配置文件，~/.vimrc配置文件会覆盖/etc/vimrc配置

#常用快捷键
- %		跳转到配对的括号去
- [[	跳转到代码块的开头去(但要求代码块中'{'必须单独占一行)
- gD	跳转到局部变量的定义处
- ''	跳转到光标上次停靠的地方, 是两个', 而不是一个"
- mx	设置书签,x只能是a-z的26个字母
- `x	跳转到书签处("`"是1左边的键)
- >		增加缩进,"x>"表示增加以下x行的缩进
- <		减少缩进,"x<"表示减少以下x行的缩进

#ctags
产生函数，宏等符号的索引文件

## 使用
$ctags -R	#生产tags文件
:set tags=/home/wooin/vim71/tags   #制定使用的tags文件
:help usr_29    #帮助文档

## 快捷键
- "<C-]>"   跳转到函数定义
- "<C-T>"   返回


#Taglist
符号窗口，将代码的函数，变量等符号在窗口展示

## 使用
:help taglist.txt         #帮助文档

## 快捷键
