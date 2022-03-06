#!/bin/bash
function check_ip(){
    #echo $1|grep "^[0-9]\{1,3\}\.\([0-9]\{1,3\}\.\)\{2\}[0-9]\{1,3\}$" > /dev/null;
    if [ ! -n "$1" ] ; then
        echo 1 && exit;
    fi
    if [ $? -ne 0 ];then
        echo 1 && exit
    fi
    ipaddr=$1
    a=`echo $ipaddr|awk -F . '{print $1}'`
    b=`echo $ipaddr|awk -F . '{print $2}'`
    c=`echo $ipaddr|awk -F . '{print $3}'`
    d=`echo $ipaddr|awk -F . '{print $4}'`
    for num in $a $b $c $d
    do
        if [ $num -gt 255 ] || [ $num -lt 0 ]    #0~255
        then
            echo 1 && exit
        fi
    done
    echo 0
}
function get_rs_ip(){
    START=`date +%s%N`;
    command="curl -s $1";
    ip=$($command);
    END=`date +%s%N`;
    time=$((END-START))
    time=`expr $time / 1000000`
    #echo "cost time : $time"
    echo "$ip"
}

function get_ip(){
    detect_ip1="http://169.254.169.254/latest/meta-data/public-ipv4"
    detect_ip2="http://100.100.100.200/latest/meta-data/eipv4"
    ip=$(get_rs_ip $detect_ip1)
    judge_is_ip=$(check_ip $ip)
    if [ $judge_is_ip -eq 1 ]; then
        ip=$(get_rs_ip $detect_ip2)
        judge_is_ip=$(check_ip $ip)
        if [ $judge_is_ip -eq 1 ];then
            echo "get rs ip fail."
            echo 1 && exit
        fi
    fi
    echo "$ip"
    #public_adress=$(hostname)
    #public_ip=`echo $public_adress | awk -F":" '{print $2}'`
    #echo $public_ip
}
function register_consul(){
    port="18080"
    consul_address="127.0.0.1:8500"
    ip=$(get_ip)
    service="'"'{"id": "node-52.74.179.178-test","name": "rs-monitor","address":
         "52.74.179.178","port": 18080,"tags": ["rs","monitor"],"checks": [{"http": "http://52.74.179.178:
         18080/metrics","interval": "35s"}]}'"'"
    register_command="curl -g -X  PUT -d ${service} http://127.0.0.1:8500/v1/agent/service/register"
    echo $register_command
    curl -g -X PUT -d '{"id": "node-'$ip'","name": "rs-monitor","address": "'$ip'","port": '$port',"tags": ["rs","monitor"],"checks": [{"http": "http://'$ip':'$port'/metrics","interval": "35s"}]}' http://$consul_address/v1/agent/service/register
    echo 0
}

function deregister_consul(){
    consul_address="127.0.0.1:8500"
    port="18080"
    ip=$(get_ip)
    deregister_command="curl -X PUT http://$consul_address/v1/agent/service/deregister/node-$ip-test"
    echo $deregister_command
    curl -X PUT http://$consul_address/v1/agent/service/deregister/node-$ip-test
    echo 0
}
function search_consul(){
    consul_address="127.0.0.1:8500"
    search_command="curl -s http://127.0.0.1:8500/v1/health/service/rs-monitor"
    echo $search_command
    curl -s http://127.0.0.1:8500/v1/health/service/rs-monitor
    echo 0
}
function Main(){
    if [ $1 -eq 0 ]; then
        (register_consul)
    fi

    if [ $1 -eq 1 ];then
        (deregister_consul)
    fi

    if [ $1 -eq 2 ];then
        (search_consul)
    fi
}
# simple parameter : 0 register , 1 deregister , 2 search
Main $*

