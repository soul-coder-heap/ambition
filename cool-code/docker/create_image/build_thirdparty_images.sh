#!/bin/bash

set -e
set -x
alias docker='docker.exe'
export LANG=en_US.UTF-8
export LC_CTYPE=en_US.UTF-8
SCRIPT=$(readlink -f "$0")
BASEDIR=$(dirname "$SCRIPT")

source ${BASEDIR}/docker/VERSIONS
img_url=${ML_THIRDPARTY_BUILD_DOCKER_URL}/${ML_THIRDPARTY_BUILD_DOCKER_NAME}:${ML_THIRDPARTY_BUILD_DOCKER_TAG}
docker build -f docker/Dockerfile_thirdparty_build -t  $img_url .