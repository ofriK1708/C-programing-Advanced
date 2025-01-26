cmake_minimum_required(VERSION 3.27)
project(Assignment_4 C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment_4 main.c myTreeFun.c myTreeFun.h)
add_executable(expressionTree expressionTree.c
        expressionTreeFun.c
        expressionTreeFun.h myTreeFun.c myTreeFun.h)
add_executable(addLeaf addLeaf.c
        ListFun.c
        ListFun.h
        TreeLeafFun.c
        TreeLeafFun.h)
add_executable(testingZone testingZone.c)
add_executable(printTreeByLevels printTreeByLevels.c myTreeFun.c myTreeFun.h
        coordListFun.c
        coordListFun.h
        TreeLevels.c
        TreeLevels.h)
