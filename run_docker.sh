#!/bin/bash

# Variables
IMAGE_NAME="web_app"
CONTAINER_NAME="C_web_app"
HOST_PORT=9002
CONTAINER_PORT=9002
DOCKERFILE_PATH="."

# build docker image
docker build -t $IMAGE_NAME $DOCKERFILE_PATH

# run docker container
docker run -d -p $HOST_PORT:$CONTAINER_PORT --name $CONTAINER_NAME --rm $IMAGE_NAME