#!/bin/bash
function readjson(){
    if [ -f $1 ]; then
        cat $1 | awk -F"[firstName]" '/firstName/{print $0}'
    fi
}
readjson $@
