#!/bin/bash
set -x
num=0
function read_num
{
    random_num=`shuf -i 0-99 -n 1`
    if [[ $random_num -lt 10  ]]; then
        echo "$random_num" >> log.num
        ((num++))
        echo $num >> log.num
    fi
}
function cyc
{
    for i in {1..100};do
        echo "No.$i ---   "
        read_num
    done
    echo "total 100,appear $num"
}

cyc $*

