cmake_minimum_required(VERSION 3.20)
project(DS_Prj_Hash)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_Prj_Hash
        arrayHash.cpp
        arrayHash.h
        main.cpp chainingArray.cpp chainingArray.h)
