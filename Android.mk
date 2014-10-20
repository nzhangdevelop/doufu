ifneq ($(TARGET_SIMULATOR),true)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS:= eng
LOCAL_SRC_FILES:= fbcontrol.c
LOCAL_MODULE := fbcontrol
LOCAL_STATIC_LIBRARIES := libcutils libc
include $(BUILD_EXECUTABLE)

endif  # TARGET_SIMULATOR != true
