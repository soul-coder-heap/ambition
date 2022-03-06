#!/bin/bash
set -e
set -x

export LANG=en_US.UTF-8
export LC_CTYPE=en_US.UTF-8
SCRIPT=$(readlink -f "$0")
BASEDIR=$(dirname "$SCRIPT")

source ${BASEDIR}/docker/VERSIONS

DOCKER_URL=$ML_DEV_DOCKER_URL
DOCKER_NAME=$ML_DEV_DOCKER_NAME
DOCKER_TAG=$ML_DEV_DOCKER_TAG
#EXTERNAL_VERSION=$(git rev-parse --short HEAD)
function build_image() {
docker build -f docker/Dockerfile_ml_platform_dev -t ${DOCKER_URL}/${DOCKER_NAME}:${DOCKER_TAG} \
    --build-arg thirdparty_build_image_tag=${ML_THIRDPARTY_BUILD_DOCKER_URL}/${ML_THIRDPARTY_BUILD_DOCKER_NAME}:${ML_THIRDPARTY_BUILD_DOCKER_TAG} \
    --build-arg external_url=${EXTERNAL_URL}/ml-platform-thirparty-RelWithDebInfo-${EXTERNAL_VERSION}.tar.bz2 \
    --build-arg external_file_name=ml-platform-thirparty-RelWithDebInfo-${EXTERNAL_VERSION}.tar.bz2 .

}
function push_image() {
docker push ${DOCKER_URL}/${DOCKER_NAME}:${DOCKER_TAG}

}
function help_usage() {
echo "sh build_dev_image.sh -b[uild] -p[ush]"

}
function Main() {
while getopts hbp OPTION
do
    case ${OPTION} in
        h) help_usage
            exit 1
            ;;
        b) build_image
            ;;
        p) push_image
            ;;
    esac
done

}
Main $*
