#!/bin/bash

function in_path(){
    # 尝试在环境变量PATH中找到命令。如果找到就返回0；
    valid=$(echo $1 | sed -e 's/[^[:alnum:]//g]')
    if [ $valid==$1 ];then
        echo "yes"
    else
        echo "no"
    fi
}
in_path $#
