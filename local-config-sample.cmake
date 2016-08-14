
if (LOCAL_HEADER)

  set(android_sdk_dir "E:/Programs/Android/sdk")
  #  set(DEBUG_OPTIMIZATION_LEVEL O2)
  set(MYTHIC_DEPENDENCIES E:/dev/cpp/mythic/dependencies/mingw)
  set(ANDROID_DEPENDENCIES E:/dev/cpp/mythic/mythic-dependencies/build/android/jni)

  macro(on_create_target_local)
    if (MSVC AND NOT CURRENT_TARGET STREQUAL "boost_regex" AND NOT CURRENT_TARGET STREQUAL "shader_processing")
      #  set(MSVC_DEBUG_FLAGS /O2 /Ob2)
      #      set(MSVC_DEBUG_FLAGS /FI\"${CMAKE_SOURCE_DIR}/projects/misc/commoner/source/commoner/ms-debug-new.h\")
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${MSVC_DEBUG_FLAGS}")
    endif ()
  endmacro()

elseif (LOCAL_FOOTER)

  include(games/spacegame/spacegame.cmake)

endif ()