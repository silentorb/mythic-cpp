
add_project(glow)

include_directories(
	${glow_includes}
)

add_library(glow
	../glow/source/gl_core_4_4.c

)
target_link_libraries(glow
	-lglu32 -lopengl32
	)
