# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# 3. set environment variable
# 设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"

# set name for build
SET(MATRIX_LIB matrixlib)
SET(BUILD_NAME ${MATRIX_LIB})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

########################## var info ##########################


########################## compile info ##########################

# ADD SOURCES

AUX_SOURCE_DIRECTORY(m4ri SRCS)
AUX_SOURCE_DIRECTORY(matrixlib SRCS)

########################## dynamic lib ##########################

ADD_LIBRARY(${BUILD_NAME} SHARED ${SRCS})

SET_TARGET_PROPERTIES(${BUILD_NAME} PROPERTIES OUTPUT_NAME ${BUILD_NAME})
SET_TARGET_PROPERTIES(${BUILD_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

message(STATUS "MATRIXLIB_LINK: ${MATRIXLIB_LINK}")

IF(MATRIXLIB_LINK)
    TARGET_LINK_LIBRARIES(${BUILD_NAME} ${MATRIXLIB_LINK})
ENDIF(MATRIXLIB_LINK)

##########################  static lib ##########################


ADD_LIBRARY(${BUILD_NAME}_STATIC STATIC ${SRCS})

SET_TARGET_PROPERTIES(${BUILD_NAME}_STATIC PROPERTIES OUTPUT_NAME ${BUILD_NAME})
SET_TARGET_PROPERTIES(${BUILD_NAME}_STATIC PROPERTIES CLEAN_DIRECT_OUTPUT 1)

IF(MATRIXLIB_LINK)
    TARGET_LINK_LIBRARIES(${BUILD_NAME}_STATIC ${MATRIXLIB_LINK})
ENDIF(MATRIXLIB_LINK)

########################## install info  ##########################

install(TARGETS ${BUILD_NAME}
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


install(TARGETS ${BUILD_NAME}_STATIC
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


