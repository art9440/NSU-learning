cmake_minimum_required(VERSION 3.26)
project(NSU_learning C)

set(CMAKE_C_STANDARD 11)

add_executable(NSU_learning
        "AVL_tree/AVL_tree.c"
        AVL_tree/functions.h
)
add_executable(lab9 lab9-0/lab9-0.c
        lab9-0/Graph_func.h)

add_executable(lab8 lab8-0
        lab8-0/Kruskal.c
        lab8-0/Graph.h
)
