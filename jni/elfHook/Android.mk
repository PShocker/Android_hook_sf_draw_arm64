LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := hello
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog -lEGL -lGLESv1_CM -lGLESv2
MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
# MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)
LOCAL_CPPFLAGS := -std=c++11
LOCAL_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_SHARED_LIBRARY)
