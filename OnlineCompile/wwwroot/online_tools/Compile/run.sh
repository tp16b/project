#########################################################################
# File Name: run.sh
# Author: tp
# Created Time: 2018年08月17日 星期五 13时24分46秒
#########################################################################
#!/bin/bash

SRCPATH=/home/tp/project/OnlineCompile/wwwroot/online_tools/Compile 

$SRCPATH/loadcodefile         #执行,则从浏览器中导入用户编辑的代码文件

codefile=`ls -t1 $SRCPATH/file | head -1` 

echo "<!DOCTYPE html>"
echo "<html>" 
echo "<meta charset=\"UTF-8\" http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>"  
echo "<body bgcolor=\" #d0d0d0\">" 

echo "<h1>The result: </h1>"
echo "<p>"

if [ "X$codefile" == "Xedit.c" ];then
	echo "暂时还不支持..."
elif [ "X$codefile" == "Xedit.cc" ];then
	cd $SRCPATH;make clean \-s;make \-s 2> log #产生loadcodefile可执行文件和 compile可执行文件
	if [ $? -ne 0 ];then
		cd $SRCPATH;cat log   #显示编译错误信息结果到屏幕
	fi
elif [ "X$codefile" == "Xedit.py" ];then
	echo "暂时还不支持..."
elif [ "X$codefile" == "Xedit.java" ];then
	echo "暂时还不支持..."
fi
$SRCPATH/file/compile
echo "</p>"
echo "</html>"

