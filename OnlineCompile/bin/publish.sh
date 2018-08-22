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

mkdir -p  $DST/html $DST/css $DST/image $DST/book ;

cp $SRC/*.html $DST/html -rf; 
cp $SRC/css  $DST/css  -rf; 
cp $SRC/*.txt $DST/book -rf; 
cp $SRC/image $DST/image -rf; 
cp $SRC/cgi_src $DST -rf; 

mkdir -p $DST/cgi_src;
cp $SRC/cgi_src/*.c  $DST/cgi_src  -rf; 
cp $SRC/test_cgi $DST -rf; 

echo published finish! 
