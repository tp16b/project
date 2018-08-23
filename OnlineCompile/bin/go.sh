#########################################################################
# File Name: go.sh
# Author: tp
# mail: 1605872032@qq.com
# Created Time: 2018年08月07日 星期二 17时34分46秒
#########################################################################
#!/bin/bash

cd /home/tp/project/OnlineCompile;make clean;
make;./bin/httpd 3030;
