#!/bin/bash
repo_url=https://registry.hub.docker.com/v1/repositories
image_tag=$1
curl -s ${repo_url}/${image_tag} | jq | grep name | awk '{print $2}' | sed -e 's/"/g'
