#########################################################################
# File Name: publish.sh
# Author: tp
# mail: 1605872032@qq.com
# Created Time: 2018年08月07日 星期二 23时43分46秒
#########################################################################

#!/bin/bash


ROOT_PATH=/home/tp/project/web/bin
SRC=$ROOT_PATH/../wwwroot/
DST=$ROOT_PATH/../output

cp $ROOT_PATH/httpd  $DST -rf; 

mkdir -p  $DST/html $DST/css $DST/image 

cp $SRC/*.html $DST/html -rf; 
cp $SRC/css  $DST/css  -rf; 
cp $SRC/image $DST/image -rf; 


echo publish done! 
