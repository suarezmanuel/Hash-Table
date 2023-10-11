cmake_minimum_required(VERSION 3.26)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

add_executable(HashTable src/main.cpp
        src/hash_table.cpp
        headers/hash_table.h
        src/prime.cpp
        headers/prime.h
        src/hash_item.cpp
        headers/hash_item.h
)
