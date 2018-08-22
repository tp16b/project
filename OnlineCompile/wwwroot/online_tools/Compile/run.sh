#########################################################################
# File Name: run.sh
# Author: tp
# mail: 1605872032@qq.com
# Created Time: 2018年08月17日 星期五 13时24分46秒
#########################################################################
#!/bin/bash

SRCPATH=/home/tp/project/web/wwwroot/online_tools/Compile 

$SRCPATH/loadcodefile         #执行该文件 生成用户编辑代码文件

codefile=`ls -t1 $SRCPATH/file | head -1` 
if [ "X$codefile" == "Xedit.c" ];then
	echo "find edit.c"
elif [ "X$codefile" == "Xedit.cc" ];then
	echo "find edit.cc"
elif [ "X$codefile" == "Xedit.py" ];then
	echo "find edit.py"
fi

#echo "<!DOCTYPE html>"
#echo "<html>" 
#echo "<meta charset=\"UTF-8\" http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>"  
#echo "<body bgcolor=\" #d0d0d0\">" 
#
#echo "<h1>The result: </h1>"
#cd $SRCPATH;make clean \-s;make \-s 2> log #产生loadcodefile可执行文件和 compile可执行文件
#if [ $? -ne 0 ];then
#	cd $SRCPATH;cat log
#fi
#echo "<p>"
#$SRCPATH/file/compile
#echo "</p>"
#echo "</html>"

