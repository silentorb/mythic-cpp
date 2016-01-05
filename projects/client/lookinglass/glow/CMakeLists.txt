
if (MSVC)
  set(GL_FILES glad/src/glad.c)
elseif (MINGW)
  set(GL_FILES source/gl_core_4_4.c)
endif ()

create_library(glow)

if (ANDROID)
  set(glow_system_libraries EGL GLESv1_CM PARENT_SCOPE)
else ()
  target_link_libraries(glow
    ${OPENGL_LIB}
    )
endif ()