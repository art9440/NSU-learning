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
add_executable(Kosaraju Kosaraju/Kosaraju.c
        Kosaraju/Kosaraju_func.c
        Kosaraju/Kosaraju_func.h)
add_executable(Huffman Huffman/Huffman.c)

add_executable(Akinator ../1st_term/Akinator/akinator.c
        ../1st_term/Akinator/tree.h)
add_executable(Calculator ../1st_term/Calculator/Calculator.c
        ../1st_term/Calculator/Stack.h)
add_executable(Boera-Mur ../1st_term/Boera-Mur-lab1-0/lab1-0.c)
add_executable(quickSort ../1st_term/quickSort/quickSort.c)

add_executable(Deikstra-lab2 ../1st_term/Deikstra-lab2/lab2.c)


add_executable(lab0 ../1st_term/lab0/lab0.c)
