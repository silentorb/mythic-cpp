
add_project(glow)

include_directories(
	${glow_includes}
)

create_library(glow
	source/gl_core_4_4.c
	source/lookinglass/utility.cpp
	source/lookinglass/utility.h
	source/lookinglass/glow/Capabilities.cpp
	source/lookinglass/glow/Capabilities.h
	source/lookinglass/glow/Version.cpp
	source/lookinglass/glow/Version.h)

target_link_libraries(glow
	-lglu32 -lopengl32
	)
