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
        lab8-1/Prim.c

)
add_executable(lab8-1 lab8-1/Prim.c
        lab8-1/Prim_function.c
        lab8-1/Prim_function.h
)
add_executable(lab7 lab7-0/Top_Sort.c
        lab7-0/Top_sort_func.c
        lab7-0/Top_sort_func.h)
