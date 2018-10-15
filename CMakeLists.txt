# 0. Options for Compiler
option(DEBUG "debug" OFF)
option(ML_TEST "test" ON)
option(BUILD_TARGET "target platform" OFF)

if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
    set(build_os win32)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    set(build_os macOS)
    SET(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
    set(build_os linux)
endif()

IF(BUILD_TARGET)
    message("\nBuild: ${BUILD_TARGET}")
ELSE()
    SET(BUILD_TARGET ${build_os})
    message("\nBuild: ${BUILD_TARGET}")
    
ENDIF()

IF(BUILD_TARGET STREQUAL macOS)
    add_definitions(-D__macOS__)
ENDIF()

IF(BUILD_TARGET STREQUAL win32)
    add_definitions(-D_WIN32)
ENDIF()

IF(BUILD_TARGET STREQUAL iOS)
    add_definitions(-D__iOS__)

    SET(CMD "xcrun -sdk iphoneos --show-sdk-path")
    EXEC_PROGRAM(${CMD} OUTPUT_VARIABLE iOS_SDK_PATH)
    SET(CMD "xcrun -sdk iphoneos --find clang")
    EXEC_PROGRAM(${CMD} OUTPUT_VARIABLE CLANG_PATH)
    set(CMAKE_C_COMPILER ${CLANG_PATH})
    #-F${iOS_SDK_PATH}/System/Library/Frameworks
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -isysroot ${iOS_SDK_PATH} -Wunused-command-line-argument -arch arm64 -arch armv7 -miphoneos-version-min=8.0 -fembed-bitcode")
    message("CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
    message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
ENDIF()

IF(BUILD_TARGET STREQUAL Android)
    add_definitions(-D__ANDROID__)

    message(FATAL_ERROR
    "Finished to generate <ml_config.h>! \n"
    "If you want to compile, please run 'ndk-build NDK_PROJECT_PATH=./ NDK_APPLICATION_MK=./Application.mk'."
    )
ENDIF()


# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(MatrixLib)

# 3. set environment variable
# 设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"

# set name for build
SET(BUILD_NAME ${PROJECT_NAME})

# set debug
IF(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(DEBUG ON)
ENDIF()

SET(BUILD_SHARED_NAME ${PROJECT_NAME}_SHARED)
SET(BUILD_STATIC_NAME ${PROJECT_NAME}_STATIC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# iOS Setting


# ------------------
# Compiler Environment Configure
#
message("\nCMake Complier IS:")

IF(DEBUG)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -O0 -g3")
ENDIF(DEBUG)

if(CMAKE_COMPILER_IS_GNUCC)
    # some warnings we want are not available with old GCC versions
    # note: starting with CMake 2.8 we could use CMAKE_C_COMPILER_VERSION
    message("GNUCC\n")
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                    OUTPUT_VARIABLE GCC_VERSION)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm  -fPIC -D_POSIX_SOURCE -std=c99 -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings")
    if (GCC_VERSION VERSION_GREATER 4.5 OR GCC_VERSION VERSION_EQUAL 4.5)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wlogical-op")
    endif()
    if (GCC_VERSION VERSION_GREATER 4.8 OR GCC_VERSION VERSION_EQUAL 4.8)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wshadow")
    endif()
    set(CMAKE_C_FLAGS_RELEASE     "-O2")
    set(CMAKE_C_FLAGS_DEBUG       "-O0 -g3")
    set(CMAKE_C_FLAGS_COVERAGE    "-O0 -g3 --coverage")
    set(CMAKE_C_FLAGS_ASAN        "-Werror -fsanitize=address -fno-common -O3")
    set(CMAKE_C_FLAGS_ASANDBG     "-Werror -fsanitize=address -fno-common -O1 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls ")
    set(CMAKE_C_FLAGS_CHECK       "-Werror -Os")
    set(CMAKE_C_FLAGS_CHECKFULL   "${CMAKE_C_FLAGS_CHECK} -Wcast-qual")
endif(CMAKE_COMPILER_IS_GNUCC)

if(CMAKE_COMPILER_IS_CLANG)
    message("CLang\n")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -W -Wdeclaration-after-statement -Wwrite-strings -Wpointer-arith -Wimplicit-fallthrough -Wshadow")
    set(CMAKE_C_FLAGS_RELEASE     "-O2")
    set(CMAKE_C_FLAGS_DEBUG       "-O0 -g3")
    set(CMAKE_C_FLAGS_COVERAGE    "-O0 -g3 --coverage")
    set(CMAKE_C_FLAGS_ASAN        "-Werror -fsanitize=address -fno-common -fsanitize=undefined -fno-sanitize-recover -O3")
    set(CMAKE_C_FLAGS_ASANDBG     "-Werror -fsanitize=address -fno-common -fsanitize=undefined -fno-sanitize-recover -O1 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls ")
    set(CMAKE_C_FLAGS_MEMSAN      "-Werror -fsanitize=memory -O3")
    set(CMAKE_C_FLAGS_MEMSANDBG   "-Werror -fsanitize=memory -O1 -g3 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2")
    set(CMAKE_C_FLAGS_CHECK       "-Werror -Os")
endif(CMAKE_COMPILER_IS_CLANG)

if(MSVC)
    # Strictest warnings, and treat as errors
    message("MicroSoft Visual C\n")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
endif(MSVC)

# ------------------
# Compiler Module Configure
#
message("Compiler Module Configure:")

# 5. Generate config file
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ml_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/ml_config.h @ONLY)



########################## var info ##########################


SET(BUILD_SHARED_NAME ${PROJECT_NAME}_SHARED)
SET(BUILD_STATIC_NAME ${PROJECT_NAME}_STATIC)
if (DEFINED CMAKE_INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX ./install_destination)
endif()
message("install_destination:\t"  ${CMAKE_INSTALL_PREFIX})

########################## compile info ##########################

# 6. head file path，头文件目录
INCLUDE_DIRECTORIES(include)

# ADD SOURCES

AUX_SOURCE_DIRECTORY(src/m4ri M4RI_SRC)
AUX_SOURCE_DIRECTORY(src/Matrixlib ML_SRCS)

SET(LIB_SRCS  ${ML_SRCS} ${M4RI_SRC})



##########################  static lib ##########################


ADD_LIBRARY(${BUILD_STATIC_NAME} STATIC ${LIB_SRCS})

SET_TARGET_PROPERTIES(${BUILD_STATIC_NAME} PROPERTIES OUTPUT_NAME ${BUILD_NAME})
SET_TARGET_PROPERTIES(${BUILD_STATIC_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

IF(LINK_LIBS)
    TARGET_LINK_LIBRARIES(${BUILD_STATIC_NAME} ${LINK_LIBS})
ENDIF(LINK_LIBS)


########################## dynamic lib ##########################

ADD_LIBRARY(${BUILD_SHARED_NAME} SHARED ${LIB_SRCS})
SET_TARGET_PROPERTIES(${BUILD_SHARED_NAME} PROPERTIES OUTPUT_NAME ${BUILD_NAME})
SET_TARGET_PROPERTIES(${BUILD_SHARED_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

IF(LINK_LIBS)
    TARGET_LINK_LIBRARIES(${BUILD_SHARED_NAME} ${LINK_LIBS})
ENDIF(LINK_LIBS)


########################## test ##########################
# test
IF(ML_TEST)
    message("${PROJECT_NAME} ML_TEST ON")
    SET(ML_TEST_SRC test/test.c test/math_test.c)

    SET(ML_TEST_NAME ML_TEST_NAME)

    ADD_EXECUTABLE(${ML_TEST_NAME} ${ML_TEST_SRC})
    TARGET_LINK_LIBRARIES(${ML_TEST_NAME} ${BUILD_SHARED_NAME} ${LINK_LIBS})

ELSE(ML_TEST)
    message("${PROJECT_NAME} ML_TEST OFF")
ENDIF(ML_TEST)


########################## install info  ##########################


install(DIRECTORY include DESTINATION ./ 
        PATTERN "CMakeLists.txt" EXCLUDE
        PATTERN ".gitignore" EXCLUDE)

install(TARGETS ${BUILD_SHARED_NAME}
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


install(TARGETS ${BUILD_STATIC_NAME}
    DESTINATION lib
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)


