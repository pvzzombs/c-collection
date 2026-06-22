#!/usr/bin/bash

export INCLUDE="C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include;C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Include"
export LIB="C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/lib;C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Lib"
export PATH="/c/Program Files (x86)/Microsoft Visual Studio 10.0/Common7/IDE":"/c/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Bin":"/c/Program Files (x86)/Microsoft Visual Studio 10.0/VC/bin":$PATH
export VSINSTALLDIR="/c/Program Files (x86)/Microsoft Visual Studio 10.0"

if [ -d ./buildWindows ]; then
  echo "Build folder detected..."
else 
  mkdir ./buildWindows
  echo "Build folder created..."
fi

meson setup --reconfigure buildWindows --backend=vs

# ninja -C buildWindows

# cl main.c
# RC.Exe

# echo $INCLUDE
# echo $LIB
# echo $PATH