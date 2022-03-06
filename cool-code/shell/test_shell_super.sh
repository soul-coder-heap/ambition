#!/bin/bash
set -e

if [ $# -eq 0 ];then
    echo "\$0 =$0$@"
    exit 2
else
    echo "$0 parma > 1"
fi


factorial=1
for (( number = 1; number <= 1 ; number++ ))
do
    echo "factorial = $factorial"
    factorial=$[ $factorial * $number ]

done
echo The factorial of $1 is $factorial



count=1
#
for param in "$*"
do
    echo "\$* Parameter #$count = $param"
    count=$[ $count + 1 ]
done
#
echo
count=1
#
for param in "$@"
do
    echo "\$@ Parameter #$count = $param"
    count=$[ $count + 1 ]
done

while getopts :ab:c opt
do
    case "$opt" in
        a) echo "Found the -a option" ;;
        b) echo "Found the -b option, with value $OPTARG";;
        c) echo "Found the -c option" ;;
        *) echo "Unknown option: $opt";;
    esac
done
set -x
set -e
function getsum(){
    local sum=0  #局部变量
    for((i=$1; i<=$2; i++)); do
        ((sum+=i))
    done
   
    echo $sum
    #return 1
}

read m
read n

total=$(getsum $m $n)
echo "The sum is $? $total"
