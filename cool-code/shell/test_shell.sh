#!/bin/bash
set -x
set -e
if pwd;
then
    echo "It work"
fi


today=$(date +%y%m%d)
ls -al /usr/bin >log.$today
echo "((数学计算))"
value1=10
value2=$(( $value1 * 100 ))
va=$(( $value2 ** 2 ))
echo "va = $va"
echo The resulting value is $value2
echo "(expr 数学计算)"
va1=10
va2=23
va3=$(expr 1 \* 5)
echo "$va3"

echo "[ 数学计算 ]"
va3=$[ $va1 * $va2 ]
echo "$va3"
echo "$?"
echo "1"

#数学

if [ $va1 -eq 56 ]
then
    echo "$val == 56, True"
else
    echo "$val == 56, False"
fi

#字符串
str1="asdfvg"
str2="2e3ewrtt"
if [ $str1 != $str2 ];then
    echo "$str1 != $str2"
else
    echo "$str1 == $str2"
fi

if [ ! -z $str1 ];then
    echo "$str1 lengeth != 0"
else
    echo "$str1 length == 0"
fi

echo "$str2 length = ${#str2}"


# 文件
filename="a.txt"
if [ -f $filename ];then
    echo "$filename exist"
else
    echo "$filename not exist"
    touch $filename
fi

USER="rich"
case $USER in
rich | barbara)
    echo "Welcome, $USER"
    echo "Please enjoy your visit";;
testing)
    echo "Special testing account";;
jessica)
    echo "Do not forget to log off when you're done";;
*)
    echo "Sorry, you are not allowed here";;
esac

set +x
for (( i=1; i <= 3; i++ ))
do
    echo "c style --> The next number is $i"
done

for i in {1..3}
do
    echo "in style--> The next number is $i"
done

var1=10
while [ $var1 -gt 0 ]
do
    echo $var1
    var1=$[ $var1 - 1 ]
done
