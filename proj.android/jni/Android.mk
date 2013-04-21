LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp 
                   ../../Classes/AppMacros.cpp
				   ../../Classes/DaFeiJi.cpp
				   ../../Classes/bullet.cpp
				   ../../Classes/enemy.cpp
				   ../../Classes/explosion.cpp
				   ../../Classes/LevelManager.cpp
				   ../../Classes/ship.cpp
				   ../../Classes/HelloWorldScene.cpp\
				   ../../Classes/SysMenu.cpp\


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

