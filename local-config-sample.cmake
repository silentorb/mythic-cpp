
if (LOCAL_HEADER)
  set(android_sdk_dir "C:/Users/me/AppData/Local/Android/android-sdk")
  set(DEBUG_OPTIMIZATION_LEVEL O2)
  #  set(MSVC_DEBUG_FLAGS /O2 /Ob2)

elseif (LOCAL_FOOTER)
  include(games/mygame/mygame.cmake)
  set(ANDROID_DEPENDENCIES E:/dev/cpp/dependencies/build/android/jni)
endif ()
