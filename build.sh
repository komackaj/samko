#!/bin/bash

BUILD_DIRECTORY="build"
if [ ! -d $BUILD_DIRECTORY ]; then
  mkdir $BUILD_DIRECTORY
fi

cd build
cmake .. && make
