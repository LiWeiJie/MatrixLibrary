#
# MatrixLibrary.main.mk
# For Android MatrixLibrary Library
#
# Only compile MatrixLibrary (Base modules, except SM4 White box)
#
# ONLY SUPPORT 32bits OS
#

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
APP_BUILD_SCRIPT := MatrixLibrary.mk
NDK_APP_DST_DIR := ./android-lib/$(TARGET_ARCH_ABI)

# Target filename
LOCAL_MODULE := MatrixLibrary-lib
APP_ABI := armeabi-v7a x86
# NOT SUPPORT armeabi
# PARTICULAR SUPPORT x64

APP_PLATFORM := android-14 # >= 4.0

# APP_STL := c++_static # OLLVM
APP_CPPFLAGS += -frtti -fexceptions -fvisibility=hidden

# Required Modules
LOCAL_CFLAGS += -DANDROID_VER -DANDROID_MK_VER
LOCAL_CFLAGS += -D__ANDROID__

MY_HEADER_FILES_PATH := $(LOCAL_PATH)/include/

MY_SOURCE_FILES_PATH := $(LOCAL_PATH)/src

# Debug / Production
ifeq ($(DEBUG),1)
APP_CFLAGS += -O0 -g
APP_OPTIM := debug
else
APP_CFLAGS += -O3
APP_OPTIM := release
endif

# Include headers
LOCAL_C_INCLUDES := $(MY_HEADER_FILES_PATH)

# Include source files
LOCAL_SRC_FILES := $(wildcard $(MY_SOURCE_FILES_PATH)/m4ri/*.c)
LOCAL_SRC_FILES += $(wildcard $(MY_SOURCE_FILES_PATH)/matrixlib/*.c)

LOCAL_LDLIBS += -landroid
LOCAL_LDLIBS += -llog # When Debug

include $(BUILD_SHARED_LIBRARY)
