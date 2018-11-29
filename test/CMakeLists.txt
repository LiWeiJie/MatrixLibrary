# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# 3. set environment variable
# 设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"

# set name for build
SET(BUILD_NAME matrixlib_test)

SET(BUILD_SHARED ${PROJECT_NAME}_SHARED)
SET(BUILD_STATIC ${PROJECT_NAME}_STATIC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# 5. Generate config file
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ml_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/ml_config.h @ONLY)

message(STATUS "${PROJECT_NAME} ML_TEST ON")
SET(ML_TEST_SRC 
    test.c 
    math_test.c
)

ADD_EXECUTABLE(${BUILD_NAME} ${ML_TEST_SRC})
TARGET_LINK_LIBRARIES(${BUILD_NAME} matrixlib ${MATRIXLIB_LINK})


