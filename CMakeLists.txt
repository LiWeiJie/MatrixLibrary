﻿# 0. Options for Compiler
option(ML_TEST "test" ON)
option(RANDOM_FUNC default)

# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# 3. set environment variable

# 4. set name for build
SET(BUILD_NAME ${PROJECT_NAME})

set(MATRIXLIB_VERSION_MAJOR 1)
set(MATRIXLIB_VERSION_MINOR 0)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

IF(BUILD_TARGET STREQUAL macOS)
    add_definitions(-D__macOS__)
ELSEIF(BUILD_TARGET STREQUAL win32)
    add_definitions(-D_WIN32)
ELSEIF(BUILD_TARGET STREQUAL iOS)
    add_definitions(-D__iOS__)
    message(STATUS "iOS\t" ${CMAKE_TOOLCHAIN_FILE} \t ${IOS_PLATFORM})
    IF(NOT DEFINED CMAKE_TOOLCHAIN_FILE OR NOT DEFINED IOS_PLATFORM OR NOT DEFINED IOS_ARCH)
        message(FATAL_ERROR "If you want to compile iOS version, please add the definition CMAKE_TOOLCHAIN_FILE, IOS_PLATFORM, IOS_ARCH. For more details, please read the README.md")
    ENDIF()
ELSEIF(BUILD_TARGET STREQUAL Android)
    add_definitions(-D__ANDROID__)
    SET(MATRIXLIB_LINK ${MATRIXLIB_LINK} android log m)
    IF(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        message(FATAL_ERROR "If you want to compile Android version, please add the definition CMAKE_TOOLCHAIN_FILE. For more details, please read the README.md")
    ENDIF()
ELSEIF(BUILD_TARGET STREQUAL Unix)
    SET(MATRIXLIB_LINK ${MATRIXLIB_LINK} m)
    add_definitions(-D__unix__)
ELSE()
    message(FATAL_ERROR "Please set the definition BUILD_TARGET=[macOS/win32/iOS/Unix/Android]")
ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


# ------------------
# Compiler Environment Configure
#
message(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})

set(CMAKE_C_FLAGS_RELEASE     "-O2")
set(CMAKE_C_FLAGS_DEBUG       "-O0 -g3 -Werror -Wall")


########################## var info ##########################

########################## compile info ##########################

IF(NOT RANDOM_FUNC STREQUAL default)
    INCLUDE(third-party/CMakeLists.txt)
ENDIF()

LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/lib
)

INCLUDE_DIRECTORIES(include)

configure_file(
        "${PROJECT_SOURCE_DIR}/scripts/matrixlib_cfg.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/matrixlib/matrixlib_cfg.h"
)

add_subdirectory(src)

##########################  static lib ##########################

########################## dynamic lib ##########################

########################## test ##########################

IF(ML_TEST)
    add_subdirectory(test test)
ENDIF(ML_TEST)

########################## install info  ##########################

install(DIRECTORY include DESTINATION ./ 
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN ".gitignore" EXCLUDE
)

