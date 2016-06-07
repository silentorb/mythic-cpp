
create_library(glow)

if (MSVC)
  add_sources(glad/src/glad.c)
elseif (MINGW)
  add_sources(glloader/gl_core_4_4.c)
endif ()

if (ANDROID)
  add_sources(android/android-gl.cpp)
  add_system_libraries(GLESv2)
#  target_link_libraries(glow -lGLESv2)
else ()
  target_link_libraries(glow ${OPENGL_LIB})
endif ()

add_definitions(-DGLOW_LIB)