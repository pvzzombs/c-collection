#!/usr/bin/bash

export INCLUDE="C:/Apps/vs15/include;C:/Apps/vs15/sdk/include"
export LIB="C:/Apps/vs15/lib;C:/Apps/vs15/sdk/lib"
export PATH=$PATH:"/c/Apps/vs15/bin":"/c/Apps/vs15/sdk/bin"

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
  cmake .. -DCMAKE_BUILD_TYPE=Release
  echo "Generated cmake files..."
fi

cmake --build . --config Release
# cl main.c
# RC.Exe

# echo $INCLUDE
# echo $LIB
# echo $PATH