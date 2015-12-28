
add_project(glass)

create_library(glass
	source/lookinglass/Glass.cpp
	source/lookinglass/Glass.h
	source/lookinglass/Renderable.h
	source/lookinglass/Draw_Method.h
	)

require_package(glass glow)
require_package(glass shading)
require_package(glass modeling)

include_directories(
	${glass_includes}
)

target_link_libraries(glass

  )
