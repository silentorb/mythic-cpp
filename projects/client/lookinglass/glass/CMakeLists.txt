
add_project(glass)

add_library(glass
	source/lookinglass/Glass.cpp
	source/lookinglass/Glass.h
	source/lookinglass/Renderable.h
	source/lookinglass/Draw_Method.h
	source/lookinglass/Mesh_Data.h)

require_package(glass glow)

include_directories(
	${glass_includes}
)

target_link_libraries(glass

  )
