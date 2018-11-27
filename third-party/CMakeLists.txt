# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

IF (RANDOM_FUNC STREQUAL aisino)
    add_definitions(-DAISINO_RAND_FUNC)
    add_subdirectory(aisino_rand)
ELSE()
    add_definitions(-DCUSTOM_RAND_FUNC)
ENDIF()
