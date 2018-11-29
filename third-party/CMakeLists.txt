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
ELSEIF(RANDOM_FUNC STREQUAL custom)
    add_definitions(-DCUSTOM_RAND_FUNC)
ELSE()
    message(WARNING "not defined RANDOM_FUNC: [${RANDOM_FUNC}], continue with the default rand() function")
ENDIF()