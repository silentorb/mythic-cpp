
create_library(glow)

if (MSVC)
  add_sources(glad/src/glad.c)
#  add_sources(glloader/gl_core_4_4.c)
elseif (MINGW)
  add_sources(glloader/gl_core_4_4.c)
endif ()

if (ANDROID)
  add_sources(android/android-gl.cpp)
  add_system_libraries(GLESv2)
#  target_link_libraries(glow -lGLESv2)
else ()
#  target_link_libraries(glow ${OPENGL_LIB})
  if (MINGW)
    #    set(OPENGL_LIB -lglu32 -lopengl32)
    link_system_library(glu32)
    link_system_library(opengl32)
  elseif (MSVC)
    #    set(OPENGL_LIB opengl32.lib)
    link_system_library(opengl32)
  endif ()
endif ()

add_definitions(-DGLOW_LIB)

require(math)