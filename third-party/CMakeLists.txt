# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# add_subdirectory(third-party)    
IF (RANDOM_FUNC STREQUAL aisino)
    add_definitions(-DAISINO_RAND_FUNC)
    SET(MATRIXLIB_LINK aisino_rand)
    
    INCLUDE_DIRECTORIES(third-party/aisino_rand/header)
    INCLUDE_DIRECTORIES(third-party/aisino_rand/include)
    add_subdirectory(third-party/aisino_rand)
ELSE()
    add_definitions(-DCUSTOM_RAND_FUNC)
ENDIF()