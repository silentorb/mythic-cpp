
add_project(glow)

include_directories(
	${glow_includes}
)

add_library(glow
	../glow/source/gl_core_4_4.c

	source/lookinglass/utility.cpp source/lookinglass/utility.h source/lookinglass/Capabilities.cpp source/lookinglass/Capabilities.h)
target_link_libraries(glow
	-lglu32 -lopengl32
	)
