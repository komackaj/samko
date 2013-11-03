#!/bin/bash

BUILD_DIRECTORY="build"

if [ ! -d $BUILD_DIRECTORY ]; then
  mkdir $BUILD_DIRECTORY
fi

cd $BUILD_DIRECTORY
cmake .. -DCMAKE_INSTALL_PREFIX=.
make
make install
