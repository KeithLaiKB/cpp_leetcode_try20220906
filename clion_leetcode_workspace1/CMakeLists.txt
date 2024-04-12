cmake_minimum_required(VERSION 3.22)
project(clion_leetcode_workspace1)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 20)

#add_executable(clion_leetcode_workspace1 main.cpp)


# 遍历项目根目录下所有的 .cpp 文件
file (GLOB_RECURSE files mysrc/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file} )
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()