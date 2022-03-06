#!/bin/bash
#SHELL_FOLDER=$(cd "$(dirname "$0")";pwd)
#echo ${SHELL_FOLDER}hub.xxx.com/ml-platform/ml-platform-dev
set -x
#Docker recommend to use exec
function runDocker(){
    docker run --rm -it --name yafengzhao-ml-platform-rs --net=host \
        -v /home/yafeng.zhao:/home/yafeng.zhao \
        -w /home/yafeng.zhao \
        -v /opt/aws:/opt/aws \
        hub.xxx.com/ml-platform/zyf-docker-dev:0.1
}

#-v /data:/data \
function execDocker(){
    docker exec -it $1 /bin/bash
}

function Main(){
    echo "parament number : $#"
    name="yafengzhao-ml-platform-rs"
    if [ $# -gt 0 ];then
        echo -n "You are setting docker run name tag : $1, are you sure ?(yes|no) : "
        read bool
        if [ $bool == "yes" ];then
            name=$1
        elif [ $bool == "no" ];then
            echo "WRRNING ,don't need new tag of container!"
            exit
        else
            echo "ERROR ,input error"
            exit
        fi
    fi

    containerID=$(docker ps | grep  "\<$name\>" | awk '{print $1}')
    if [ -z "$containerID" ];then
        echo "runDocker"
        runDocker $name
    else
        echo "execDocker"
        execDocker $containerID
    fi
}

Main $*


