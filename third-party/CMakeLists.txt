# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# add_subdirectory(third-party)    
IF (RANDOM_FUNC STREQUAL aisino)
    SET(AISINO_RAND_FUNC ON)
    
    SET(MATRIXLIB_LINK aisino_rand)
    
    INCLUDE_DIRECTORIES(third-party/aisino_rand/header)
    INCLUDE_DIRECTORIES(third-party/aisino_rand/include)
    add_subdirectory(third-party/aisino_rand)
ELSEIF(RANDOM_FUNC STREQUAL custom)
    SET(CUSTOM_RAND_FUNC ON)
ELSE()
    message(WARNING "Not defined RANDOM_FUNC: [${RANDOM_FUNC}], continue with the default rand() function")
ENDIF()