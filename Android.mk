LOCAL_PATH := $(call my-dir)
 

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder       
LOCAL_LDLIBS += -landroid -llog
LOCAL_MODULE    := PolySpatialServer
LOCAL_CFLAGS += -Wno-error -Wnon-virtual-dtor -Wunused-parameter
LOCAL_SRC_FILES := \
    sharedmemory/sharedmemory_android.cpp \
    binder/PolySpatialServer.cpp
   
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
  

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libbinder
LOCAL_LDLIBS += -landroid -llog 
LOCAL_MODULE    := PolySpatialClient
LOCAL_CFLAGS += -Wno-error -Wnon-virtual-dtor -Wunused-parameter
LOCAL_SRC_FILES := \
    sharedmemory/sharedmemory_android.cpp \
    binder/PolySpatialClient.cpp
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
