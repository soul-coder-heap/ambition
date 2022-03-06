#!/usr/bin/env bash

function get_proc_pid() {
    local name=$1
    pid=$(ps aux |grep $name|grep -v grep | awk '{print $2}')
    echo $pid
}
function is_same_file() {
    local base_file=$1
    local online_file=$2
    if [[ -f $online_file ]]; then
        base_md5sum=$(md5sum $base_file | awk '{print $1}')
        online_md5sum=$(md5sum $online_file |awk '{print $1}')
        if [[ $base_md5sum == $online_md5sum ]];then
            return 0
        else
            return 1
        fi
    fi
    return 1
}
no_update=0
gray_check=1
gray_download_fail=0
algo_testing_machine=0
function sync_file_bykey() {
    local key=$1
    python script/model_tool.py --type=1 --url="onlytest" \
                                --path=/data/model_update/download \
                                --key="$key"
    if [[ $? -ne 0 ]];then
        echo "run model_tool.py $key failed, please check aws or oss"
        exit -1
    fi
}
function main() {
    ulimit -c unlimited
    ulimit -r unlimited
    ulimit -e unlimited
    export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
    export TCMALLOC_MAX_TOTAL_THREAD_CACHE_BYTES=104857600
    export OMP_NUM_THREADS=1
    export MXNET_ENGINE_TYPE=NaiveEngine
    export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
    export ASAN_OPTIONS=symbolize=1:abort_on_error=1:disable_coredump=0:unmap_shadow_on_exit=1:disable_core=0:sleep_before_dying=150
    if [[ -f /sys/fs/cgroup/cpu/tasks ]]; then
        echo $$ >> /sys/fs/cgroup/cpu/tasks
    fi
    pid=$(get_proc_pid "bin/exec_bin")
    if [[ ! -z $pid ]]; then
        echo "another exec_bin with $pid exist"
        exit -1
    fi
    #generate newest configure
    python script/model_tool.py -t 3 -c conf/model_service_client_local.json
    if [[ $? -ne 0 ]];then
        echo "run model_tool.py failed, please check aws or oss"
        exit -1
    fi
    if [[ $no_update -eq 0 ]];then
        sync_file_bykey "modeldata/ranker/"
        if [[ algo_testing_machine -gt 0 ]]; then
            sync_file_bykey "dev/modeldata/dense/"
        fi
        sync_file_bykey "modeldata/dense/"
    fi
    #regisiter watch key
    model_consul_watches_file="/etc/consul/model_consul_watches.json"
    this_consul_watches_file="script/model_consul_watches.json"
    is_same_file $this_consul_watches_file $model_consul_watches_file
    if [[ $? -ne 0 ]];then
        cp $this_consul_watches_file  $model_consul_watches_file
    fi
    if  [[ $no_update -gt 0 ]];then
        rm -rf $model_consul_watches_file
    fi
    cp script/http_consul_watches.json  /etc/consul/
    /usr/local/consul/consul reload
    ./bin/exec_bin
}
function help_usage() {
    echo "run -n[o_update]"
}
function get_value_from_gray() {
    local key=$1
    gray_key_onconsul="modeldata/gray/exec_bin"
    curl "http://127.0.0.1:8500/v1/kv/$gray_key_onconsul?raw=true" | jq -r ".$key"
}
function empty_jq_value() {
    local value=$1
    if [ -z $value -o "X$value" == "Xnull" ];then
        return 0
    fi
    return 1;
}
function get_grayrate_from_gray() {
    local cloud=$(get_value_from_gray cloud)
    empty_jq_value $cloud
    if [[ $? -eq 0 ]]; then
        return;
    fi
    # info {
    #     gray_cloud_list : "aws-fk:10;ali-sg:10"
    # }
    local gray_cloud_list=$(get_value_from_gray info.gray_cloud_list)
    empty_jq_value $gray_cloud_list
    if [[ $? -eq 0 ]]; then
        return;
    fi
    echo $gray_cloud_list | awk -vcloud=$cloud -F'[;|:]' '{
        grayrate=0
        for(i = 1; i <= NF; i+=2) {
            if ($i==cloud) {
                grayrate = $(i+1)
                break;
            }
        }
        print grayrate
    }'
}
function check_sync_gray_version() {
    which jq
    if [[ $? -ne 0 ]];then
        yum install jq.x86_64 -y
        if [[ $? -ne 0 ]];then
            echo "pls install jq"
            return
        fi
    fi
    #https://blog.eduonix.com/shell-scripting/generating-random-numbers-in-linux-shell-scripting/
    grayrate=$(get_grayrate_from_gray)
    random_num=$(shuf -i 0-99 -n 1)
    echo "random_num $random_num when grayrate $grayrate"
    # cut grayrate % to gray flow
    if [[ $random_num -ge $grayrate ]]; then
        return
    fi
    ranker_deploy=/data/recommend/exec_bin
    local_version=$($ranker_deploy/bin/exec_bin -v | grep RANKER_TAG_VERSION | awk '{print $2}')
    gray_version=$(get_value_from_gray version)
    if [[ -z $gray_version ]]; then
        return
    fi
    if [[ $local_version == $gray_version ]];then
        return
    fi
    util_cmd=$(get_value_from_gray util_cmd)
    if [[ -z $util_cmd ]]; then
        return
    fi
    path=$(get_value_from_gray path)
    if [[ -z $path ]]; then
        return
    fi
    cmd=$(echo "$util_cmd $path $ranker_deploy")
    echo $cmd
    try_count=1
    kMaxTryCount=4
    while [[ $try_count -lt $kMaxTryCount ]]; do
        $cmd
        if [[ $? -eq 0 ]]; then
            chmod +x $ranker_deploy/bin/exec_bin
            chmod +x $ranker_deploy/run
            chmod +x $ranker_deploy/supervise.exec_bin
            break;
        else
            # todo Notify when fail download
            echo "try $try_count : $cmd"
            try_count=$(($try_count + 1))
        fi
    done
    if [[ $try_count -ge $kMaxTryCount ]]; then
        gray_download_fail=1
    fi
}
function port_check() {
    port_list=("7077" "18080" "10102" "10101")
    for port in ${port_list[@]}
    do
        proc_list=$(netstat -nltp | grep $port |grep -v grep)
        if [[ $? -eq 0 ]];then
            pid=$(echo $proc_list | awk '{n=split($NF, arr, "/"); print arr[1];}')
            #skip "-"
            if [[ "X"$pid != "X-" ]];then
                kill -9 $pid
            fi
        fi
    done
}
function main_wrapper() {
   while getopts hgn OPTION
    do
       case ${OPTION} in
            h) help_usage
            exit 1
            ;;
            n) no_update=1
            ;;
            g) gray_check=1
            ;;
        esac
    done
    #test env check
   if [[ "X$RS" == "XDEV" ]];then
       gray_check=0
       algo_testing_machine=1
   fi
   if [[ $gray_check -eq 1 ]];then
       check_sync_gray_version
   fi
   if [[ $gray_download_fail -eq 0 ]]; then
       port_check
       main
   fi
}
main_wrapper $*
