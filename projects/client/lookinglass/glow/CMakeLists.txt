
add_project(glow)

include_directories(
	${glow_includes}
)

if (MSVC)
	set(GL_FILES glad/src/glad.c)
elseif (MINGW)
	set(GL_FILES source/gl_core_4_4.c)
endif ()

create_library(glow
	${GL_FILES}
	source/lookinglass/glow.h
	source/lookinglass/utility.cpp
	source/lookinglass/utility.h
	source/lookinglass/glow/Capabilities.cpp
	source/lookinglass/glow/Capabilities.h
	source/lookinglass/glow/Version.cpp
	source/lookinglass/glow/Version.h)

target_link_libraries(glow
	${OPENGL_LIB}
	)
