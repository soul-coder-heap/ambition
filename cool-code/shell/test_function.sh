#!/bin/bash
function get_schema_string(){
    json_fmt='{"%s":"%s","%s":"%s","%s":"%s","%s":"%s"}\n'
    json_service='{"id":"node-%s-test","name": "rs-monitor","address":"%s",
    "port": %s,"tags":["rs","monitor"],
    "checks": [{"http": "http://%s:%s/metrics","interval": "35s"}]}\n'
    #printf $json_fmt $ad ${prefix}$ad $creative ${prefix}$creative $user $user ${prefix}$user $user
    json_service_fmt='{"id":"node-%s-test","name":"re-monitor","address":"%s","port":%s,"tag":["rs":["rs","monitor"],"checks":[{"http":"http://%s:%s/metrics","internal":"35s"}]}\n'
    printf $json_service_fmt $1 $1 $2 $1 $2 
}
function show_ip(){
    detect_ip="http://186.12.34.23 http://52.74.179.178"
    for ip in ${detect_ip};do
        echo $ip
    done
} 

function checks_ip(){
    ip=$1
    echo $ip
    if [[ $ip =~ ^[0-9]{1,3}\.([0-9]{1,3}\.){2}[0-9]{1,3}$ ]];then
        for i in {1..4};do
            num=`echo "$ip" | xargs | cut -d "." -f$i`
            if [[  $num -le 0 || $num -ge 255 ]];then
                echo 1 && exit
            fi
        done
    else
        echo 1 && exit
    fi        
    echo 0
}

checks_ip $*
#show_ip




#get_schema_string $*
