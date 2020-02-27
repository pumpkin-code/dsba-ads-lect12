cmake_minimum_required(VERSION 3.0)

project(ADSLecture12_Demos CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 14)

# the following options prevent compiler-optimization issues that are unwanted in an edu process


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

#### the list of targets ####
add_executable(ex1_smartptrs
        ex1_smartptrs/main.cpp
    )
    
add_executable(ex2_typeinfo
        ex2_typeinfo/main.cpp
    )
    
add_executable(ex3_auto
        ex3_auto/main.cpp
    )

add_executable(ex4_stlalgo    
        ex4_stlalgo/main.cpp
    )    
    