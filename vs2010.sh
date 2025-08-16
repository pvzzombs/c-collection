#!/usr/bin/bash

export INCLUDE="C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include"
export LIB="C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/lib;C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Lib"
export PATH=$PATH:"/c/Program Files (x86)/Microsoft Visual Studio 10.0/Common7/IDE":"/c/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Bin":"/c/Program Files (x86)/Microsoft Visual Studio 10.0/VC/bin"

if [ -d ./buildWindows ]; then
  echo "Build folder detected..."
else 
  mkdir ./buildWindows
  echo "Build folder created..."
fi

cd ./buildWindows

if [ -d ./CMakeFiles ]; then
  echo "Detected cmake files..."
else
  cmake .. -DCMAKE_BUILD_TYPE=Debug
  echo "Generated cmake files..."
fi

cmake --build .
# cl main.c
# RC.Exe

# echo $INCLUDE
# echo $LIB
# echo $PATH