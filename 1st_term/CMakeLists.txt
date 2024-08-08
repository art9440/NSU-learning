cmake_minimum_required(VERSION 3.26)
project(NSU_learning C)

set(CMAKE_C_STANDARD 11)

add_executable(../1st_term/Akinator ../1st_term/Akinator/akinator.c
        ../1st_term/Akinator/tree.h)
add_executable(../1st_term/Calculator ../1st_term/Calculator/Calculator.c
        ../1st_term/Calculator/Stack.h)
add_executable(quickSort ../1st_term/quickSort/quickSort.c
        ../1st_term/quickSort/quickSort.c)