#########################################################################
# File Name: run.sh
# Author: tp
# Created Time: 2018年08月17日 星期五 13时24分46秒
#########################################################################
#!/bin/bash

SRCPATH=/home/tp/project/OnlineCompile/wwwroot/online_tools/Compile 

$SRCPATH/loadcodefile         #执行,则从浏览器中导入用户编辑的代码文件
C_PATH=$SRCPATH/file/C/
CC_PATH=$SRCPATH/file/C++/
JV_PATH=$SRCPATH/file/Java/
PY_PATH=$SRCPATH/file/Python/

codefile=`ls -t1 $SRCPATH/file | head -1` #当前用户编辑的codefile 

echo "<!DOCTYPE html>"
echo "<html>" 
echo "<meta charset=\"UTF-8\" http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>"  
echo "<body bgcolor=\" #d0d0d0\">" 
echo "<h1>The result: </h1>"
echo "<p>"


if [ "X$codefile" == "Xedit.c" ];then
	cd $C_PATH;make clean \-s;make \-s 2> log
	if [ $? -ne 0 ];then      #make执行出错，用户编辑的代码有语法错误
		cd $C_PATH;cat log   #显示编译错误信息结果到屏幕
	else
		$SRCPATH/file/compile     #执行编译完的程序
	fi
elif [ "X$codefile" == "Xedit.cc" ];then
	cd $CC_PATH;make clean \-s;make \-s 2> log #make产生compile可执行文件,将错误信息导入到log
	if [ $? -ne 0 ];then      #make执行出错，用户编辑的代码有语法错误
		cd $CC_PATH;cat log   #显示编译错误信息结果到屏幕
	else
		$SRCPATH/file/compile     #执行编译完的程序
	fi
elif [ "X$codefile" == "Xedit.py" ];then
	echo "sorry,暂时还不支持python语言..."
elif [ "X$codefile" == "Xedit.java" ];then
	echo "sorry,暂时还不支持java语言..."
fi

echo "</p>"
echo "</html>"

