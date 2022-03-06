 #!/bin/bash

if [ ! -f $1 ];then
    echo "XXXX" && exit
else
    echo "success"
fi
ipstr=$(cat $1 | jq '{external_ip:.external_ip} | .[]')
ip=${ipstr//\"/}
if [ -n "$ip" ];then
    echo "length > 0"
fi
echo $ip